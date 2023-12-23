/* 
Excercise 2: Compute matrix square
    # Akanksh Jagadish 885199208
    # Jorge Mejia 888533239,
    # Samee Rauf 888657053
    # Hamid Suha 886960848
// compile with: // nvcc -o ex2 excercise2.cu
*/
#include <stdio.h>
#include <cuda.h>

#define N 16

__global__ void square(unsigned *result, unsigned *matrix, unsigned matrixsize) {
    unsigned id = blockIdx.x * blockDim.x + threadIdx.x;

    unsigned ii = id / matrixsize;
    unsigned jj = id % matrixsize;

    for (unsigned kk = 0; kk < matrixsize; ++kk) {
        result[ii * matrixsize + jj] += matrix[ii * matrixsize + kk] * matrix[kk * matrixsize + jj];
    }
}

int main() {
    dim3 block(N * N, 1, 1);

    unsigned *matrix, *hmatrix, *result;

    cudaMalloc(&matrix, N * N * sizeof(unsigned));
    cudaMalloc(&result, N * N * sizeof(unsigned));

    hmatrix = (unsigned *)malloc(N * N * sizeof(unsigned));
    printf("Matrix elements:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            hmatrix[i * N + j] = 2;
            printf("%u ", hmatrix[i * N + j]);
        }
        printf("\n");
    }

    cudaMemcpy(matrix, hmatrix, N * N * sizeof(unsigned), cudaMemcpyHostToDevice);

    square<<<1, block>>>(result, matrix, N);

    cudaMemcpy(hmatrix, result, N * N * sizeof(unsigned), cudaMemcpyDeviceToHost);

    printf("Result matrix after squaring:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%u ", hmatrix[i * N + j]);
        }
        printf("\n");
    }

    // Free allocated memory on the device
    cudaFree(matrix);
    cudaFree(result);

    // Free allocated memory on the host
    free(hmatrix);

    cudaDeviceSynchronize();

    return 0;
}
