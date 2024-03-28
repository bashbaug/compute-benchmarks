/*
 * Copyright (C) 2022-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "definitions/submit_graph.h"

#include "framework/test_case/register_test_case.h"
#include "framework/utility/common_gtest_args.h"

#include <gtest/gtest.h>

[[maybe_unused]] static const inline RegisterTestCase<SubmitGraph> registerTestCase{};

class SubmitGraphTest : public ::testing::TestWithParam<std::tuple<Api, bool, size_t, size_t, size_t, bool>> {
};

TEST_P(SubmitGraphTest, Test) {
    SubmitGraphArguments args{};
    args.api = std::get<0>(GetParam());
    //args.useProfiling = std::get<1>(GetParam());
    args.inOrderQueue = std::get<1>(GetParam());
    //args.discardEvents = std::get<3>(GetParam());
    args.numKernels = std::get<2>(GetParam());
    args.kernelExecutionTime = std::get<3>(GetParam());
    args.kernelType = std::get<4>(GetParam());
    args.measureCompletionTime = std::get<5>(GetParam());
    SubmitGraph test;
    test.run(args);
}

INSTANTIATE_TEST_SUITE_P(
    SubmitGraphTest,
    SubmitGraphTest,
    ::testing::Combine(
        ::CommonGtestArgs::allApis(),
        //::testing::Values(false),         // useProfiling
        ::testing::Values(false, true),   // inOrderQueue
        //::testing::Values(false, true),   // discardEvents
        ::testing::Values(32u),           // numKernels
        ::testing::Values(1u),            // kernelExecutionTime
        ::testing::Values(0u),            // kernelType
        ::testing::Values(false, true))); // measureCompletionTime
