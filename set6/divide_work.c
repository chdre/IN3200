#include <stdio.h>
#include <stdlib.h>
#include "mpih."

/*   Having p processes divided by size workers. The goal is to divide the work
   such that we achieve a good load balance. The remainder of p/size will always
   be smaller than size, therefore we simply do add the remainder (rest) by
   increasing the work w for each process. */

int main(int nargs, char** argvs) {
	int size, rank;
	int p = 93;    // processes

	MPI_Init(&nargs, &argvs);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int w = p/size;

	int rest = p%size;

	if(rank < rest) w++;

	MPI_Finalize();
	return 0;
}
