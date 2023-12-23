/*
Exercise 2. [ 4 points] Modify the ring example given in class to calculate 
the total communication time of sending the integer value 23 from process with 
rank 0 to process with rank 1, etc. until the value is received back at the 
process with rank 0. The program(s) needs to calculate and display the communication
 time (using MPI_Wtime) for each of the ring sizes stated below. Use only blocking 
 communication. Launch the execution of the program with a varied number of parallel
  processes (for example, mpirun -n 10 ./a.out to launch the executable a.out for 10 
  processes). Also, complete the table below as well and submit it:
*/

#include <mpi.h>
#include <iostream>
#include <ctime>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int token = 23; // Initial value to send

    double start_time, end_time, communication_time;

    start_time = MPI_Wtime();

    if (rank == 0) {
        MPI_Send(&token, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        std::cout << "Rank 0 sent the token=" << token << " to process 1." << std::endl;
        MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Recv(&token, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Rank " << rank << " has received the token=" << token << " from rank " << rank - 1 << std::endl;
        MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
        std::cout << "Rank " << rank << " sent the token=" << token << " to rank " << (rank + 1) % size << std::endl;
    }

    end_time = MPI_Wtime();
    communication_time = end_time - start_time;

    // Gather communication times from all processes
    double *all_communication_times = new double[size];
    MPI_Gather(&communication_time, 1, MPI_DOUBLE, all_communication_times, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double total_communication_time = 0.0;
    if (rank == 0) {
        std::cout << "Communication times for each process:" << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << "Rank " << i << ": " << all_communication_times[i] << " seconds" << std::endl;
            total_communication_time += all_communication_times[i];
        }
        std::cout << "Total communication time: " << total_communication_time << " seconds" << std::endl;
    }

    MPI_Finalize();
    delete[] all_communication_times;
    return 0;
}

// ----------------------------------- TABLE ----------------------------------- //
//
// ------------------------------------------------------------
//                         Execution Time                     |
// ------------------------------------------------------------
//  Ring with 3 nodes:   |              0.001497 seconds      |
// ------------------------------------------------------------
//  Ring with 6 nodes:   |              0.067744 seconds      |
// ------------------------------------------------------------
//  Ring with 9 nodes:   |              0.054453 seconds      |
// ------------------------------------------------------------
//  Ring with 12 nodes:  |              0.098697 seconds      |
// ------------------------------------------------------------



/*
To build:
    mpic++ hw2.2.cpp -o hw2.2

To run:
    mpirun –n 4 ./hw2.2

If it returns with an ERROR reporting there are not enough slots available:
    mpirun -n 4 --oversubscribe ./hw2.2
    OR:
    mpirun --oversubscribe -n 4 ./hw2.2 

*/

/*
RUN WITH:
    mpirun -n 3 ./hw2.2

OUTPUT:
    Rank 0 sent the token=23 to process 1.
    Rank 1 has received the token=23 from rank 0
    Rank 1 sent the token=23 to rank 2
    Rank 2 has received the token=23 from rank 1
    Rank 2 sent the token=23 to rank 0
    Communication times for each process:
    Rank 0: 0.00084 seconds
    Rank 1: 0.000175 seconds
    Rank 2: 0.000482 seconds
Total communication time: 0.001497 seconds
--------------------------------------------------------------------------

RUN WITH:
    mpirun -n 6 ./hw2.2

OUTPUT:
    Rank 0 sent the token=23 to process 1.
    Rank 1 has received the token=23 from rank 0
    Rank 1 sent the token=23 to rank 2
    Rank 2 has received the token=23 from rank 1
    Rank 2 sent the token=23 to rank 3
    Rank 3 has received the token=23 from rank 2
    Rank 3 sent the token=23 to rank 4
    Rank 4 has received the token=23 from rank 3
    Rank 4 sent the token=23 to rank 5
    Rank 5 has received the token=23 from rank 4
    Rank 5 sent the token=23 to rank 0
    Communication times for each process:
    Rank 0: 0.022831 seconds
    Rank 1: 0.001695 seconds
    Rank 2: 0.003343 seconds
    Rank 3: 0.008675 seconds
    Rank 4: 0.010819 seconds
    Rank 5: 0.020381 seconds
Total communication time: 0.067744 seconds
--------------------------------------------------------------------------

RUN WITH:
    mpirun -n 9 ./hw2.2

OUTPUT:
    Rank 0 sent the token=23 to process 1.
    Rank 1 has received the token=23 from rank 0
    Rank 1 sent the token=23 to rank 2
    Rank 2 has received the token=23 from rank 1
    Rank 2 sent the token=23 to rank 3
    Rank 3 has received the token=23 from rank 2
    Rank 3 sent the token=23 to rank 4
    Rank 4 has received the token=23 from rank 3
    Rank 4 sent the token=23 to rank 5
    Rank 5 has received the token=23 from rank 4
    Rank 5 sent the token=23 to rank 6
    Rank 6 has received the token=23 from rank 5
    Rank 6 sent the token=23 to rank 7
    Rank 7 has received the token=23 from rank 6
    Rank 7 sent the token=23 to rank 8
    Rank 8 has received the token=23 from rank 7
    Rank 8 sent the token=23 to rank 0
    Communication times for each process:
    Rank 0: 0.013282 seconds
    Rank 1: 0.002409 seconds
    Rank 2: 0.004516 seconds
    Rank 3: 0.001116 seconds
    Rank 4: 0.004902 seconds
    Rank 5: 0.007427 seconds
    Rank 6: 0.00917 seconds
    Rank 7: 0.005599 seconds
    Rank 8: 0.006032 seconds
Total communication time: 0.054453 seconds
--------------------------------------------------------------------------

RUN WITH:
    mpirun -n 12 ./hw2.2

OUTPUT:
    Rank 0 sent the token=23 to process 1.
    Rank 1 has received the token=23 from rank 0
    Rank 1 sent the token=23 to rank 2
    Rank 2 has received the token=23 from rank 1
    Rank 2 sent the token=23 to rank 3
    Rank 3 has received the token=23 from rank 2
    Rank 3 sent the token=23 to rank 4
    Rank 4 has received the token=23 from rank 3
    Rank 4 sent the token=23 to rank 5
    Rank 5 has received the token=23 from rank 4
    Rank 5 sent the token=23 to rank 6
    Rank 6 has received the token=23 from rank 5
    Rank 6 sent the token=23 to rank 7
    Rank 7 has received the token=23 from rank 6
    Rank 7 sent the token=23 to rank 8
    Rank 8 has received the token=23 from rank 7
    Rank 8 sent the token=23 to rank 9
    Rank 9 has received the token=23 from rank 8
    Rank 9 sent the token=23 to rank 10
    Rank 10 has received the token=23 from rank 9
    Rank 10 sent the token=23 to rank 11
    Rank 11 has received the token=23 from rank 10
    Communication times for each process:
    Rank 0: 0.016189 seconds
    Rank 1: 0.000409 seconds
    Rank 2: 0.001162 seconds
    Rank 3: 0.00172 seconds
    Rank 4: 0.004031 seconds
    Rank 5: 0.005005 seconds
    Rank 6: 0.006325 seconds
    Rank 7: 0.007711 seconds
    Rank 8: 0.010866 seconds
    Rank 9: 0.014205 seconds
    Rank 10: 0.015279 seconds
    Rank 11: 0.015795 seconds
Total communication time: 0.098697 seconds
    

--------------------------------------------------------------------------
*/