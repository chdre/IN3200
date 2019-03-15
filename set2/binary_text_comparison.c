/* Write a simple C program that illustrates the speed advantages of reading
   and writing binary data files, compared with using ASCII data files. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void binary_write(){
	FILE *fptr;     // defining file fptr

	clock_t begin, end;
	double time_spent;

	if((fptr = fopen("test.bin", "wb")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}

	begin = clock();
	for(int n = 1; n < 100000000; n++) {
		fwrite(&n, 1, 1, fptr);
	}
	end = clock();
	time_spent = (double) (end - begin)/CLOCKS_PER_SEC;

	fclose(fptr);

	printf("%lf \n", time_spent);
}

void text_write(){
	FILE *fptr;     // defining file fptr

	clock_t begin, end;
	double time_spent;

	if((fptr = fopen("test.txt", "wb")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}

	begin = clock();

	for(int n = 1; n < 100000000; n++) {
		fprintf(fptr, "%i\n", n);
	}
	end = clock();
	time_spent = (double) (end-begin)/CLOCKS_PER_SEC;

	fclose(fptr);

	printf("%lf \n", time_spent);
}

void read_binary(){
	FILE *fptr;     // defining file fptr

	clock_t begin, end;
	double time_spent;

	begin = clock();

	if((fptr = fopen("test.bin", "r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	end = clock();
	time_spent = (double) (end-begin)/CLOCKS_PER_SEC;

	fclose(fptr);

	printf("%lf \n", time_spent);

}

void read_text() {
	FILE *fptr;     // defining file fptr

	clock_t begin, end;
	double time_spent;

	begin = clock();

	if((fptr = fopen("test.txt", "r")) == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	end = clock();
	time_spent = (double) (end-begin)/CLOCKS_PER_SEC;

	fclose(fptr);

	printf("%lf \n", time_spent);

}

int main(){
	binary_write();
	text_write();
	read_binary();
	read_text();

	return 0;
}
