#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
        int nx = 5;//atoi(argv[1]);
        int ny = 5;//atoi(argv[2]);
        int nz = 5;//atoi(argv[3]);


        double ***arr = malloc(nx*sizeof(double ***));
        //double ***arr = (double ***) malloc (sizeof(double ***)*ny);

        for(int i = 0; i < nx; i++) {
                arr[i] = (double **) malloc(ny*sizeof(double *));
                for(int j = 0; j < ny; j++) {
                        arr[i][j] = (double *) malloc(nz*sizeof(double));
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
                                printf("%f", arr[i][j][k]);
                        }
                }
        }
        free(arr);

        return 0;
}
