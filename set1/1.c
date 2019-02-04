#include <stdio.h>
#include <math.h>

int main(){
  int n = 10000; // approx of infty
  double sum = 1.0;
  int factor = -1; // sign of the next term

  for(int i = 1; i < n; i++){
    if(factor > 0) sum += (double) 1/pow(2,2*i); // check if next term is negative or positive
    if(factor < 0) sum -= (double) 1/pow(2,2*i);
    factor *= -1; // change sign of next term
  }
  printf("%f", sum);
  return 0;
}
