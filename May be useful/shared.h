#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>


//Define the struct that will be shared
typedef struct
{
	int number;
	char buf[1024];
} shared_data;

//Creates a shared memory called "shared" and returns the address, if "shared" already exists, it will be deleted
shared_data *createShared();

//Open an existing shared memory and returns the adress
shared_data *openShared();

