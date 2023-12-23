/*
non-blocking communication to exchange a string value 
between processes with rank 0 and 1. We will calculate and display 
the communication time for each of the communication operations. 
*/

#include <iostream>
#include <string>
#include <mpi.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int MAX_STRING_LENGTH = 100;
    std::string message = "midsu";

    double start_time, end_time, elapsed_time;

    if (size != 2) {
        std::cerr << "This program requires exactly 2 processes." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    char received_message[MAX_STRING_LENGTH];
    MPI_Request send_request, recv_request;
    MPI_Status recv_status;

    if (rank == 0) {
        start_time = MPI_Wtime();
        MPI_Isend(message.c_str(), message.length() + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &send_request);

        MPI_Wait(&send_request, MPI_STATUS_IGNORE);

        end_time = MPI_Wtime();
        elapsed_time = end_time - start_time;
        std::cout << "Non-Blocking Isend-Irecv Time: " << elapsed_time << " seconds" << std::endl;
    } else if (rank == 1) {
        start_time = MPI_Wtime();
        MPI_Irecv(received_message, MAX_STRING_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &recv_request);

        MPI_Wait(&recv_request, &recv_status);

        end_time = MPI_Wtime();
        elapsed_time = end_time - start_time;
        std::cout << "Non-Blocking Isend-Irecv Time: " << elapsed_time << " seconds" << std::endl;
        std::cout << "Received: " << received_message << std::endl;
    }

    MPI_Finalize();
    return 0;
}

/*
To build:
    mpic++ hwQ2.cpp -o hwQ2

To run:
    mpirun –n 2 ./hwQ2

If it returns with an ERROR reporting there are not enough slots available:
    mpirun -n 2 --oversubscribe ./hwQ2
    OR:
    mpirun --oversubscribe -n 2 ./hwQ2 
*/

// ----------------------------------- TABLE ----------------------------------- //
//
// --------------------------------------------------------------------------------------------
//                                                                      Execution Time        |
// --------------------------------------------------------------------------------------------
//  A single transmission using blocking communication              |   0.001497 seconds      |
// --------------------------------------------------------------------------------------------
// A single transmission using non blocking communication           |   0.067744 seconds      |
// --------------------------------------------------------------------------------------------
// Two transmissions (round trip) using blocking communication      |   0.054453 seconds      |
// --------------------------------------------------------------------------------------------
// Two transmissions (round trip) using non blocking communication  |   0.098697 seconds      |
// --------------------------------------------------------------------------------------------

/*
OUTPUT:

Non-Blocking Isend-Irecv Time: 1.8e-05 seconds
Non-Blocking Isend-Irecv Time: 3.1e-05 seconds
Received: midsu
*/