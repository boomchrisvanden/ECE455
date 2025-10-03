#include <iostream>
#include <vector>
#include <omp.h>

int main() {    
    const int n = 512;
    std::vector<std::vector<int>> A(n, std::vector<int(n, 2)); // filled with twos
    std::vector<std::vector<int>> B(n, std::vector<int(n, 3)); // filled with threes
    std::vector<std::vector<int>> C(n, std::vector<int(n, 0)); 

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum; // store individual sum. 
        }
    }
    std::cout << "C[0][0] = " << C[0][0] << std::endl;
    return 0;
}