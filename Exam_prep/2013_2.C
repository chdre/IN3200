#include <stdio.h>
#include <omp.h>

void func(double **A, int n){
	int k, j;

  #pragma omp for default(shared) private(j) schedule(static)
	{
		for(k = 0; k < n; k++) {
			for(j = 0; j < k; j++) {
				A[k][j] = A[j][k];
			}
		}
	}

	return 0;
}
