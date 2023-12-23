'''
 CPSC 479 Problem1 part A
 Jorge Mejia, Samee Rauf, Akanksh Jagadish
 Problem 1: Two transmissions (round trip) using blocking communication
 command to execute program: mpiexec -n 4 python3 round_trip_blocking.py  

'''
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
start_time = MPI.Wtime() #start timer

if rank == 0:
    #send the initial message
    initial_message = "Samee, Jorge, and Akanksh"
    comm.send(initial_message, dest=1)

    #recieve the final message
    final_message = comm.recv(source=1)

    #stop timer and print results
    end_time = MPI.Wtime() #stop timer
    execution_time = end_time - start_time
    print(f"Rank {rank} sent the initial message - '{initial_message}'")
    print(f"Rank {rank} received the final message - '{final_message}'")
    print(f"Round trip took {execution_time} seconds")
elif rank == 1:
    #recieve the initial message
    initial_message = comm.recv(source=0)

    #modify the initial message before sending it back
    final_message = f"Received from Rank 0: {initial_message}"
    comm.send(final_message, dest=0)

MPI.Finalize()
