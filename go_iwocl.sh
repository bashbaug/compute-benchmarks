set -ex
rm -f iwocl_results.csv

echo "--- Initial Environment Variables..."
echo Initial LD_LIBRARY_PATH is: $LD_LIBRARY_PATH
echo Initial OPENCL_LAYERS is: $OPENCL_LAYERS

echo "--- Setting Environment Variables..."
export LD_LIBRARY_PATH=/home/bashbaug/git/SimpleOpenCLSamples/install/lib:$LD_LIBRARY_PATH
echo Now LD_LIBRARY_PATH is: $LD_LIBRARY_PATH

echo "OpenCL With Layer:" >> iwocl_results.csv
# NVIDIA GeForce RTX 3060
OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
./bin/api_overhead_benchmark_ocl --iterations=10000 --gtest_filter=*ExecuteCommandBuffer* --oclPlatformIndex=0 --csv >> iwocl_results.csv
# POCL (CPU)
OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
./bin/api_overhead_benchmark_ocl --iterations=10000 --gtest_filter=*ExecuteCommandBuffer* --oclPlatformIndex=1 --csv >> iwocl_results.csv
# Arc(TM) A750 Graphics
OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
./bin/api_overhead_benchmark_ocl --iterations=10000 --gtest_filter=*ExecuteCommandBuffer* --oclPlatformIndex=2 --csv >> iwocl_results.csv
# UHD Graphics 770
OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
./bin/api_overhead_benchmark_ocl --iterations=10000 --gtest_filter=*ExecuteCommandBuffer* --oclPlatformIndex=3 --csv >> iwocl_results.csv
# OneAPI Construction Kit (CPU)
OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
OCL_ICD_FILENAMES=/home/bashbaug/git/oneapi-construction-kit/build/lib/libCL.so \
./bin/api_overhead_benchmark_ocl --iterations=10000 --gtest_filter=*ExecuteCommandBuffer* --oclPlatformIndex=0 --csv >> iwocl_results.csv

echo "OpenCL No Layer:" >> iwocl_results.csv
# POCL (CPU)
./bin/api_overhead_benchmark_ocl --iterations=10000 --gtest_filter=*ExecuteCommandBuffer* --oclPlatformIndex=1 --csv >> iwocl_results.csv
# OneAPI Construction Kit (CPU)
OCL_ICD_FILENAMES=/home/bashbaug/git/oneapi-construction-kit/build/lib/libCL.so \
./bin/api_overhead_benchmark_ocl --iterations=10000 --gtest_filter=*ExecuteCommandBuffer* --oclPlatformIndex=0 --csv >> iwocl_results.csv

echo "SYCL With Layer:" >> iwocl_results.csv
# POCL (CPU)
# Disabling - does not work currently:
# Fails to verify module: GEP base pointer is not a vector or a vector of pointers
#OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
#ONEAPI_DEVICE_SELECTOR=opencl:0 \
#./bin/api_overhead_benchmark_sycl --gtest_filter=*SubmitGraph* --iterations=10000 --csv >> iwocl_results.csv
# OneAPI Construction Kit (CPU)
OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
ONEAPI_DEVICE_SELECTOR=opencl:0 OCL_ICD_FILENAMES=/home/bashbaug/git/oneapi-construction-kit/build/lib/libCL.so \
./bin/api_overhead_benchmark_sycl --gtest_filter=*SubmitGraph* --iterations=10000 --csv >> iwocl_results.csv
# Arc(TM) A750 Graphics
OPENCL_LAYERS=/home/bashbaug/git/SimpleOpenCLSamples/install/RelWithDebInfo/libCmdBufEmu.so \
ONEAPI_DEVICE_SELECTOR=opencl:1 \
./bin/api_overhead_benchmark_sycl --gtest_filter=*SubmitGraph* --iterations=10000 --csv >> iwocl_results.csv

echo "SYCL No Layer:" >> iwocl_results.csv
# POCL (CPU)
# Disabling - does not work currently:
# Fails to verify module: GEP base pointer is not a vector or a vector of pointers
#ONEAPI_DEVICE_SELECTOR=opencl:0 \
#./bin/api_overhead_benchmark_sycl --gtest_filter=*SubmitGraph* --iterations=10000 --csv >> iwocl_results.csv
# OneAPI Construction Kit (CPU)
ONEAPI_DEVICE_SELECTOR=opencl:0 OCL_ICD_FILENAMES=/home/bashbaug/git/oneapi-construction-kit/build/lib/libCL.so \
./bin/api_overhead_benchmark_sycl --gtest_filter=*SubmitGraph* --iterations=10000 --csv >> iwocl_results.csv

echo "SYCL Level Zero:" >> iwocl_results.csv
# Intel(R) Level-Zero, Intel(R) Arc(TM) A750 Graphics
./bin/api_overhead_benchmark_sycl --gtest_filter=*SubmitGraph* --iterations=10000 --csv >> iwocl_results.csv
