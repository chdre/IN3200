#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int nargs, char** argvs) {
	int size, rank, sum, *local_sum, psum, i, j;

	MPI_Init(&nargs, &argvs);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	psum = sum = 0;
	local_sum = malloc(size*sizeof(local_sum));


	for(i = 0; i < 10; i++) {
		psum += 1;    //rand()%20;
	}

	MPI_Gather(&psum, 1, MPI_INT, local_sum, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		for(i = 0; i < size; i++) {
			sum += local_sum[i];
		}
	}

	MPI_Finalize();

	if(rank == 0) printf("%i\n", sum);

	free(local_sum);

	return 0;
}
