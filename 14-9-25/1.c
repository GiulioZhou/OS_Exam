//Scrivere un programma che preso come parametro un file contenente un elenco di comandi (con I relativi parametri) li attivi tutti in esecuzione concorrente e rimanga in attesa. Quando il primo termina, vengono terminati (con segnale SIGTERM) tutti gli altri. (consiglio: puo' essere utile usare la mia libreria s2argv-execs)
// esempio: wta commands
//il file commands contiene:
//./ttest 40
//./ttest 10
//./ttest 20
//lo script ./ttest contiene:
//#!/bin/bash
//echo waiting for $1 seconds
//sleep $1
//echo done $i
//l'ouptut sara':
//waiting for 40 seconds
//waiting for 10 seconds
//waiting for 20 seconds
//done 10
//e poi basta perche' gli altri processi verranno terminati.



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64
#define MAX_LINE 1024



void split(char *command[], char line[]);


int main(int argc, char *argv[]){
	
	if (argc != 2) {
		fprintf(stderr, "Error: Expected 1 parameter.\n"
				"Usage: %s <pathname>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	
	char *path = argv[1]; //indirizzo del file da leggere
	char *cmd[MAX_ARGS]; //vettore dei parametri
	char cmdString[MAX_LINE]; //riga di codice
	FILE *f;
	pid_t *pid, winner;
	int i = 0, status;
	int fd[2];

	/* struct pollfd {
		int    fd;       // file descriptor
		short  events;   // events to look for
		short  revents;  // events returned
	 }; */
	
	struct pollfd fds;
	
	int myPgid= getpgid(getpid());
	printf("%d\n",myPgid);
	
	printf("Apro il file \n");
	f = fopen(path, "r");
	if (f == NULL){
		printf("cannot open the file\n");
		exit(EXIT_FAILURE);
	}
	
	printf("Apro la pipe \n");
	if((pipe(fd)) == -1){
		perror("Pipe");
		return(EXIT_FAILURE);
	}
	
	fds.fd = fd[0];
	fds.events=POLLIN; // Data other than high priority data may be read without blocking
	
	

	/*
	//count the number of line
	while ( fgets (cmdString, MAX_LINE, f)!=NULL){
		i++;
	}
	printf("Il numero delle righe è: %d \n", i);
	*/
	
	pid = malloc(sizeof(pid_t));
	rewind(f); //void rewind(FILE *stream) sets the file position to the beginning of the file of the given stream
	i=0;
	
	printf("Ora si fa sul serio \n");
	while ( fgets (cmdString, MAX_LINE, f)!=NULL){
		//realloc added and deleted the line counter
		pid = realloc(pid, sizeof(pid_t)*(i+1));
		printf("Il comando è %s \n", cmdString);
		if ( (pid[i] = fork()) == -1) {
			printf("fork fail\n");
			return(EXIT_FAILURE);
		}
		
		if (pid[i] == 0) {	//child
			i++;
			
			setpgid(0, 0);
			
			printf("Sono il processo %d e sto aspettando \n", i);
			poll(&fds,1,-1); //poll(struct pollfd fds[], nfds_t nfds, int timeout)
			//The nfds argument specifies the size of the fds array.
			//If timeout is -1, poll() shall block until a requested event occurs or until the call is interrupted.

			printf("Via!\n");
			split (cmd, cmdString);
			//Wait event to exec the command
			printf("sono il processo %d e sto per eseguire",pid[i]);
			// execvp(cmd[0], cmd);
			pid[i]=getpid(); //???? Can I do this??? ---> Answer: NO, these 2 line will never be execute, exept in case of error
			//printf("questo codice viene esequito? \n");
			
			perror(cmd[0]);
			return(EXIT_FAILURE);
			
		}
	}
	
	i--;
	
	printf("Do il via \n");
	//start all the processes
	write(fd[1], "g", 1); //ssize_t write(int fd, const void *buf, size_t count)
	
	printf("Aspetto... \n");
	winner = wait(&status); //pid_t wait(int *wstatus) -> wait for one child to finish
	/*
	printf("Il vincitore è %d !, ora uccido tutti :3 \n", winner);
	//kill all the processes
	while(i >= 0){
		if(pid[i] != winner){ //useless! The winner has already terminated
			kill(pid[i], SIGTERM);
		}
		--i;
	}
	
	printf("fine");
	*/
	
	
	// In theory kill(0, SIGUSR1) kill all process in the process group of the sender
	signal(SIGUSR1,SIG_IGN); //ignore, do not commit suicide!
	kill(0, SIGUSR1); // -> I don't know why it doesn't run...
	
	fclose(f);
	return 0;
}




void split(char *command[], char line[]){
	
	char *token;
	int spaces = 0;
 
	strtok(line, "\n");
	token = strtok(line, " ");
	
	while( token != NULL )
	{
		spaces++;
		command[spaces-1] = token;
		token = strtok(NULL, " ");
	}
	
	command[spaces] = NULL;
	
}
