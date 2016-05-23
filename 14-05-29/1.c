//Scrivere un programma con un solo parametro.
//Come prima cosa il programma deve creare una directory con il path specificato nel parametro. Se la directory esiste gia' o si verifica un errore nella creazione, il programma deve terminare. Chiameremo questa directory “directory-base”
//Il programma usando inotify rimane in attesa e stampa una riga di log per ogni file o directory creato o cancellato nella directory-base. (solo nella directory-base, non nelle sottodirectory).
//Quando viene cancellata la directory-base il programma termina.


//Getting inspiration from here https://www.ibm.com/developerworks/library/l-ubuntu-inotify/

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
	int poll=1;
	int wd;
	char buffer[BUF_LEN];
	
	//make the directory, if path is an existing directory, it terminates
	if (mkdir(argv[1], 0777) == -1) { //mkdir() attempts to create a directory named pathname.
		fprintf(stderr, "mkdir failed:%s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	
//	The inotify API provides a mechanism for monitoring filesystem
//		events.  Inotify can be used to monitor individual files, or to
//		monitor directories.  When a directory is monitored, inotify will
//		return events for the directory itself, and for files inside the
//			directory.
	
	fd = inotify_init();	//initializes a new inotify instance and returns a file descriptor associated with a new inotify event queue.
	
	if (wd=inotify_add_watch(fd, argv[1], IN_CREATE | IN_DELETE | IN_DELETE_SELF) == -1) { 	//adds a new watch, or modifies an existing watch
		fprintf(stderr, "inotify_init failed:%s\n", strerror(errno));
		return(EXIT_FAILURE);
	}
	
	
	while(poll){
		i=0;
		length = read( fd, buffer, BUF_LEN ); //read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf, On success, the number of bytes read is returned
		
		if ( length < 0 ) {
			perror( "read" );
		}
		
		while ( i < length && poll ) {
			struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
			if ( event->len ) {
				if ( event->mask & IN_CREATE ) {
					if ( event->mask & IN_ISDIR ) {
						printf( "The directory %s was created.\n", event->name );
					}
					else {
						printf( "The file %s was created.\n", event->name );
					}
				}
				else if ( event->mask & IN_DELETE ) {
					if ( event->mask & IN_ISDIR ) {
						printf( "The directory %s was deleted.\n", event->name );
					}
					else {
						printf( "The file %s was deleted.\n", event->name );
					}
				}
				else if (event->mask & IN_DELETE_SELF ) {
					printf( "Base directory deleted.\n" );
					poll=0;
				}
			}
			i += EVENT_SIZE + event->len;
		}

		
	}
	
	inotify_rm_watch( fd, wd );
	close( fd );
	
	return 0;
}
