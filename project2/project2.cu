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
    const int arraySize = 8;
        int h_array[arraySize] = {25, 33, 70, 102, 56, 9, 11, 32};
            int *d_array;
        std::cout << "Unsorted array: ";
                  for (int j = 0; j < arraySize; j++){
                  std::cout << h_array[j] << " ";
                  }
        std::cout << "\n";
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
