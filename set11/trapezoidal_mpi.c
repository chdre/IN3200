#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

double trapezoidal_serial(int n){
	double result = 0.0;
	double h = 1.0/n;
	double x;
	int i;

	x = 0.0;
	for(i = 1; i < n; i++) {
		x += h;
		result += exp(5.0*x) + sin(x) - x*x;
	}

	x = 0;
	result += 0.5*(exp(5.0*x) + sin(x) - x*x);

	x = 1;
	result += 0.5*(exp(5.0*x) + sin(x) - x*x);

	return (h*result);
}

double trapezoidal(int n, int rank, int procs) {
	int i, my_n, start, *my_n_arr, *displs;
	double result, my_result, h, x;

	my_n = n/procs;
	if(rank < n%procs)
		my_n++;

	printf("my_n: %i\n",my_n);

	my_n_arr = malloc(procs*sizeof(my_n_arr));
	displs = malloc(procs*sizeof(displs));

	MPI_Gather(&my_n, 1, MPI_INT, my_n_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

	result = my_result = 0.0;
	h = 1.0/n;



	if(rank == 0) {
		displs[0] = 0;
		for(i = 1; i < procs; i++)
			displs[i] = displs[i-1] + my_n_arr[i];
		for(i = 0; i < procs; i++) {
			printf("displs: %i\n", my_n_arr[i]);
		}
	}

	if(rank > 0) {
		start = 0;
	}
	else {
		start = 1;
	}

	x = (double) displs[rank]*h;
	printf("x: %f\n", x);

	for(i = start; i < my_n; i++) {
		x += h;
		my_result += exp(5.0*x) + sin(x) - x*x;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if(rank == 0) {
		x = 0;
		my_result += 0.5*(exp(5.0*x) + sin(x) - x*x);
		x = 1;
		my_result += 0.5*(exp(5.0*x) + sin(x) - x*x);
	}

	MPI_Reduce(&my_result, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	return (h*result);
}

int main(int nargs, char **argvs) {
	int n, procs, rank;
	double result_prll, result_srl;

	n = 10;
	result_srl = trapezoidal_serial(n);

	MPI_Init(&nargs, &argvs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);

	result_prll = trapezoidal(n, rank, procs);

	MPI_Finalize();

	printf("Rank: %i, serial: %f, parallel: %f\n", rank, result_srl, result_prll);

	return 0;
}













//
