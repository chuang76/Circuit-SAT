all: run

run: circuit_sat
	mpiexec -n 16 circuit_sat
	mpiexec -n 8 circuit_sat 
	mpiexec -n 4 circuit_sat 
	mpiexec -n 2 circuit_sat 
	mpiexec -n 1 circuit_sat 	

circuit_sat: circuit_sat.c 
	mpiicc circuit_sat.c -o circuit_sat 

