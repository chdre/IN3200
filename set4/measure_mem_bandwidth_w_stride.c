#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int n = 250000; // array length
	int N = 1000;

	int stride = 4;

	clock_t begin, end;
	double time_spent;

	float *A = malloc(n*sizeof(float));
	float *B = malloc(n*sizeof(float));

	int s = 2;

	for(int i = 0; i < n; i++) B[i] = i;

	begin = clock();

	for(int j = 0; j < N; j++) {
		for(int i = 0; i < n; i+=stride) {
			A[i] = s*B[i];
			//A[i+1] = s*B[i+1];
			//A[i+2] = s*B[i+2];
			//A[i+3] = s*B[i+3];
		}
	}

	end = clock();
	time_spent = (double) (end - begin)/CLOCKS_PER_SEC;

	printf("%f",time_spent);

	free(A); free(B);

}

// 8 byte * 250 000 * 1000 = 2,000,000,000

// 2e9 / /0.70 = 2,857,142,857.14 = 2.85 GB/s
// max memory bandiwth  i5-6300U = 34.1 GB/s

/*
   8 byte * 250 000 * 1000 / 4 = 0.5e9
   0.5e9/.2 = 2.5e9 = 2.5 GB/s
 */
