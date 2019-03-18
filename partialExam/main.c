#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	FILE *file;
	char *lines; // ptr to save file to
	size_t len;  // len of
	ssize_t line_len;

	len = 0;

	lines = NULL;

	file = fopen(argv[1], "r");
	if(file == NULL) {
		perror("Error (fopen)");
		return(-1);
	}

	while((line_len = getline(&lines, &len, file)) != -1) {
		printf("Writing line of length: %zu:\n", line_len);
	}






}
