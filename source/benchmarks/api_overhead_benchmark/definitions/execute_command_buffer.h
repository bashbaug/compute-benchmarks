/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include "framework/argument/basic_argument.h"
#include "framework/test_case/test_case.h"

struct ExecuteCommandBufferArguments : TestCaseArgumentContainer {
    BooleanArgument useCommandBuffers;
    PositiveIntegerArgument numKernels;
    PositiveIntegerArgument kernelExecutionTime;
    BooleanArgument measureCompletionTime;

    ExecuteCommandBufferArguments()
        : useCommandBuffers(*this, "UseCommandBuffers", "Build and use command buffers"),
          numKernels(*this, "NumKernels", "Number of kernels to submit to the queue"),
          kernelExecutionTime(*this, "KernelExecutionTime", "Approximately how long a single kernel executes, in us"),
          measureCompletionTime(*this, "MeasureCompletionTime", "Measures time taken to complete the command (default is to measure only enqueue calls)") {}
};

struct ExecuteCommandBuffer : TestCase<ExecuteCommandBufferArguments> {
    using TestCase<ExecuteCommandBufferArguments>::TestCase;

    std::string getTestCaseName() const override {
        return "ExecuteCommandBuffer";
    }

    std::string getHelp() const override {
        return "measures time spent enqueueing a command buffer to an OpenCL queue on CPU.";
    }
};
