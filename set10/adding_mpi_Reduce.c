#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int nargs, char** argvs) {
	int size, rank, sum, local_sum, psum, i;

	psum = sum = 0;

	MPI_Init(&nargs, &argvs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	//local_sum = malloc(size*sizeof(local_sum));

	for(i = 0; i < 10; i++) {
		psum += 1;//rand() % 20;
	}

	MPI_Reduce(&psum, &local_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	MPI_Finalize();

	if(rank==0) printf("%i\n", local_sum);

	return 0;
}
