'''
 CPSC 479 Problem1 part A
 Jorge Mejia, Samee Rauf, Akanksh
 Problem 1: A single transmission using blocking communication
 command to execute program: mpiexec -n 4 python3 single_transmission_blocking.py 

'''

from mpi4py import MPI

# Initialize MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
start_time = MPI.Wtime() #start timer

if rank == 0:
    #Send the message
    message = "Samee, Jorge, Akanksh"
    comm.send(message, dest=1)

elif rank == 1:
    #Recieve the message
    message = comm.recv(source=0)
    end_time = MPI.Wtime()  #stop timer
    execution_time = end_time - start_time
    print(f"Rank {rank} recieved the message - '{message}' in {execution_time} seconds")


MPI.Finalize()
