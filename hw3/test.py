from mpi4py import MPI

# Initialize MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()

# Create an array of integers
data = rank + 1

# Perform a parallel scan operation to compute the cumulative sum
cumulative_sum = comm.scan(data, op=MPI.SUM)

# Print the result on each process
print(f"Process {rank}: Data = {data}, Cumulative Sum = {cumulative_sum}")

# Finalize MPI
MPI.Finalize()