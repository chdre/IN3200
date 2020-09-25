#include <stdio.h>
#include <omp.h>

double Euclidean_norm(double *a, int n){
	double sum = 0;
	int i;

	for(i = 0; i < n; ++)
		sum += a[i]*a[i];

	return sqrt(sum);
}

double Euclidean_norm_prll(double *a, int n){
	double sum = 0;
	int i;

  #pragma omp parallel for shared(a) reduction(+:sum)
	{
		for(i = 0; i < n; i++)
			sum += a[i]*a[i];
	}

	return sqrt(sum);
}
