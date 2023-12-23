'''
 CPSC 479 Problem1 part A
 Jorge Mejia, Samee Rauf, Akanksh Jagadish
 Problem 1: A single transmission using non blocking communication
 command to execute program: mpiexec -n 4 python3 single_transmission_non_blocking.py  
'''
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
start_time = MPI.Wtime() #start timer

if rank == 0:
    #Send the message
    message = "Samee, Jorge, and Akanksh"
    req_send = comm.isend(message, dest=1, tag=11)
    req_send.wait()

elif rank == 1:
    #Recieve the message
    req = comm.irecv(source=0, tag=11)
    message = req.wait()
    end_time = MPI.Wtime() #stop timer
    execution_time = end_time - start_time
    print(f"Rank {rank} recieved the message - '{message}' in {execution_time} seconds")


MPI.Finalize()