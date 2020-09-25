#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

double Euclidean_norm(double *a, int n){
	double sum = 0;
	int i;

	for(i = 0; i < n; ++)
		sum += a[i]*a[i];

	return sqrt(sum);
}

double Euclidean_norm_prll(double *a, int n) {
	double sum = 0, sum_tot = 0;
	int i, rank, size, *start_k, *stop_k;

	MPI_Init();
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	divide(n, size, rank, start_k, stop_k);

	for(i = start_k; i <= stop_k; i++) {
		sum += a[i]*a[i];
	}

	MPI_Allreduce(&sum, &sum_tot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	MPI_Finalize();

	return sqrt(sum_tot);
}
