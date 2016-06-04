//Scrivere un programma chiamato spy che tenga sotto controllo una directory (il cui pathname viene passato come unico paramentro), e segnali, stampandone il nome, ogni file che viene creato in tale directory.
//Si faccia uso della interfaccia inotify (leggere la pagina di manuale).
//Attenzione: il buffer per gli eventi deve avere dimensione superiore a quella della struttura inotify_event altrimento non c'e' spazio per il campo name.


#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )


int main(int argc, char *argv[]){
	
	if (argc != 2){
		fprintf(stderr, "Expected 1 parameter");
		return(EXIT_FAILURE);
	}
	
	int length, i = 0;
	int fd;
	int wd;
	char buffer[BUF_LEN];
	
	
	//	The inotify API provides a mechanism for monitoring filesystem
	//		events.  Inotify can be used to monitor individual files, or to
	//		monitor directories.  When a directory is monitored, inotify will
	//		return events for the directory itself, and for files inside the
	//			directory.
	
	fd = inotify_init();	//initializes a new inotify instance and returns a file descriptor associated with a new inotify event queue.
	
	if (wd=inotify_add_watch(fd, argv[1], IN_CREATE) == -1) { 	//adds a new watch, or modifies an existing watch
		fprintf(stderr, "inotify_init failed:%s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	
	
	while(1){
		i=0;
		length = read( fd, buffer, BUF_LEN ); //read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf, On success, the number of bytes read is returned
		
		if ( length < 0 ) {
			perror( "read" );
		}
		
		while ( i < length) {
			struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
			if ( event->len ) {
				if ( event->mask & IN_CREATE ) {
					if ( !(event->mask & IN_ISDIR) ) {
						printf( "The file %s was created.\n", event->name );
					}
				}
			}
			i += EVENT_SIZE + event->len;
		}

	}
	
	inotify_rm_watch( fd, wd );
	close( fd );
	
	return 0;
}
