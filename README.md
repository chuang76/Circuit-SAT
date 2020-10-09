# Circuit-SAT
Carry out the circuit satisfiability problem with exhaustive search in parallel.



## Circuit satisfiability problem

There are 32 input ports, each can value "1" or "0", so the program will consider $2^{32}$ combinations. <br>Let the master (process 0) allocate the tasks to the slaves, each process will execute its own job and send the result to the master. The master will receive the local results and do the summation. 



<img src="https://cs.calvin.edu/courses/cs/374/exercises/01/project/32-Bit-Circuit.png" style="zoom: 50%;" />

## Usage

- Compile

  ```
  $ mpiicc circuit_sat.c -o circuit_sat
  ```

- Execute

  ```
  $ mpiexec -n [number of processes] circuit_sat
  ```

- Plot

  ```
  $ python plot.py
  ```

  

## Results

