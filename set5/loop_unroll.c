#include <stdlib.h>
#include <stdio.h>

int main(){
	int N = 70;
	int step = 4;
	int N_max = N - (N % step); // unrolled max value of N

	int **A = malloc(sizeof(int)*N);
	int *B = malloc(sizeof(int)*N);
	int *y = malloc(sizeof(int)*N);

	for(int i = 0; i < N; i++) {
		A[i] = malloc(sizeof(int)*N);
	}

	for(int j = 0; j < N-step; j++) {
		for(int i = 0; i < N-step; i+=step) {
			y[j] += A[j][i]*B[i];
			y[j+1] += A[j][i+1]*B[i+1];
			y[j+2] += A[j][i+2]*B[i+2];
			y[j+3] += A[j][i+3]*B[i+3];
		}
	}

	if((N-1) % step != 0) {
		// if there is a remainder we have an N/4 that is not an integer, must still
		// calculate the y[j]'s
		for(int j = N_max; j < N; j++) {
			for(int i = N_max; i < N; i++) {
				y[j] += A[j][i]*B[i];
			}
		}
	}
}
