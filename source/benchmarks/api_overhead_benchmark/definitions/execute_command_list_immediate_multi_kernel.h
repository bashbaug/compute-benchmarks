/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "framework/argument/basic_argument.h"
#include "framework/test_case/test_case.h"

struct ExecuteCommandListImmediateMultiKernelArguments : TestCaseArgumentContainer {
    PositiveIntegerArgument amountOfCalls;
    PositiveIntegerArgument kernelExecutionTime;
    BooleanArgument addBarrier;
    PositiveIntegerArgument numKernelsBeforeBarrier;
    PositiveIntegerArgument numKernelsAfterBarrier;

    ExecuteCommandListImmediateMultiKernelArguments()
        : amountOfCalls(*this, "CallsCount", "amount of calls that is being measured"),
          kernelExecutionTime(*this, "KernelExecutionTime", "Approximately how long a single kernel executes, in us"),
          addBarrier(*this, "AddBarrier", "Add a Barrier after certain number of Kernel launches, number of kernels before barrier is controlled by numKernelsBeforeBarrier"),
          numKernelsBeforeBarrier(*this, "NumKernelsBeforeBarrier", "Adds certain number of kernels prior to Barrier, Default is 2"),
          numKernelsAfterBarrier(*this, "NumKernelsAfterBarrier", "Adds certain number of kernels after Barrier, Default is 2") {}
};

struct ExecuteCommandListImmediateMultiKernel : TestCase<ExecuteCommandListImmediateMultiKernelArguments> {
    using TestCase<ExecuteCommandListImmediateMultiKernelArguments>::TestCase;

    std::string getTestCaseName() const override {
        return "ExecuteCommandListImmediateMultiKernel";
    }

    std::string getHelp() const override {
        return "measures time spent in executing multiple instances of two different kernels with immediate command list on CPU";
    }
};
