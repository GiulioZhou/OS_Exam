#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char* argv[]){
	if (argc != 2){
		fprintf(stderr, "Expected 1 parameter");
		return(EXIT_FAILURE);
	}

	return 0;
}