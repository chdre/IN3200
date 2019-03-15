#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	int *arr, max, min;

	srand(time(NULL));

	arr = (int*)malloc(n);

	for(int i = 0; i < n; i++) arr[i] = rand();

	for(int i = 0; i < n; i++) printf("%i \n", arr[i]);

	for(int i = 1; i < n; i++) {
		if(arr[i-1] < arr[i]) max = arr[i];         // find max value
		if(arr[i-1] > arr[i]) min = arr[i];         // find min value
	}
	printf("\n %i \n", max);
	printf("%i \n", min);

	free(arr);     // deallocate
}
