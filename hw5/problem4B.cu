/* 
Problem 4B): Create another kernel that adds i to array[i] with a size of 8000
    # Akanksh Jagadish 885199208
    # Jorge Mejia 888533239,
    # Samee Rauf 888657053
    # Hamid Suha 886960848
// compile with: // nvcc -o problem4B problem4B.cu
*/
#include <stdio.h>

#define N 8000

__global__ void initialize(int *a, int *b) {
    int i = blockIdx.x;
    if (i < N) {
        b[i] = 2;
        }
}
__global__ void add(int *a, int *b) {
    int i = blockIdx.x;
    if (i < N) {
        b[i] = b[i] + i;
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

    initialize <<<N, 1 >>>(da, db);

    // copy output array from GPU back to CPU

   cudaMemcpy(hb, db, N*sizeof(int), cudaMemcpyDeviceToHost);

   for(int i = 0; i < N; ++i) {
        printf("element: %d : %d\n",i, hb[i]);
   }

   add <<< N,1 >>>(da, db);
   cudaMemcpy(hb, db, N*sizeof(int), cudaMemcpyDeviceToHost);
   printf("\nvaleues of array after adding i : \n");
   for(int i = 0; i < N; ++i) {
        printf("element: %d : %d\n",i, hb[i]);
   }
   cudaFree(da);
   cudaFree(db);
    return 0;
}
