/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "framework/sycl/sycl.h"
#include "framework/test_case/register_test_case.h"
#include "framework/utility/timer.h"

#include "definitions/execute_command_list_immediate.h"

#include <gtest/gtest.h>

// Unused:
// arguments.useBarrierSynchronization


static TestResult run(const ExecuteCommandListImmediateArguments &arguments, Statistics &statistics) {
    const bool HaveEvent = false;
    MeasurementFields typeSelector(MeasurementUnit::Microseconds, MeasurementType::Cpu);

    if (isNoopRun()) {
        statistics.pushUnitAndType(typeSelector.getUnit(), typeSelector.getType());
        return TestResult::Nooped;
    }

    // Setup
    Sycl sycl = arguments.useProfiling ?
        Sycl{sycl::device{sycl::gpu_selector_v}, sycl::property::queue::in_order(), sycl::property::queue::enable_profiling()} :
        HaveEvent ?
        Sycl{sycl::device{sycl::gpu_selector_v}, sycl::property::queue::in_order()} :
        Sycl{sycl::device{sycl::gpu_selector_v}, sycl::property::queue::in_order(), sycl::ext::oneapi::property::queue::discard_events()};
    Timer timer;
    const size_t gws = 1u;
    const size_t lws = 1u;
    sycl::nd_range<1> range(gws, lws);

    // Create kernel
    //const auto empty = [=]([[maybe_unused]] auto i) {};
    int kernelOperationsCount = static_cast<int>(arguments.kernelExecutionTime * 4);
    const auto eat_time = [=]([[maybe_unused]] auto u) {
        volatile int value = 1u;
        for(int i =0;i<kernelOperationsCount;i++){
            value /=2;
            value *=2;
        }
    };

    // Warmup
    auto event = sycl.queue.parallel_for(range, eat_time);
    if (arguments.useEventForHostSync) {
        event.wait();
    } else {
        sycl.queue.wait();
    }

    // Benchmark
    for (auto i = 0u; i < arguments.iterations; i++) {
        timer.measureStart();
        for (auto iteration = 0u; iteration < arguments.amountOfCalls; iteration++) {
            if (arguments.useEventForHostSync) {
                event = sycl.queue.parallel_for(range, event, eat_time);
            } else {
                sycl.queue.parallel_for(range, eat_time);
            }
        }

        if (!arguments.measureCompletionTime) {
            timer.measureEnd();
            statistics.pushValue(timer.get(), typeSelector.getUnit(), typeSelector.getType());
        }

        if (arguments.useEventForHostSync) {
            event.wait();
        } else {
            sycl.queue.wait();
        }

        if (arguments.measureCompletionTime) {
            timer.measureEnd();
            statistics.pushValue(timer.get(), typeSelector.getUnit(), typeSelector.getType());
        }
    }
    sycl.queue.wait();

    return TestResult::Success;
}

[[maybe_unused]] static RegisterTestCaseImplementation<ExecuteCommandListImmediate> registerTestCase(run, Api::SYCL);
