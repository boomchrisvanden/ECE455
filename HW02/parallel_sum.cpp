#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <chrono>
#include <random>

/**
 * @brief 
 * 
 * @param data 
 * @param start 
 * @param end 
 * @param result 
 */
void partial_sum(const std::vector<int>& data, size_t start, size_t end, long long& result) {
    result = std::accumulate(data.begin() + start, data.begin() + end, 0LL);
}


int main() {
    const size_t dataSize = 10000000;
    const int numThreads = std::thread::hardware_concurrency() ? 
                           std::thread::hardware_concurrency() : 4;

    // generate random data
    std::vector<int> data(dataSize);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(1, 100);
    for (auto& val : data) {
        val = dis(gen);
    }

    // single threaded baseline
    auto start = std::chrono::high_resolution_clock::now();
    long long singleThreadedSum = std::accumulate(data.begin(), data.end(), 0LL);
    auto end = std::chrono::high_resolution_clock::now();

    // parallel sum
    std::vector<long long> partialResults(numThreads, 0);
    std::vector<std::thread> threads;
    size_t blockSize = dataSize / numThreads;
    threads.reserve(numThreads);

    auto parallelStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numThreads; ++i) {
        size_t startIdx = i * blockSize;
        size_t endIdx = (i == numThreads - 1) ? dataSize : startIdx * blockSize;
        threads.emplace_back(partial_sum, std::cref(data), 
                             startIdx, endIdx, 
                             std::ref(partialResults[i]));
    }

    for (auto& t : threads) {
        t.join();
    }

    long long parallelSum = std::accumulate(partialResults.begin(), partialResults.end(), 0LL);
    auto parallelEnd = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> singleThreadedDuration = end - start;
    std::chrono::duration<double> parallelDuration = parallelEnd - parallelStart;
    // print sums
    std::cout << "Baseline sum: " << singleThreadedSum
              << " Time: " << singleThreadedDuration.count() << " s\n";

    std::cout << "Parallel sum: " << parallelSum 
              << " Time: " << parallelDuration.count() << " s\n";
    return 0;
}