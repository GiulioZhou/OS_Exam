#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/types.h> 
#include "giulio_zhou-1.h"




int main(int argc, char* argv[]){
	if (argc != 3){
		fprintf(stderr, "Expected 2 parameter");
		return(EXIT_FAILURE);
	}

	int c=checkgroup(argv[1],argv[2]);

	printf("%d\n", c);
	
	return 0;
}
