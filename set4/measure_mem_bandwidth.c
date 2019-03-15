#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int n = 250000; // array length
	int N = 1000;

	clock_t begin, end;
	double time_spent;

	float *A = malloc(n*sizeof(float));
	float *B = malloc(n*sizeof(float));

	int s = 2;

	for(int i = 0; i < n; i++) B[i] = i;

	begin = clock();

	for(int j = 0; j < N; j++) {
		for(int i = 0; i < n; i++) A[i] = s*B[i];
	}

	end = clock();
	time_spent = (double) (end - begin)/CLOCKS_PER_SEC;

	printf("%f",time_spent);

	free(A); free(B);

}

// 8 byte * 250 000 * 1000 = 2,000,000,000

// 2e9 / /0.73 = 2,739,726,027.34 = 2.74 GB/s
// max memory bandiwth  i5-6300U = 34.1 GB/s
