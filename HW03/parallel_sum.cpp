#include <iostream>
#include <vector>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    long long sum = 0;
    std::vector<int> nums(ARRAY_SIZE, 2); // fill with 2s

    #pragma omp parallel for reduction(+:sum)
    for (int = 0; i < ARRAY_SIZE; ++i) {
        sum += nums[i];
    }
    std::cout << "SUM: " << sum << std::endl;
    return 0;
}