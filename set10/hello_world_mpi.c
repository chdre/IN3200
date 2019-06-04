#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int nargs, char** args) {
	int rank, size, len, i;
	char buffer[50];
	MPI_Status status;

	MPI_Init(&nargs, &args);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	strcpy(buffer, "rank 1 out of 4");
	len = strlen(buffer)+1; // = 16

	sprintf(buffer, "rank %i out of %i\n", rank, size);

	if(rank == 0) {
		printf("rank %i out of %i\n", rank, size);
		for(i = 1; i < size; i++) {
			MPI_Recv(&buffer, len, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
			printf("This is rank %i printing: %s", rank, buffer);
		}
	}
	else{
		MPI_Send(&buffer, len, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return 0;
}
