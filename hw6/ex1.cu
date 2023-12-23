/* 
Excercise 1 : compute even values from 2d matrix
    # Akanksh Jagadish 885199208
    # Jorge Mejia 888533239,
    # Samee Rauf 888657053
    # Hamid Suha 886960848
// compile with: // nvcc -o ex1 ex1.cu
*/
#include <stdio.h>
#include <cuda.h>

__global__ void dkernel(int *solution, unsigned *matrix) {
    unsigned id = threadIdx.x * blockDim.y + threadIdx.y;
    if (matrix[id] % 2 == 0) {
        atomicAdd(solution, 1);
    }
}

#define N 16

int main() {
    dim3 block(N, N, 1);

    unsigned *matrix, *hmatrix;
    int *solution;
    int *hsolution = (int *)malloc(sizeof(int));
    *hsolution = 0;

    cudaMalloc(&matrix, N * N * sizeof(unsigned));
    cudaMalloc(&solution, sizeof(int));

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
    cudaMemcpy(solution, hsolution, sizeof(int), cudaMemcpyHostToDevice);

    dkernel<<<1, block>>>(solution, matrix);

    cudaMemcpy(hsolution, solution, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Number of even elements: %d\n", *hsolution);

    cudaDeviceSynchronize();
    return 0;
}
