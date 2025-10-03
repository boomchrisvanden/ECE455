#include <vector>
#include <iostream>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    long long sum = 0;
    std::vector<int> nums(ARRAY_SIZE, 2); // fill with 2s

    for (int t = 1; t <= 8; t *= 2) {
        double start_time = omp_get_wtime();

        #pragma omp parallel for reduction(+:sum) num_threads(t)
        for (int = 0; i < ARRAY_SIZE; ++i) {
            sum += nums[i];
        }

        double end_time = omp_get_wtime();
        std::cout << "Threads: " << threads
                  << ", Time: " << t1- t0
                  << " sec, Sum: " << sum << std::endl;
    }
    
    return 0;
}