#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void swap(int ind, int ind2, int *vec){
	// takes two elements of vector vec and swaps the position in memory
	int temp = vec[ind];
	vec[ind] = vec[ind2];
	vec[ind2] = temp;
}

int check_sort(int *vec, int n){
	int sorted, i;

	sorted = 0;

	for(i = 0; i < n-1; i++) {
		if(vec[i+1] > vec[i]) {
			if(i == n-1) {
				sorted = 1;
				printf("Sorted has been set to 1\n");

				return sorted;
			}
			else{
				return sorted;
			}
		}
	}
}

void serial_odd_even(int n, int *a){
	int sorted, i, j;

	for(i = 0; i < n; i++) {
		sorted = check_sort(a, n);
		if(sorted == 0) {
			if(i%2 == 0) {
				for(j = 0; j < n/2; j++) {
					if(a[2*j+1] > a[2*j+2])
						swap(2*j+1, 2*j+2, a);
				}
			}
			else {
				for(j = 0; j < n/2; j++) {
					if(a[2*j] > a[2*j+1])
						swap(2*j, 2*j+1, a);
				}
			}
		}
		else{
			printf("List is sorted\n");
		}
		printf("%s\n", sorted ? "true" : "false");
	}
}

void parallel_odd_even(int n, int *a){
	int sorted = 0;
	int i, j;

	#pragma omp parallel for

	for(i = 0; i < n; i++) {
		if(sorted == 0) {
			if(i%2 == 0) {
				for(j = 0; j < n/2; j++)
					if(a[2*j+1] > a[2*j+2])
						swap(2*j+1, 2*j+2, a);
			}

			else{
				for(j = 0; j < n/2; j++)
					if(a[2*j] > a[2*j+1])
						swap(2*j, 2*j+1, a);
			}
		}
		else{
			printf("List is sorted\n");
		}
		check_sort(a, n);
	}
}


int main(int argc, char const *argv[]) {
	int *a, n;
	double start, start_prll, time, time_prll;

	n = atoi(argv[1]);
	a = malloc(n*sizeof(a));

	for(int i = 0; i < n; i++) {
		a[i] = (double) rand()/ RAND_MAX * 10;
	}

	start = clock();
	serial_odd_even(n,a);
	time = ((double) (clock() - start))/CLOCKS_PER_SEC;

	// start_prll = omp_get_wtime();
	// parallel_odd_even(n, a);
	// time_prll = omp_get_wtime() - start_prll;

	for(int i = 0; i < n; i++)
		printf("%i\n",a[i]);

	// printf("Time parallel: %f, time serial: %f\n", time_prll, time);
}
