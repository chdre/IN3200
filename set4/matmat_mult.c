#include <stdlib.h>
#include <stdio.h>

void initt(double **A, double **B, int n, int m, int p){
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			A[i][j] = (double) i + j;
		}
	}

	for(int i = 0; i < m; i++) {
		for(int j = 0; j < p; j++) {
			B[i][j] = (double) 2*i + j/2.0;
		}
	}
}


int main(){
	int n, m, p; // dimensions
	double **A, **B, **C; // matrices

	n = 10;
	m = 15;
	p = 20;

	A = malloc(sizeof(double)*m);
	B = malloc(sizeof(double)*p);
	C = malloc(sizeof(double)*p);

	for(int i = 0; i < m; i++) {
		A[i] = malloc(sizeof(double)*n);
	}

	for(int i = 0; i < p; i++) {
		B[i] = malloc(sizeof(double)*m);
		C[i] = malloc(sizeof(double)*n);
	}

	initt(A,B,n,m,p);


	for(int i = 0; i < n; i++) {
		for(int j = 0; j < p; j++) {
			C[i][j] += A[i][j]*B[i][j];
		}
	}


	free(A);
	free(B);
	free(C);

}
