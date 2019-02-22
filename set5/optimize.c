#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void foo(int N, double **mat, double **s, int *v){
	int i, j;
	double val, c;

	for(int j = 0; j < N; j++) {
		for(int i = 0; i < N; i++) {
			val = (v[j]%256);
			c = cos(val); // using sin^2 + cos^2 = 1 => sin^2 = 1 - cos^2 => sin^2 - cos^2 = 1 - cos^4
			mat[i][j] = s[i][j]*(1 - c*c*c*c);
		}
	}
}

int main(){
	int N = 100;
	double **mat, **s;
	int *v;

	mat = calloc(N, sizeof(mat[0][0]));
	s = calloc(N, sizeof(s[0][0]));
	v = calloc(N, sizeof(v[0]));

	for(int i = 0; i < N; i++) {
		mat[i] = calloc(N, sizeof(mat[0][0]));
		s[i] = calloc(N, sizeof(mat[0][0]));;
	}

	for(int i = 0; i < N; i++) {
		foo(N, mat, s, v);
	}
	for(int i = 0; i < N; i++) {
		free(mat[i]);
		free(s[i]);
	}
	free(mat);
	free(s);
	free(v);
}
