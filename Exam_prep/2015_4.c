#include <stdio.h>
#include <omp.h>
#include "mpi.h"

void mat_vec(int n, double **A, double *x, double *y){
	int i, j;
	double partial;

  #pragma omp parallel
	{
	#pragma omp for private(j) reduction(+: partial)
		for(i = 0; i < n; i++) {
			partial = 0;
			for(j = 0; j < n; j++) {
				partial += A[i][j]*x[j];
			}
			y[i] = partial;
		}
	} // end of parallel
}


void mat_vec_mpi(int n, double **A, double *x, double *y){
	int i, j, my_n, num_procs, size;
	double partial;

	my_n = n/num_procs;
	if(n%num_procs > rank) {
		my_n++;
	}

	MPI_Scatterv(&A, &A_loc);
	MPI_Scatterv(&x, &x_loc);

	for(i = 0; i < my_n; i++) {
		partial = 0;
		for(j = 0; j < n; j++) {
			partial_loc += A_loc[i][j]*x[j];
		}
		MPI_Reduce(&partial, &partial_loc)
		MPI_
		y_loc[i] = partial;
	}

	MPI_Gather(&y, &y_loc);
}
