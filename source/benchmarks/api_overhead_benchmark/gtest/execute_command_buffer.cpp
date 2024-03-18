/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "definitions/execute_command_buffer.h"

#include "framework/test_case/register_test_case.h"
#include "framework/utility/common_gtest_args.h"

#include <gtest/gtest.h>

[[maybe_unused]] static const inline RegisterTestCase<ExecuteCommandBuffer> registerTestCase{};

class ExecuteCommandBufferTest : public ::testing::TestWithParam<std::tuple<Api, bool, size_t, size_t, bool>> {
};

TEST_P(ExecuteCommandBufferTest, Test) {
    ExecuteCommandBufferArguments args{};
    args.api = std::get<0>(GetParam());
    args.useCommandBuffers = std::get<1>(GetParam());
    args.numKernels = std::get<2>(GetParam());
    args.kernelExecutionTime = std::get<3>(GetParam());
    args.measureCompletionTime = std::get<4>(GetParam());
    ExecuteCommandBuffer test;
    test.run(args);
}

INSTANTIATE_TEST_SUITE_P(
    ExecuteCommandBufferTest,
    ExecuteCommandBufferTest,
    ::testing::Combine(
        ::CommonGtestArgs::allApis(),
        ::testing::Values(false, true),   // useCommandBuffers
        ::testing::Values(10u),           // numKernels
        ::testing::Values(1u),            // kernelExecutionTime
        ::testing::Values(false, true))); // measureCompletionTime
