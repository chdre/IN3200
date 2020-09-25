#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int nargs, char **argvs) {
	int rank, num_procs, bounce, recv, i, n;
	double start;

	MPI_Init(&nargs, &argvs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Status status;

	bounce = 1;
	n = 1000;

	start = MPI_Wtime();

	for(i = 0; i < n; i++) {
		if(rank == 0)
			MPI_Send(&bounce, 1, MPI_INT, 1, 123, MPI_COMM_WORLD);

		if(rank == 1) {
			MPI_Recv(&recv, 1, MPI_INT, 0, 123, MPI_COMM_WORLD, &status);
			MPI_Send(&bounce, 1, MPI_INT, 0, 321, MPI_COMM_WORLD);
		}

		if(rank == 0)
			MPI_Recv(&recv, 1, MPI_INT, 1, 321, MPI_COMM_WORLD, &status);
	}

	if(rank == 0)
		printf("Time for %i runs: %f, operations/time: %f\n", n, MPI_Wtime() - start, 2*n/(MPI_Wtime() - start));
	MPI_Finalize();

	return 0;
}
