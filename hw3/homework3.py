# Homework 3

# Group Members:
    # Akanksh Jagadish 885199208
    # Jorge Mejia 888533239,
    # Samee Rauf 888657053
    # Hamid Suha 886960848
# Command to run the script with 8 processes:
    # mpiexec -n 8 python3 homework3.py 

# import libraries
from mpi4py import MPI
import argparse
import sys
import random

# init MPI communication
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# Generate the EV charging duration
charge_durations = random.randint(3,100)

temp = comm.scan(charge_durations, op=MPI.SUM) 

# Compute the number of hours
hour = int((temp-charge_durations)/60)
# Compute the number of minutes
minutes = (temp-charge_durations)%60

print(f"rank {rank} will start charging after {temp-charge_durations} minutes ({hour} hrs, {minutes} min) and will be done after {charge_durations} mins")


MPI.Finalize()
