#include <stdio.h>    
#include <limits.h>   
#include <mpi.h>

int checkCircuit (int, long);

int main(int argc, char** argv) 
{
    /*
        pid = unique id of current process
        comm_sz = max number of processes can be used 
        count = number of solutions, glocal_count = total number of solutions 
    */
    int i, pid, comm_sz, count = 0, global_count = 0, tag = 0;   
    double startTime = 0.0, totalTime = 0.0;   
    MPI_Status status; 
    
    MPI_Init(&argc, &argv);                                               // initialize 
    MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);     
    long slice = UINT_MAX / comm_sz; 
    long bits, send, recv, end;

    startTime = MPI_Wtime();                                               // start caculating the time  

    if (pid == 0) 
    {                                                 
        for (i = 1; i < comm_sz; i++) {                                    // distribute the tasks to slaves 
            send = slice * i; 
            MPI_Send(&send, 1, MPI_LONG, i, tag, MPI_COMM_WORLD); 
        }

        for (bits = 0; bits < slice; bits++)                               // execute part of tasks 
            global_count += checkCircuit(pid, bits); 

        for (i = 1; i < comm_sz; i++) {
            MPI_Recv(&count, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);   // collect the results from slaves and do the summation  
            global_count += count; 
        }
    }
    else 
    {
        MPI_Recv(&recv, 1, MPI_LONG, 0, tag, MPI_COMM_WORLD, &status); 

        if (pid == (comm_sz - 1))
          end = UINT_MAX; 
        else
          end = recv + slice; 

        for (bits = recv; bits < end; bits++)                            // execute the task (check circuit)
            count += checkCircuit(pid, bits); 

        MPI_Send(&count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);            // send the local count to master (process 0)
    }

    totalTime = MPI_Wtime() - startTime;                                 // end caculating the time, and get the duration 

    if (pid == 0) 
    {                                                         
        printf("\nA total of %d solutions were found.\n", global_count);    
        printf ("Process %d finished in time %f secs.\n", pid, totalTime);

        FILE *fp; 
        fp = fopen("result.txt", "a"); 

        if (fp == NULL)
          perror("File open error."); 

        fprintf(fp, "%d %f\n", global_count, totalTime);
        fclose(fp); 
    }

    MPI_Finalize();    

    return 0;
}


/* EXTRACT_BIT is a macro that extracts the ith bit of number n.
 *
 * parameters: n, a number;
 *             i, the position of the bit we want to know.
 *
 * return: 1 if 'i'th bit of 'n' is 1; 0 otherwise 
 */

#define EXTRACT_BIT(n,i) ( (n & (1<<i) ) ? 1 : 0)


/* checkCircuit() checks the circuit for a given input.
 * parameters: id, the id of the process checking;
 *             bits, the (long) rep. of the input being checked.
 *
 * output: the binary rep. of bits if the circuit outputs 1
 * return: 1 if the circuit outputs 1; 0 otherwise.
 */

#define SIZE 32

int checkCircuit (int id, long bits) {
   int v[SIZE];        /* Each element is a bit of bits */
   int i;

   for (i = 0; i < SIZE; i++)
     v[i] = EXTRACT_BIT(bits,i);

   if ( ( (v[0] || v[1]) && (!v[1] || !v[3]) && (v[2] || v[3])
       && (!v[3] || !v[4]) && (v[4] || !v[5])
       && (v[5] || !v[6]) && (v[5] || v[6])
       && (v[6] || !v[15]) && (v[7] || !v[8])
       && (!v[7] || !v[13]) && (v[8] || v[9])
       && (v[8] || !v[9]) && (!v[9] || !v[10])
       && (v[9] || v[11]) && (v[10] || v[11])
       && (v[12] || v[13]) && (v[13] || !v[14])
       && (v[14] || v[15]) )
       ||
          ( (v[16] || v[17]) && (!v[17] || !v[19]) && (v[18] || v[19])
       && (!v[19] || !v[20]) && (v[20] || !v[21])
       && (v[21] || !v[22]) && (v[21] || v[22])
       && (v[22] || !v[31]) && (v[23] || !v[24])
       && (!v[23] || !v[29]) && (v[24] || v[25])
       && (v[24] || !v[25]) && (!v[25] || !v[26])
       && (v[25] || v[27]) && (v[26] || v[27])
       && (v[28] || v[29]) && (v[29] || !v[30])
       && (v[30] || v[31]) ) )
   {
      printf ("%d) %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d \n", id,
         v[31],v[30],v[29],v[28],v[27],v[26],v[25],v[24],v[23],v[22],
         v[21],v[20],v[19],v[18],v[17],v[16],v[15],v[14],v[13],v[12],
         v[11],v[10],v[9],v[8],v[7],v[6],v[5],v[4],v[3],v[2],v[1],v[0]);
      fflush (stdout);
      return 1;
   } else {
      return 0;
   }
}

