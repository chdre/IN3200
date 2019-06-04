#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int nargs, char** argvs) {
	int rank, num_procs, N, i, my_N, my_NN, *my_N_arr, *my_NN_arr, *displs;
	double **A, *x, *y, **A_loc, *x_loc, *y_loc;

	N = 4;

	MPI_Init(&nargs, &argvs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	my_N = N/num_procs;
	if(rank < N%num_procs)
		my_N++;

	// local arrays
	x_loc = malloc(my_N*sizeof(x_loc));
	y_loc = malloc(my_N*sizeof(y_loc));
	A_loc = calloc(my_N,sizeof(A_loc));
	A_loc[0] = calloc(my_N*N,sizeof(double));
	for(i = 1; i < my_N; i++)
		A_loc[i] = A_loc[0] + i*N;  // contigous in memory

	if(rank == 0) { // allocating x, y and A for rank 0, and filling A and x.
		my_NN_arr = malloc(num_procs*sizeof(my_NN_arr)); // for scattering A and x
		my_N_arr = malloc(num_procs*sizeof(my_N_arr));
		displs = malloc(num_procs*sizeof(displs));

		x = malloc(N*sizeof(x));
		y = malloc(N*sizeof(y));

		A = calloc(N,sizeof(A));
		A[0] = calloc(N*N,sizeof(double));
		for(i = 1; i < N; i++) {
			A[i] = A[0] + i*N; // contigous in memory
		}
		for(i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				A[i][j] = i + 1;
			}
			x[i] = i + 1;
		}
	}



	my_NN = my_N*N;
	MPI_Gather(&my_NN, 1, MPI_INT, my_NN_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gather(&my_N, 1, MPI_INT, my_N_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		// displacement for A
		displs[0] = 0;
		for(i = 0; i < num_procs-1; i++)
			displs[i+1] = displs[i] + my_NN_arr[i];
	}

	printf("here\n");
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Scatterv(A[0], my_NN_arr, displs, MPI_DOUBLE, A_loc[0], my_NN, MPI_DOUBLE,
	             0, MPI_COMM_WORLD);

	if(rank == 0) {
		// remaking displacement for x
		displs[0] = 0;
		for(i = 0; i < num_procs-1; i++)
			displs[i+1] = displs[i] + my_N_arr[i];
	}

	MPI_Scatterv(x, my_N_arr, displs, MPI_DOUBLE, x_loc, my_N, MPI_DOUBLE, 0,
	             MPI_COMM_WORLD);

	for(i = 0; i < my_N; i++) {
		printf("rank: %i, x_i = %f\n", rank, x_loc[i]);
	}

	// Matrix vector multiplication. Partial and j are declared by each process,
	// therefore they are private variables.
	for(i = 0; i < my_N; i++) {
		double partial = 0;
		for(int j = 0; j < N; j++) {
			partial += A_loc[i][j]*x_loc[j];
		}
		y_loc[i] = partial;
	}

	MPI_Gatherv(y, my_N, MPI_DOUBLE, y_loc, my_N_arr, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if(rank == 0) {
		for(i = 0; i < N; i++) {
			printf("%f\n", y[i]);
		}
	}

	if(rank == 0) {
		free(A[0]);
		free(A);
		free(x);
		free(y);
		free(my_NN_arr);
		free(my_N_arr);
		free(displs);
	}

	free(A_loc[0]);
	free(A_loc);
	free(x_loc);
	free(y_loc);

	MPI_Finalize();

	return 0;
}
