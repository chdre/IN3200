#include <stdlib.h>
#include <stdio.h>


void divide(int n, int P, int k, int *start_k, int *stop_k){
	*start_k = (n*k)/P;
	*stop_k = (n*k)/P - 1;
}


int main(int argc, char const *argv[]) {
	int n, i, P, k, *start_k = NULL, *stop_k = NULL;

	P = 3;
	n = 100;


	for(k = 0; k < P; k++) {
		divide(n, P, k, start_k, stop_k);
		printf("k = %i, start = %ls, stop = %ls\n", k, start_k, stop_k);
	}
	return 0;
}
