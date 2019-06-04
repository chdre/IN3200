#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(int argc, char const *argv[]) {
	int i, N;
	double s, *a, *b;

	N = 10;
	s = 0.0;

	a = malloc(N*sizeof(a));
	b = malloc(N*sizeof(b));

	// SERIAL____________________________________________________________________
	// Code is to be optimized and parallelized
	s = 0;
	for (i=0; i<N; i++) {
		a[i] = 10.0+2*i;
		b[i] = 20.0+sin(0.1*i);
	}
	for (i=0; i<N-1; i++) {
		s += a[i];
		a[i+1] = cos(b[i]);
	}

	printf("serial s = %f\n", s);
	// SERIAL DONE_______________________________________________________________

	s = 10.0; // = a[0];

  #pragma omp parallel reduction(+:s)
	{
	  #pragma omp for
		for(i = 1; i < N-1; i++) {
			a[i] = cos(20.0 + sin(0.1*(i-1))); // b[N-1] is never used
			s += a[i];
		}
	} // end of prll

	printf("prll s = %f\n", s);

	return 0;
}
