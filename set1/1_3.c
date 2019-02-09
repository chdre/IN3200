#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int nx = atoi(argv[1]);
	int ny = atoi(argv[2]);
	int nz = atoi(argv[3]);

	double ***arr = malloc(nx*sizeof(double **));

	for(int i = 0; i < nx; i++) {
		arr[i] = malloc(ny*sizeof(double *));
		for(int j = 0; j < ny; j++) {
			arr[i][j] = malloc(nz*sizeof(double));
		}
	}

	for(int i = 0; i < nx; i++) {
		for(int j = 0; j < ny; j++) {
			for(int k = 0; k < nz; k++) {
				arr[i][j][k] = (double) i*ny*nz + j*nz + k;
			}
		}
	}

	for(int i = 0; i < nx; i++) {
		for(int j = 0; j < ny; j++) {
			for(int k = 0; k < nz; k++) {
				printf("%f\n", arr[i][j][k]);
			}
		}
	}

	// deallocate 3D array
	for(int i = 0; i < nx; i++) {
		for(int j = 0; j < ny; j++) {
			free(arr[i][j]);
		}
		free(arr[i]);
	}
	free(arr);

	return 0;
}
