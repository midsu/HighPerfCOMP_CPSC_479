'''
 CPSC 479 Problem1 part A
 Jorge Mejia, Samee Rauf, Akanksh Jagadish
 Two transmissions (round trip) using non blocking communication
 command to execute program: mpiexec -n 4 python3 round_trip_non_blocking.py 
'''

from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
start_time = MPI.Wtime() #start timer

if rank == 0:
    #send the initial message
    initial_message = "Samee, Jorge, and Akanksh"
    req_send = comm.isend(initial_message, dest=1)
    req_send.wait()

    #recieve the final message
    req_recv = comm.irecv(source=1)
    final_message = req_recv.wait()

    #stop timer and print results
    end_time = MPI.Wtime()
    execution_time = end_time - start_time
    print(f"Rank {rank} sent the initial message - '{initial_message}'")
    print(f"Rank {rank} received the final message - '{final_message}'")
    print(f"Round trip took {execution_time} seconds")

elif rank == 1:
    #recieve the initial message
    req_recv = comm.irecv(source=0)
    initial_message = req_recv.wait()
    
    #modify the initial message before sending it back
    final_message = f"Received from Rank 0: {initial_message}"
    req_send = comm.isend(final_message, dest=0)
    req_send.wait()

MPI.Finalize()