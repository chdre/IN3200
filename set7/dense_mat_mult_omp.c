#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
/*
   Parallelising dense_mat_vec
 */



void dense_mat_vec(int m, int n, double *x, double *A, double *y){
	int i, j;

	#pragma omp for private(j) // alternativel: for(int j = 0; ...) such that it's private by declaration
	for(i = 0; i < m; i++) {
		double tmp = 0;
		for(j = 0; j < n; j++) {
			tmp += A[i*n+j]*y[j];
		}
		x[i] = tmp;
	}
}


int main(int argc, char *argv[]){
	int m, n;
	double *A, *x, *y, start, total_time, sum_y;

	n = atoi(argv[1]);
	m = atoi(argv[2]);

	A = malloc(m*n*sizeof(A));
	x = malloc(m*sizeof(x));
	y = malloc(n*sizeof(y));

	start = omp_get_wtime();

  #pragma omp parallel
	{
	  #pragma omp for
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				A[i*n+j] = j;
				y[j] = j;
			}
		}

		dense_mat_vec(m, n, x, A, y);
	} // end of parallel


	total_time = omp_get_wtime() - start;
	printf("%f\n",total_time);
	for(int i = 0; i < 15; i++) {
		printf("%f\n", x[i]);
	}

	free(A);
	free(x);
	free(y);
}
