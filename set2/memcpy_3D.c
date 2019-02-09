#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
        int nx, ny, nz;
        FILE *outfile;

        nx = ny = nz = 5;

        double ***u = malloc(sizeof(double **)*nx);  // triple pointers pr element of array length nx
        double ***v = malloc(sizeof(double **)*nx);

        for(int i = 0; i < nx; i++) {
                v[i] = malloc(sizeof(double *)*ny); // double pointers. Each element of array is itself an array, where each element again is an array
                u[i] = malloc(sizeof(double *)*ny); // double pointers. Each element of array is itself an array, where each element again is an array
                for(int j = 0; j < ny; j++) {
                        u[i][j] = malloc(sizeof(double)*nz); // pointers. Final elements of z dimension
                        v[i][j] = malloc(sizeof(double)*nz); // pointers. Final elements of z dimension
                }
        }

        for(int i = 0; i < nx; i++) {
                for(int j = 0; j < ny; j++) {
                        for(int k = 0; k < nz; k++) {
                                v[i][j][k] = 2.0 + sin(i*j*k*M_PI/((nx - 1)*(ny - 1)*(nz - 1)));
                                u[i][j][k] = 0.0;
                        }
                }
        }

        for(int i = 1; i < nx - 1; i++) {
                for(int j = 1; j < ny - 1; j++) {
                        for(int k = 1; k < nz - 1; k++) {
                                double fact = 1.0/6;
                                u[i][j][k] = v[i][j][k] + (v[i-1][j][k] + v[i][j-1][k] + v[i][j][k-1] - 6.0*v[i][j][k] + v[i+1][j][k] + v[i][j+1][k] + v[i][j][k+1])*fact;
                        }
                }
                //memcpy(v, u, sizeof(double)*nx*ny*nz);
                for(int i = 0; i < nx; i++) {
                        for(int j = 0; j < ny; j++) {
                                memcpy(v[i][j], u[i][j], sizeof(double)*nz);
                        }
                }
        }


        if((outfile = fopen("test.txt", "wb")) == NULL) {
                printf("Error! opening file");
                exit(1);
        }

        for(int i = 0; i < nx; i++) {
                for(int j = 0; j < ny; j++) {
                        for(int k = 0; k < nz; k++) {
                                fprintf(outfile, "%lf ",u[i][j][k]);
                        }
                        fprintf(outfile, " \n");
                }
                fprintf(outfile, "\n");
        }


        // deallocate 3D array
        for(int i = 0; i < nx; i++) {
                for(int j = 0; j < ny; j++) {
                        free(u[i][j]);
                        free(v[i][j]);
                }
                free(u[i]);
                free(v[i]);
        }
        free(u);
        free(v);

}
