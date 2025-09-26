#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>

// Task: Parallel matrix multiplication (C = A * B) for N x N matrices (e.g., N=800).
// - Split rows of C among threads
// - Measure execution time vs single-threaded
// - Use std::vector<double> in row-major layout


void mult_block(const std::vector<std::vector<int>>& A, 
                const std::vector<std::vector<int>>& B, 
                std::vector<std::vector<int>>& C, 
                int rowStart, int rowEnd, int N) {
    for (int i = rowStart; i < rowEnd; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    const int N = 800; // Matrix size
    const int numThreads = std::thread::hardware_concurrency() ? 
                           std::thread::hardware_concurrency() : 4; 
    std::vector<double> A(N * N), B(N * N), C(N * N);
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (auto& x : A) x = dist(rng);
    for (auto& x : B) x = dist(rng);

    std::vector<std::thread> threads;
    int chunk = N / numThreads;
    auto start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < numThreads; ++t) {
        int rowStart = t * chunk;
        int rowEnd = (t == numThreads - 1) ? N : rowStart + chunk;
        threads.emplace_back(mult_block, std::ref(A), std::ref(B), std::ref(C), rowStart, rowEnd, N);
    }

    for (auto& th : threads) th.join();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Multithreaded time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " ms\n";
}