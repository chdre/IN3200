#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

/*
   Not parallelising dense_mat_vec

   Since we are not allowed to change the dense_mat_vec function, but still
   are to parallelise it, we must manually parallelise it by specifying the
   region of the outer for loop (i = 0; i < m) for each thread.
 */

void dense_mat_vec(int start, int stop, int n, double *x, double *A, double *y){
	for(int i = start; i < stop; i++) {
		double tmp = 0;
		for(int j = 0; j < n; j++) {
			tmp += A[i*n+j]*y[j];
		}
		x[i] = tmp;
	}
}

int main(int argc, char *argv[]){
	int m, n, start, num_threads, stop, len;
	double *A, *x, *y, start_time, total_time, sum_y;

	n = atoi(argv[1]);
	m = atoi(argv[2]);

	A = malloc(m*n*sizeof(A));
	x = malloc(m*sizeof(x));
	y = malloc(n*sizeof(y));

	start_time = omp_get_wtime();

  #pragma omp parallel
	{
		int thread_id; // must remain private


		num_threads = omp_get_num_threads();
		thread_id = omp_get_thread_num();

		len = m/num_threads;

	  #pragma omp for
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < n; j++) {
				A[i*n+j] = j;
				y[j] = j;
			}
		}

		start = thread_id*len;
		stop = thread_id*len + len;

		dense_mat_vec(start, stop, n, x, A, y);
	} // end of parallel

	total_time = omp_get_wtime() - start_time;
	printf("%f\n",total_time);
	for(int i = 0; i < 15; i++) {
		printf("%f\n", x[i]);
	}

	free(A);
	free(x);
	free(y);
}
