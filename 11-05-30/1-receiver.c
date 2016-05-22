//Scrivere due programmi in modo che i parametri passati al primo vengano stampati dal secondo. La comunicazione deve avvenire tramite una shared memory realizzata con la chiamata POSIX shm_open, la sincronizzazione tramite segnali. Viene attivato per primo il programma ricevente. (anche i pid dei processi possono venir scambiati attraverso la shared memory!).
//Es: scrivere in un terminale:
//	$./receiver
//l'esecuzione di “receiver rimane in attesa”. in un secondo terminale scrivere:
//	$./sender a bb ccc
//nel primo deve comparire
//	./sender
//	a
//	bb
//	ccc


//shm_open() creates and opens a new, or opens an existing, POSIX shared memory object. A POSIX shared memory object is in effect a handle which can be used by unrelated processes to mmap(2) the same region of shared memory. The shm_unlink() function performs the converse operation, removing an object previously created by shm_open().


//Trying to take ispiration here : "http://stackoverflow.com/questions/2584678/how-do-i-synchronize-access-to-shared-memory-in-lynxos-posix"


#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include "shared.h"

shared_data* data;

static void signalHandler (int sig, siginfo_t *siginfo, void *context)
{
	printf("%s",data->buf);
	exit(0);
}


int main(int argc, char * argv[])
{
	struct sigaction signalStruct;
	
	data = createShared();
	data->number=getpid();
	
	signalStruct.sa_sigaction = &signalHandler;
	sigaction(SIGUSR1,&signalStruct,NULL);

	while (1) {}
	
	
	return 0;
}

						  
						  
