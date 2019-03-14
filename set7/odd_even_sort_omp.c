#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

void serial_odd_even(int n, int *a){
	int temp;

	for(int i = 0; i < n; i++) {
		if(a[i]%2 == 0) {
			for(int j = 0; j < n/2 - 2; j++) {
				if(a[2*j+1] < a[2*j+2]) {
					printf("Even, %i %i \n",a[2*j+1], a[2*j+2]);
					temp = a[2*j+1];
					a[2*j+1] =  a[2*j+2];
					a[2*j+2] = temp;
					printf("Changed to, %i %i \n", a[2*j+1], a[2*j+2]);
				}
			}
		}

		else {
			for(int j = 1; j < n/2 - 2; j++) {
				if(a[2*j] < a[2*j+1]) {
					printf("Odd, %i %i \n", a[2*j], a[2*j+1]);
					temp = a[2*j];
					a[2*j] = a[2*j+1];
					a[2*j+1] = temp;
					printf("Changed to: %i %i \n", a[2*j], a[2*j+1]);

				}
			}
		}
	}
}

int main(int argc, char const *argv[]) {
	int *a, n;

	n = atoi(argv[1]);
	a = malloc(n*sizeof(a));

	for(int i = 0; i < n; i++) {
		a[i] = (double) rand()/ RAND_MAX * 10;
	}

	serial_odd_even(n,a);

	for(int i = 0; i < n; i++) {
		printf("%i\n",a[i]);
	}
}
