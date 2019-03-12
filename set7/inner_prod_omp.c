#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	double start, total_time;
	int *A, *B, *C, N, i;

	N = 100000000;

	A = malloc(N*sizeof(A));
	B = malloc(N*sizeof(B));
	C = malloc(N*sizeof(C));

	for(i = 0; i < N; i++) {
		A[i] = B[i] = 1;
	}

	start = omp_get_wtime();

#pragma omp parallel for schedule(static)
	for(i = 0; i < N; i++) {
		C[i] = A[i]*B[i];
	}

	total_time = omp_get_wtime() - start;

	printf("%f\n",total_time);
	free(A); free(B); free(C);
}
