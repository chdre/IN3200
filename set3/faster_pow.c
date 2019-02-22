#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int main(){
	double x, new, x_sq, x64, x32, x4;
	int y;

	clock_t begin, end;
	double time_spent;

	x = 2.0;
	y = 100;

	begin = clock();
	for(int i = 0; i < 10000000; i++) {
		x_sq = x*x;
		x64 = x_sq*x_sq*x_sq*x_sq*x_sq*x_sq;
		x32 = x_sq*x_sq*x_sq*x_sq*x_sq;
		x4 = x_sq*x_sq;
		new = x64*x32*x4;
	}
	end = clock();
	time_spent = (double) (end - begin)/CLOCKS_PER_SEC;
	printf("%f",time_spent);

	begin = clock();
	for(int i = 0; i < 10000000; i++) {
		new = pow(x,y);
	}
	end = clock();
	time_spent = (double) (end - begin)/CLOCKS_PER_SEC;
	printf("%f",time_spent);
}
