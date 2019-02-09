/*
   Write a simple C program that compares the following hand-coded copy
   operation between two arrays

   for (i=0; i<n; i++) b[i]=a[i]

   with using the standard memcpy function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  int n = 10;
  int *arr = malloc(sizeof(int)*n);
  int *arr_2 = malloc(sizeof(int)*n);

  for(int i = 0; i < n; i++) arr[i] = i;

  memcpy(arr_2, arr, sizeof(int)*n);

  for(int i = 0; i < n; i++) printf("%i\n", arr_2[i]);

  free(arr); free(arr_2);
}
