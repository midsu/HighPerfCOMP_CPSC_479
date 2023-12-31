// sendrecvarray3.cpp
// Send/receive an array of 3 ints

#include <stdio.h>

#include <mpi.h>

int main( int argc, char *argv[] )

{

int rank, size;

MPI_Init( &argc, &argv );

MPI_Comm_rank( MPI_COMM_WORLD, &rank );

MPI_Comm_size( MPI_COMM_WORLD, &size );

printf( "I am %d of %d\n", rank, size );

int A[3];

A[0]=A[1]=A[2]=0;

printf("Process %d has array=[%d,%d,%d]\n", rank, A[0],A[1],A[2]);

if (rank == 0) {

A[0] = A[1] = A[2] = -10;

MPI_Send(A, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);

printf("Process 0 sent array [%d,%d,%d] to process 1\n", A[0], A[1], A[2]);

} else if (rank == 1) {

MPI_Recv(A, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

printf("Process 1 received array[%d,%d,%d] from process 0\n", A[0],A[1],A[2]);

}

printf("Process %d has array=[%d,%d,%d]\n", rank, A[0],A[1],A[2]);

MPI_Finalize();

return 0; ;

}

/*
To build:
    mpic++ hello.cpp -o hello

To run:
    mpirun –n 4 ./hello

If it returns with an ERROR reporting there are not enough slots available:
    mpirun -n 4 --oversubscribe ./hello
    OR:
    mpirun --oversubscribe -n 4 ./hw3 

*/