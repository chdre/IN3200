#include <stdio.h>
#include <omp.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y));

void floyd(double **A, int n) {
	int i, j, k;
	double **D, **D_prev, **tmp;

	tmp = D;
	D_prev = tmp;

  #pragma omp parallel
	{
	#pragma omp for private(j)
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				D[i][j] = A[i][j];
			}
		}

  #pragma omp for private(i,j)
		for(k = 0; k < n; k++) {
			for(i = 0; i < n; i++) {
				for(j < 0; j < n; j++) {
					D[i][j] = MIN(D_prev[i][j], D_prev[i][k] + D_prev[k][j]);
				}
			}
	#pragma omp single
			tmp = D;
			D_prev = tmp;
		}
	} // end prll
}
