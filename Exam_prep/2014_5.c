#include <stdio.h>
#include <omp.h>

void gaubian_elimination(double **A, double *b, double *y) {
	int k, j, i, n;

	for(k = 0; k < n; k++) {
		for(j = 0; j < n; j++) {
			A[k][j] = A[k][j]/A[k][k];
		}
		y[k] = b[k]/A[k][k];
		A[k][k] = 1;
		for(i = k+1; i < n; i++) {
			for(j = k+1; j < n; j++) {
				A[i][j] = A[i][j] - A[i][k]*A[k][j];
			}
			b[i] = b[i] - A[i][k]*y[k];
			A[i][k] = 0;
		}
	}
	return 0;
}


void gaubian_elimination_prll(double **A, double *b, double *y){
	int k, j, i, n;

  #pragma omp parallel default(shared) private(i,j,k)
	{
		for(k = 0; k < n; k++) {
	  #pragma omp for
			for(j = 0; j < n; j++) {
				A[k][j] = A[k][j]/A[k][k];
			}
	  #pragma omp single
			{
				y[k] = b[k]/A[k][k];
				A[k][k] = 1;
			}

	  #pragma omp for
			for(i = k+1; i < n; i++) {
				for(j = k+1; j < n; j++) {
					A[i][j] = A[i][j] - A[i][k]*A[k][j];
				}
				b[i] = b[i] - A[i][k]*y[k];
				A[i][k] = 0;
			}
		}
	} // parallel end

	return 0;
}

/*
   We could parallelise inside of the k-loop, but this would cause overhead due
   to 2n spawnings of processes. Parallelising the outer loop gives the least
   overhead.

   As k increases the loops over i and j become smaller. Therefore we have a bad
   load balance if we do not parallelise the inner loops. Adding schedule(static,5)
   gives a better load balance, given that n >> 5.
 */




//
