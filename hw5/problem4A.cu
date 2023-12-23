/* 
Problem 4A): CUDA program to initialize an array array[] of size 8000 to all 2s in parallel.
    # Akanksh Jagadish 885199208
    # Jorge Mejia 888533239,
    # Samee Rauf 888657053
    # Hamid Suha 886960848
// compile with: // nvcc -o problem4A problem4A.cu
*/
#include <stdio.h>
#define N 8000

__global__ void add(int *a, int *b) {
    int i = blockIdx.x;
    if (i < N) {
        b[i] = 2;
}
}
int main() {
    // cpu array        
    int ha[N], hb[N];

    //device array
    int *da, *db;
    cudaMalloc((void **)&da, N*sizeof(int));
    cudaMalloc((void **)&db, N*sizeof(int));

    //initialize cpu array
    for (int i = 0; i < N; ++i){
            ha[i] = i;
        }
    // transfer input from cpu to device
    cudaMemcpy(da, ha, N*sizeof(int), cudaMemcpyHostToDevice);

    // launch GPU code

    add <<<N, 1 >>>(da, db);

    // copy output array from GPU back to CPU

   cudaMemcpy(hb, db, N*sizeof(int), cudaMemcpyDeviceToHost);

   for(int i = 0; i < N; ++i) {
        printf("element: %d : %d\n",i, hb[i]);
   }
   cudaFree(da);
   cudaFree(db);
    return 0;
}
