#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

// int main(int argc, char const *argv[]) {
//  int i, N = 100000;
//  double u[N], v[N];
//
//  for(i = 0; i < N; i++) {
//      u[i] = 0.001*(i-N/2);
//      v[i] = 0.0;
//  }
//
//   #pragma omp parallel default(shared)
//  {
//      int time_step;
//      double *tmp;
//
//      for(time_step = 0; time_step < 1000; time_step++) {
//    #pragma omp for nowait
//          for(i = 1; i < N-1; i++)
//              v[i] = u[i-1] - 2*u[i] + u[i+1];
//
//          tmp = v;
//          v = u;
//          u = tmp;
//      }
//  }
// }

int main(int argc, char const *argv[]) {
	int i, N = 100000;
	double *u, *v, *tmp;

	u = malloc(N*sizeof(u));
	v = malloc(N*sizeof(v));

	for(i = 0; i < N; i++) {
		u[i] = 0.001*(i-N/2);
		v[i] = 0.0;
	}

  #pragma omp parallel default(shared)
	{
		int time_step;

		for(time_step = 0; time_step < 1000; time_step++) {
	  #pragma omp for
			for(i = 1; i < N-1; i++)
				v[i] = u[i-1] - 2*u[i] + u[i+1];

			// end points
			v[0] = u[0];
			v[N-1] = u[N-1];

			/* if a process is finished with for loop and does a pointer swap, other
			   procs may be working with the wrong u. */
			#pragma omp single
			tmp = *v;
			*v = *u;
			*u = tmp;
		}
	}
	return 0;
}
