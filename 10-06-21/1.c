//Scrivere un programma in linguaggio C che abbia come unico parametro il pathname di un file o di una directory.
//Il programma, usando le recenti system call inotify_init e inotify_add_watch (descritte nella pagina di manuale inotify), deve scrivere “il file e' stato aperto” ogni volta che il file viene aperto e “il file e' stato modificato” se viene modificato. Il programma deve inoltre terminare quando il file viene cancellato.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/inotify.h>
#include <sys/types.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main (int argc, char *argv[]){
	
	if(argc!=2){
		fprintf(stderr,"expected 1 parameter");
		return(EXIT_FAILURE);
	}
	
	int length, i = 0;
	int fd;
	int wd;
	char buffer[BUF_LEN];
	
	fd = inotify_init();
	
	if ( fd < 0 ) {
		perror( "inotify_init" );
	}
	
	wd = inotify_add_watch( fd, argv[1],
						   IN_MODIFY_SELF | IN_OPEN | IN_DELETE_SELF );
	length = read( fd, buffer, BUF_LEN );
	
	if ( length < 0 ) {
		perror( "read" );
	}
	
	while ( i < length ) {
		struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
		if ( event->len ) {
			if ( event->mask & IN_OPEN ) {
					printf( "Il file è stato aperto\n");
			}
			else if ( event->mask & IN_DELETE_SELF ) {
				( void ) inotify_rm_watch( fd, wd );
				( void ) close( fd );
				return 0;
				
			}
			else if ( event->mask & IN_MODIFY_SELF ) {
				printf("Il file è stato modificato\n"); //IN_MODIFY_SELF esiste?
		}
		i += EVENT_SIZE + event->len;
	}
	
	
	
	return -1;
}
