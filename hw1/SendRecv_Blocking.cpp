
// Send/Receive program 

#include <mpi.h>

#include <iostream>

int main( int argc, char *argv[] )

{

int rank, size;

MPI_Init( &argc, &argv );

MPI_Comm_rank(MPI_COMM_WORLD, &rank);

MPI_Comm_size(MPI_COMM_WORLD, &size);

int number=0;

if (rank == 0) {

number = -10;

MPI_Send(&number, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);

std::cout << "Process " << rank << " has sent the value of " << number << " to process 8.\n";

}

else if (rank == 8) {

MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

std::cout << "Process " << rank << " has received the value of " << number << " from process 0.";

}

std::cout<< "Rank " << rank << " has the value number= " << number << " !\n";

MPI_Finalize();

return 0;

}

/*
To build:
    mpic++ hello.cpp -o hello

To run:
    mpirun –n 2 ./hello

If it returns with an ERROR reporting there are not enough slots available:
    mpirun -n 4 --oversubscribe ./hello
    OR:
    mpirun --oversubscribe -n 8 ./hw3 
*/

/*
Program done in class

#include <mpi.h>

#include <iostream>

int main( int argc, char *argv[] )

{

int rank, size;

MPI_Init( &argc, &argv );

MPI_Comm_rank(MPI_COMM_WORLD, &rank);

MPI_Comm_size(MPI_COMM_WORLD, &size);

int number=0;

if (rank == 8) {

number = -10;

MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

std::cout << "Process " << rank << " has sent the value of " << number << " to process 8.\n";

}

else if (rank == 0) {

MPI_Recv(&number, 1, MPI_INT, 8, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

std::cout << "Process " << rank << " has received the value of " << number << " from process 0.";

}

std::cout<< "Rank " << rank << " has the value number= " << number << " !\n";

MPI_Finalize();

return 0;

}
*/