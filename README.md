# Circuit-SAT
Carry out the circuit satisfiability problem with exhaustive search in parallel.



## Circuit satisfiability problem

There are 32 input ports, each can value "1" or "0", so the program will consider $2^{32}$ combinations. <br>Let the master (process 0) allocate the tasks to the slaves, each process will execute its own job and send the result to the master. The master will receive the local results and do the summation. 



<img src="https://cs.calvin.edu/courses/cs/374/exercises/01/project/32-Bit-Circuit.png" width="500" height="290" />

## Policy 

For the master (root, process 0), distribute the data which should be calculated to the salves. The slaves (process 1 - N) calculate the local result via `checkCircuit()` function first, then use `MPI_Send()` to send the local result to the master. The master uses `MPI_Recv()` to collect all the local results and does the summation. 

- Other algorithms: tree structure, butterfly structure 



## Usage

- Compile and execute 

  ```
  mpiicc circuit_sat.c -o circuit_sat
  mpiexec -n [number of processes] circuit_sat
  ```

- Plot

  ```
  python plot.py
  ```

  

## Results

- Solution: 1,179,567 combinations
- Performance

<img src="https://github.com/chuang76/Circuit-SAT/blob/main/result.png?raw=true" width="400" height="320" />
