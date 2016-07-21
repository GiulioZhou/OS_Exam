#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include "giulio_zhou-2.h"




int main(int argc, char* argv[]){

	char ** lista=get_user_groups();
	printf("stampa %s\n",lista[3]);
	
	free_user_groups(lista);
	printf("%s\n",lista);
	
	return 0;
}
