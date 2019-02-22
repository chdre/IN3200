#include <stdlib.h>
#include <stdio.h>
/*
   Write a C program that uses the following function for carrying out the
   numerical integration of 4/1+x2 between xmin and xmax using a given number
   of “slices”:

   Please verify that with xmin = 0 and xmax = 1, the numerical integration
   of 4
   1+x2
   indeed approaches π when the number of “slices” is increased.
   Suppose the floating-point division operation can not be pipelined, how
   will you use the C program to estimate the latency of a floating-point division
   in clock cycles?*/


double numerical_integration(double x_min, double x_max, int slices){
	double delta_x = (x_max - x_min)/slices;
	double x, sum = 0.0;

	for(int i = 0; i < slices; i++) {
		x = x_min + (i + 0.5)*delta_x;
		sum += 4.0/(1.0 + x*x);
	}
	return sum*delta_x;
}

int main(){
	printf("%f", numerical_integration(0, 1, 1000));
}

/*
   If the floating point operation cannot be pipelined we can estimate the latency
   by taking the cpu time of a cycle in the for loop.
 */
