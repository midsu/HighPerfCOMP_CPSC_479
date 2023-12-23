
/* 
Two important questions that arise early in a parallel program are:
- How many processes are participating in this computation?
- Which one am I?
*/

// mpi.h must be #included
#include "mpi.h"

#include <iostream>

int main(int argc, char *argv[])

{

int rank, size;

// To become part of an MPI communicator
MPI_Init(&argc, &argv);

// reports the number of processes
MPI_Comm_rank( MPI_COMM_WORLD, &rank );

// reports the rank,a number between 0 and size-1,identifying the calling process
MPI_Comm_size( MPI_COMM_WORLD, &size );

std::cout << "I am " << rank << " of " << size << std::endl;

// To stop participating in any communicator
MPI_Finalize();

return 0;

}

/*
To build:
    mpic++ hello.cpp -o hello

To run:
    mpirun –n 2 ./hello

If it returns with an error reporting there are not enough slots available:
    mpirun -n 4 --oversubscribe ./hello
    OR:
    mpirun --oversubscribe -n 8 ./hw3   
    

OUTPUT:
I am 1 of 8
I am 2 of 8
I am 4 of 8
I am 0 of 8
I am 5 of 8
I am 3 of 8
I am 6 of 8
I am 7 of 8
--------------------------------------------------------------------------
A system call failed during shared memory initialization that should
not have.  It is likely that your MPI job will now either abort or
experience performance degradation.
*/
