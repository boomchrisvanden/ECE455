#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic> 
#include <chrono> 

const int numIterations = 100000;

/**
 * @brief Increment counter with no mutex protection, leading to a race condition. 
 * 
 * @param counter 
 */
void incrementWithoutMutex(int& counter) {
    for (int i = 0; i < numIterations; ++i) {
        ++counter;
    }
}

/**
 * @brief Increment counter with mutex protection. 
 * 
 * @param counter 
 * @param mtx 
 */
void incrementWithMutex(int& counter, std::mutex& mtx) {
    for (int i = 0; i < numIterations; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }
}

/**
 * @brief Increment counter using atomic operations.
 * 
 * @param counter 
 */
void incrementWithAtomic(std::atomic<int>& counter) {
    for (int i = 0; i < numIterations; ++i) {
        counter.fetch_add(1, std::memory_order_relaxed);
    }
}

template <typename F>
int run_and_time(int T, F &&fn) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    threads.reserve(T);
    for (int i = 0; i < T; ++i) {
        threads.emplace_back(fn);
    }

    for (auto& t : threads) {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<double, std::milli>(end - start).count();
}

int main() {
    const int numThreads = std::thread::hardware_concurrency() ? 
                           std::thread::hardware_concurrency() : 4;

    const int expected = numThreads * numIterations;

    {// Scenario 1: No lock - race condition
        int counter = 0;
        auto ms = run_and_time(numThreads, [&]() { incrementWithoutMutex(counter); });
        std::cout << "No Mutex: Final counter = " << counter 
                << " (expected " << expected << "), Time = " << ms << " ms\n";
    }

    {
        // Mutex lock
        int counter = 0;
        std::mutex mtx;
        auto ms = run_and_time(numThreads, [&]() { incrementWithMutex(counter, mtx); });
        std::cout << "With Mutex: Final counter = " << counter 
                << " (expected " << expected << "), Time = " << ms << " ms\n";
    }

    {
        // atomic 
        std::atomic<int> counter(0);
        auto ms = run_and_time(numThreads, [&]() { incrementWithAtomic(counter); });
        std::cout << "With Atomic: Final counter = " << counter.load() 
                << " (expected " << expected << "), Time = " << ms << " ms\n";
    }
    return 0;
}
