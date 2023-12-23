'''
 CPSC 479 Problem1 part A
 Jorge Mejia, Samee Rauf, Akanksh Jagadish
 Problem 2: Ring example for sending integer 23
 command to execute program: mpiexec -n 3 python3 modified_ring.py  

'''
from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
start_time = MPI.Wtime() #start time

token = None

#Ranks other than rank 0 recieve the token value from previous ranks
if (rank != 0):
    token = comm.recv(source=rank-1)
    print(f"Rank {rank} recieved token {token} from rank {rank-1}")
#Rank 0 sets the initial token value
else:
    token = 23

#Send the token to the next rank
comm.send(token, dest=(rank + 1) % size)

#Rank 0 is handed back the token, stop timer and print results
if (rank==0):
    token = comm.recv(source=(size-1))
    end_time = MPI.Wtime() 
    execution_time = end_time - start_time
    print(f"Rank {rank} recieved token {token} from rank {rank-1} and it took {execution_time} seconds")
