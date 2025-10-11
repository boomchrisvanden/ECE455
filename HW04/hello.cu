#include <stdio.h>

// kernel function
__global__ void hello_world_kernel() {
    int threadId = blockIdx.x * blockDim.x + threadIdx.x;
    printf("Hello from thread %d\n", threadId);
}

int main() {
    hello_world_kernel <<<2, 4>>> ();
    cudaDeviceSynchronize();
    return 0;
}