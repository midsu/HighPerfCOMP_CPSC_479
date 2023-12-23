/* 
# Akanksh Jagadish 885199208
    # Jorge Mejia 888533239,
    # Samee Rauf 888657053
    # Hamid Suha 886960848
    
commands to  compile and run file :
g++-13 -fopenmp homework4.cpp
./a.out
*/
#include <iostream>
#include<omp.h>
using namespace std;

int main (int argc, char *argv[]) {
int nthreads, tid;
/* Fork a team of threads giving them their own copies of variables */
const int n = 64;
int arr [n];
omp_set_num_threads(16);
int local_sum = 0;
int sum = 0;


#pragma omp parallel for
for (int i = 0; i < n; i++) {
    arr [i] = 1;
}

#pragma omp parallel for
for (int i = 0; i < n; i++) {
    arr [i] += 2 * i;
}

#pragma omp parallel private(local_sum) shared(sum) num_threads(8)
{
local_sum =0;
//array is distributed statically among threads, one iteration at a time
#pragma omp for schedule(static,1)
for (int i=0; i< n; i++) {
    if (arr[i] % 3 == 0){
        local_sum++;
    }
}
//each thread calculated its local_sum. ALl threads have to add to
//the global sum. It is critical that this operation is atomic.
#pragma omp critical
sum += local_sum;
}
std::cout << "The sum of values divisible by 3 in arr [] is: " << sum << std::endl; 
return 0;

}