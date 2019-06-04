#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int nargs, char** args) {
	int size, rank, sum, psum, i;
	MPI_Status status;

	sum = psum = 0;  // sum and partial sum = 0

	MPI_Init(&nargs, &args);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for(i = 0; i < 10; i++) {
		psum += 1;//rand() % 20;
	}

	if(rank == 0) {
		sum += psum;
		for(i = 1; i < size; i++) {
			MPI_Recv(&psum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			sum += psum;
		}
	}
	else{
		MPI_Send(&psum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	if(rank == 0) {
		printf("%i\n", sum);
	}
	MPI_Finalize();

	return 0;
}
