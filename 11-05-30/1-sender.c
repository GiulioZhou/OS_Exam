#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "shared.h"

int main(int argc, char * argv[])
{
	
	shared_data* data;
	int i;
	
	data = openShared();

	
	
	for(i=0;i<1024;i++)
		data->buf[i]='\0';
	for(i=1;i<argc;i++)
	{
		strcat(data->buf,argv[i]);
		strcat(data->buf,"\n");
	}


	kill(data->number,SIGUSR1);
	   
	return 0;
}

