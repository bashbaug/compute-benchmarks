/*
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "framework/ocl/opencl.h"
#include "framework/test_case/register_test_case.h"
#include "framework/utility/file_helper.h"
#include "framework/utility/timer.h"

#include "definitions/execute_command_buffer.h"

#include <gtest/gtest.h>

#if !defined(cl_khr_command_buffer)

/***************************************************************
* cl_khr_command_buffer
***************************************************************/
#define cl_khr_command_buffer 1
#define CL_KHR_COMMAND_BUFFER_EXTENSION_NAME \
    "cl_khr_command_buffer"

typedef cl_bitfield         cl_device_command_buffer_capabilities_khr;
typedef struct _cl_command_buffer_khr* cl_command_buffer_khr;
typedef cl_uint             cl_sync_point_khr;
typedef cl_uint             cl_command_buffer_info_khr;
typedef cl_uint             cl_command_buffer_state_khr;
typedef cl_properties       cl_command_buffer_properties_khr;
typedef cl_bitfield         cl_command_buffer_flags_khr;
typedef cl_properties       cl_ndrange_kernel_command_properties_khr;
typedef struct _cl_mutable_command_khr* cl_mutable_command_khr;

/* cl_device_info */
#define CL_DEVICE_COMMAND_BUFFER_CAPABILITIES_KHR           0x12A9
#define CL_DEVICE_COMMAND_BUFFER_REQUIRED_QUEUE_PROPERTIES_KHR 0x12AA

/* cl_device_command_buffer_capabilities_khr - bitfield */
#define CL_COMMAND_BUFFER_CAPABILITY_KERNEL_PRINTF_KHR      (1 << 0)
#define CL_COMMAND_BUFFER_CAPABILITY_DEVICE_SIDE_ENQUEUE_KHR (1 << 1)
#define CL_COMMAND_BUFFER_CAPABILITY_SIMULTANEOUS_USE_KHR   (1 << 2)
#define CL_COMMAND_BUFFER_CAPABILITY_OUT_OF_ORDER_KHR       (1 << 3)

/* cl_command_buffer_properties_khr */
#define CL_COMMAND_BUFFER_FLAGS_KHR                         0x1293
#define CL_COMMAND_BUFFER_MUTABLE_DISPATCH_ASSERTS_KHR      0x12B7

/* cl_command_buffer_flags_khr - bitfield */
#define CL_COMMAND_BUFFER_SIMULTANEOUS_USE_KHR              (1 << 0)

/* Error codes */
#define CL_INVALID_COMMAND_BUFFER_KHR                       -1138
#define CL_INVALID_SYNC_POINT_WAIT_LIST_KHR                 -1139
#define CL_INCOMPATIBLE_COMMAND_QUEUE_KHR                   -1140

/* cl_command_buffer_info_khr */
#define CL_COMMAND_BUFFER_QUEUES_KHR                        0x1294
#define CL_COMMAND_BUFFER_NUM_QUEUES_KHR                    0x1295
#define CL_COMMAND_BUFFER_REFERENCE_COUNT_KHR               0x1296
#define CL_COMMAND_BUFFER_STATE_KHR                         0x1297
#define CL_COMMAND_BUFFER_PROPERTIES_ARRAY_KHR              0x1298
#define CL_COMMAND_BUFFER_CONTEXT_KHR                       0x1299

/* cl_command_buffer_state_khr */
#define CL_COMMAND_BUFFER_STATE_RECORDING_KHR               0
#define CL_COMMAND_BUFFER_STATE_EXECUTABLE_KHR              1
#define CL_COMMAND_BUFFER_STATE_PENDING_KHR                 2

/* cl_command_type */
#define CL_COMMAND_COMMAND_BUFFER_KHR                       0x12A8


typedef cl_command_buffer_khr CL_API_CALL
clCreateCommandBufferKHR_t(
    cl_uint num_queues,
    const cl_command_queue* queues,
    const cl_command_buffer_properties_khr* properties,
    cl_int* errcode_ret);

typedef clCreateCommandBufferKHR_t *
clCreateCommandBufferKHR_fn ;

typedef cl_int CL_API_CALL
clFinalizeCommandBufferKHR_t(
    cl_command_buffer_khr command_buffer);

typedef clFinalizeCommandBufferKHR_t *
clFinalizeCommandBufferKHR_fn ;

typedef cl_int CL_API_CALL
clRetainCommandBufferKHR_t(
    cl_command_buffer_khr command_buffer);

typedef clRetainCommandBufferKHR_t *
clRetainCommandBufferKHR_fn ;

typedef cl_int CL_API_CALL
clReleaseCommandBufferKHR_t(
    cl_command_buffer_khr command_buffer);

typedef clReleaseCommandBufferKHR_t *
clReleaseCommandBufferKHR_fn ;

typedef cl_int CL_API_CALL
clEnqueueCommandBufferKHR_t(
    cl_uint num_queues,
    cl_command_queue* queues,
    cl_command_buffer_khr command_buffer,
    cl_uint num_events_in_wait_list,
    const cl_event* event_wait_list,
    cl_event* event);

typedef clEnqueueCommandBufferKHR_t *
clEnqueueCommandBufferKHR_fn ;

typedef cl_int CL_API_CALL
clCommandBarrierWithWaitListKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandBarrierWithWaitListKHR_t *
clCommandBarrierWithWaitListKHR_fn ;

typedef cl_int CL_API_CALL
clCommandCopyBufferKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    size_t src_offset,
    size_t dst_offset,
    size_t size,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandCopyBufferKHR_t *
clCommandCopyBufferKHR_fn ;

typedef cl_int CL_API_CALL
clCommandCopyBufferRectKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    size_t src_row_pitch,
    size_t src_slice_pitch,
    size_t dst_row_pitch,
    size_t dst_slice_pitch,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandCopyBufferRectKHR_t *
clCommandCopyBufferRectKHR_fn ;

typedef cl_int CL_API_CALL
clCommandCopyBufferToImageKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_mem src_buffer,
    cl_mem dst_image,
    size_t src_offset,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandCopyBufferToImageKHR_t *
clCommandCopyBufferToImageKHR_fn ;

typedef cl_int CL_API_CALL
clCommandCopyImageKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_image,
    const size_t* src_origin,
    const size_t* dst_origin,
    const size_t* region,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandCopyImageKHR_t *
clCommandCopyImageKHR_fn ;

typedef cl_int CL_API_CALL
clCommandCopyImageToBufferKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_mem src_image,
    cl_mem dst_buffer,
    const size_t* src_origin,
    const size_t* region,
    size_t dst_offset,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandCopyImageToBufferKHR_t *
clCommandCopyImageToBufferKHR_fn ;

typedef cl_int CL_API_CALL
clCommandFillBufferKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_mem buffer,
    const void* pattern,
    size_t pattern_size,
    size_t offset,
    size_t size,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandFillBufferKHR_t *
clCommandFillBufferKHR_fn ;

typedef cl_int CL_API_CALL
clCommandFillImageKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    cl_mem image,
    const void* fill_color,
    const size_t* origin,
    const size_t* region,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandFillImageKHR_t *
clCommandFillImageKHR_fn ;

typedef cl_int CL_API_CALL
clCommandNDRangeKernelKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    const cl_ndrange_kernel_command_properties_khr* properties,
    cl_kernel kernel,
    cl_uint work_dim,
    const size_t* global_work_offset,
    const size_t* global_work_size,
    const size_t* local_work_size,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandNDRangeKernelKHR_t *
clCommandNDRangeKernelKHR_fn ;

typedef cl_int CL_API_CALL
clCommandSVMMemcpyKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    void* dst_ptr,
    const void* src_ptr,
    size_t size,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandSVMMemcpyKHR_t *
clCommandSVMMemcpyKHR_fn CL_API_SUFFIX__VERSION_2_0;

typedef cl_int CL_API_CALL
clCommandSVMMemFillKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_queue command_queue,
    void* svm_ptr,
    const void* pattern,
    size_t pattern_size,
    size_t size,
    cl_uint num_sync_points_in_wait_list,
    const cl_sync_point_khr* sync_point_wait_list,
    cl_sync_point_khr* sync_point,
    cl_mutable_command_khr* mutable_handle);

typedef clCommandSVMMemFillKHR_t *
clCommandSVMMemFillKHR_fn CL_API_SUFFIX__VERSION_2_0;

typedef cl_int CL_API_CALL
clGetCommandBufferInfoKHR_t(
    cl_command_buffer_khr command_buffer,
    cl_command_buffer_info_khr param_name,
    size_t param_value_size,
    void* param_value,
    size_t* param_value_size_ret);

typedef clGetCommandBufferInfoKHR_t *
clGetCommandBufferInfoKHR_fn ;

#endif // !defined(cl_khr_command_buffer)

static TestResult run([[maybe_unused]] const ExecuteCommandBufferArguments &arguments, Statistics &statistics) {
    MeasurementFields typeSelector(MeasurementUnit::Microseconds, MeasurementType::Cpu);

    if (isNoopRun()) {
        statistics.pushUnitAndType(typeSelector.getUnit(), typeSelector.getType());
        return TestResult::Nooped;
    }

    // Setup
    QueueProperties queueProperties = QueueProperties::create().setOoq(false);
    Opencl opencl(queueProperties);
    cl_int retVal{};

    if (arguments.useCommandBuffers && !opencl.getExtensions().isSupported(CL_KHR_COMMAND_BUFFER_EXTENSION_NAME)) {
        return TestResult::DeviceNotCapable;
    }

    auto clCreateCommandBufferKHR = (clCreateCommandBufferKHR_fn)clGetExtensionFunctionAddressForPlatform(opencl.platform, "clCreateCommandBufferKHR");
    auto clCommandNDRangeKernelKHR = (clCommandNDRangeKernelKHR_fn)clGetExtensionFunctionAddressForPlatform(opencl.platform, "clCommandNDRangeKernelKHR");
    auto clFinalizeCommandBufferKHR = (clFinalizeCommandBufferKHR_fn)clGetExtensionFunctionAddressForPlatform(opencl.platform, "clFinalizeCommandBufferKHR");
    auto clReleaseCommandBufferKHR = (clReleaseCommandBufferKHR_fn)clGetExtensionFunctionAddressForPlatform(opencl.platform, "clReleaseCommandBufferKHR");
    auto clEnqueueCommandBufferKHR = (clEnqueueCommandBufferKHR_fn)clGetExtensionFunctionAddressForPlatform(opencl.platform, "clEnqueueCommandBufferKHR");

    Timer timer;
    const size_t gws = 1u;
    const size_t lws = 1u;

    // Create kernel
    const std::vector<uint8_t> kernelSource = FileHelper::loadTextFile("ulls_benchmark_eat_time.cl");
    if (kernelSource.size() == 0) {
        return TestResult::KernelNotFound;
    }
    const char *source = reinterpret_cast<const char *>(kernelSource.data());
    const size_t sourceLength = kernelSource.size();
    cl_program program = clCreateProgramWithSource(opencl.context, 1, &source, &sourceLength, &retVal);
    ASSERT_CL_SUCCESS(retVal);
    ASSERT_CL_SUCCESS(clBuildProgram(program, 1, &opencl.device, nullptr, nullptr, nullptr));
    cl_kernel kernel = clCreateKernel(program, "eat_time", &retVal);
    ASSERT_CL_SUCCESS(retVal);

    int kernelOperationsCount = static_cast<int>(arguments.kernelExecutionTime);

    // Create command buffer
    cl_command_buffer_khr cmdBuf{};
    if (arguments.useCommandBuffers) {
        cmdBuf = clCreateCommandBufferKHR(1, &opencl.commandQueue, nullptr, &retVal);
        ASSERT_CL_SUCCESS(retVal);
        for (auto iteration = 0u; iteration < arguments.numKernels; iteration++) {
            ASSERT_CL_SUCCESS(clSetKernelArg(kernel, 0, sizeof(int), &kernelOperationsCount));
            ASSERT_CL_SUCCESS(clCommandNDRangeKernelKHR(cmdBuf, nullptr, nullptr, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr, nullptr));
        }
        ASSERT_CL_SUCCESS(clFinalizeCommandBufferKHR(cmdBuf));
    }

    // Warmup
    if (arguments.useCommandBuffers) {
        ASSERT_CL_SUCCESS(clEnqueueCommandBufferKHR(0, nullptr, cmdBuf, 0, nullptr, nullptr));
    } else {
        for (auto iteration = 0u; iteration < arguments.numKernels; iteration++) {
            ASSERT_CL_SUCCESS(clSetKernelArg(kernel, 0, sizeof(int), &kernelOperationsCount));
            ASSERT_CL_SUCCESS(clEnqueueNDRangeKernel(opencl.commandQueue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr));
        }
    }
    ASSERT_CL_SUCCESS(clFinish(opencl.commandQueue));

    // Benchmark
    for (auto i = 0u; i < arguments.iterations; i++) {
        timer.measureStart();
        if (arguments.useCommandBuffers) {
            ASSERT_CL_SUCCESS(clEnqueueCommandBufferKHR(0, nullptr, cmdBuf, 0, nullptr, nullptr));
        } else {
            for (auto iteration = 0u; iteration < arguments.numKernels; iteration++) {
                ASSERT_CL_SUCCESS(clSetKernelArg(kernel, 0, sizeof(int), &kernelOperationsCount));
                ASSERT_CL_SUCCESS(clEnqueueNDRangeKernel(opencl.commandQueue, kernel, 1, nullptr, &gws, &lws, 0, nullptr, nullptr));
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

    // Clean up
    if (clReleaseCommandBufferKHR && cmdBuf) {
        ASSERT_CL_SUCCESS(clReleaseCommandBufferKHR(cmdBuf));
    }
    ASSERT_CL_SUCCESS(clReleaseProgram(program));
    ASSERT_CL_SUCCESS(clReleaseKernel(kernel));

    return TestResult::Success;
}

[[maybe_unused]] static RegisterTestCaseImplementation<ExecuteCommandBuffer> registerTestCase(run, Api::OpenCL);
