/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "framework/ocl/opencl.h"
#include "framework/test_case/register_test_case.h"
#include "framework/utility/file_helper.h"
#include "framework/utility/timer.h"

#include "definitions/execute_command_list_immediate.h"

#include <gtest/gtest.h>

static TestResult run(const ExecuteCommandListImmediateArguments &arguments, Statistics &statistics) {
    const bool HaveEvent = true;
    MeasurementFields typeSelector(MeasurementUnit::Microseconds, MeasurementType::Cpu);

    if (isNoopRun()) {
        statistics.pushUnitAndType(typeSelector.getUnit(), typeSelector.getType());
        return TestResult::Nooped;
    }

    // Setup
    QueueProperties queueProperties = QueueProperties::create().setProfiling(arguments.useProfiling).setOoq(false);
    Opencl opencl(queueProperties);
    cl_int retVal{};
    Timer timer;
    const size_t gws = 1u;
    const size_t lws = 1u;

    // Create kernel
    auto spirvModule = FileHelper::loadBinaryFile("api_overhead_benchmark_eat_time.spv");
    if (spirvModule.size() == 0) {
        return TestResult::KernelNotFound;
    }
    cl_program program = clCreateProgramWithIL(opencl.context, spirvModule.data(), spirvModule.size(), &retVal);
    ASSERT_CL_SUCCESS(retVal);
    ASSERT_CL_SUCCESS(clBuildProgram(program, 1, &opencl.device, nullptr, nullptr, nullptr));
    cl_kernel kernel = clCreateKernel(program, "eat_time", &retVal);
    ASSERT_CL_SUCCESS(retVal);

    int kernelOperationsCount = static_cast<int>(arguments.kernelExecutionTime * 4);
    ASSERT_CL_SUCCESS(clSetKernelArg(kernel, 0, sizeof(int), &kernelOperationsCount));

    // Warmup
    cl_event event{};
    cl_event* eventPtr = HaveEvent ? &event : nullptr;
    ASSERT_CL_SUCCESS(clEnqueueNDRangeKernel(opencl.commandQueue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, eventPtr));
    if (HaveEvent) {
        ASSERT_CL_SUCCESS(clReleaseEvent(event));
    }
    ASSERT_CL_SUCCESS(clFinish(opencl.commandQueue));

    // Benchmark
    for (auto i = 0u; i < arguments.iterations; i++) {
        timer.measureStart();
        for (auto iteration = 0u; iteration < arguments.amountOfCalls; iteration++) {
            // Always call clSetKernelArg, to match the SYCL behavior:
            ASSERT_CL_SUCCESS(clSetKernelArg(kernel, 0, sizeof(int), &kernelOperationsCount));
            // Always create and release an event, to match the SYCL behavior:
            ASSERT_CL_SUCCESS(clEnqueueNDRangeKernel(opencl.commandQueue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, eventPtr));
            if (HaveEvent) {
                ASSERT_CL_SUCCESS(clReleaseEvent(event));
            }
        }

        if (!arguments.measureCompletionTime) {
            timer.measureEnd();
            statistics.pushValue(timer.get(), typeSelector.getUnit(), typeSelector.getType());
        }

        ASSERT_CL_SUCCESS(clFinish(opencl.commandQueue));
        if (arguments.measureCompletionTime) {
            timer.measureEnd();
            statistics.pushValue(timer.get(), typeSelector.getUnit(), typeSelector.getType());
        }
    }
    ASSERT_CL_SUCCESS(clFinish(opencl.commandQueue));

    return TestResult::Success;
}

static RegisterTestCaseImplementation<ExecuteCommandListImmediate> registerTestCase(run, Api::OpenCL);
