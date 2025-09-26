#include <thread>
#include <iostream>
#include <vector>

/**
 * @brief print formatted message from each thread with ID and total number of threads. 
 * 
 * @param threadID 
 * @param numThreads 
 */
void threadFunction(int threadID, int numThreads); {
    std::cout << "Hello from thread " << threadID << " of " << numThreads << "\n";
}


int main() {
    const int numThreads = 4;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(threadFunction, i, numThreads);
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}