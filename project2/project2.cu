
/*************************************************
 *  
 *  CPSC 479 Project 2: Introduction to HPC - Data Science project
 * 
 *  Student: Hamid Suha
 *  Instructor: Prof. Doina Bein
 * 
 * 
 *  Parallel sorting - Heap Sort
 * 
 *  TO COMPILE AND RUN
 *      nvcc proj2.cu
 *      ./a.out 
 * 
 * 
**************************************************/

#include <iostream>
#include <cuda_runtime.h>

__device__ void heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        // Swap arr[i] and arr[largest]
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

__global__ void heapSort(int *arr, int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Extract elements one by one from the heap
    for (int i = n - 1; i >= 0; i--) {
        // Move current root to the end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    const int arraySize = 10;
    int h_array[arraySize] = {12, 11, 13, 5, 6, 7, 2, 9, 8, 10};
    int *d_array;

    // Allocate device memory
    cudaMalloc((void**)&d_array, arraySize * sizeof(int));

    // Copy data from host to device
    cudaMemcpy(d_array, h_array, arraySize * sizeof(int), cudaMemcpyHostToDevice);

    // Example: Launch with 256 threads per block and a grid size based on array size
    int blockSize = 256;
    int gridSize = (arraySize + blockSize - 1) / blockSize;
    heapSort<<<gridSize, blockSize>>>(d_array, arraySize);

    // Copy the result back to the host
    cudaMemcpy(h_array, d_array, arraySize * sizeof(int), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(d_array);

    // Print sorted array
    std::cout << "Sorted Array: ";
    for (int i = 0; i < arraySize; i++) {
        std::cout << h_array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*************************************************
 *  
 *  Sample Output
 *  
 *  test case 1:
 *  array: {12, 11, 13, 5, 6, 7, 2, 9, 8, 10}
 *  sorted array: {2, 5, 6, 7, 8, 9, 10, 11, 12}
 * 
 *  test case 2:
 *  array: {40, 1, 12, 11, 22, 4, 13, 5, 6, 7, 2, 9, 8, 10}
 *  sorted array: 0 1 2 4 5 6 7 8 9 10 11 12 13 22 40 
 * 
 * 
**************************************************/

