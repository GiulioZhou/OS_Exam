//Disclaimer!! Remember to add -lrt in linking phase

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

typedef struct
{
	// Shared data
	int number;
	char buf[1024];
} shared_data;


shared_data *createShared();

shared_data *openShared();

