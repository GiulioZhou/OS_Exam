//Scrivere un programma che crei un processo figlio. Il processo genitore e il processo figlio devono essere collegati da due pipe, una per la comunicazione genitore- figlio, una per la comunicazione figlio-genitore. Il processo figlio deve rispedire al genitore ogni messaggio ricevuto dalla pipe di input nell'altra (echo). Il processo genitore deve per 100000 volte spedire un messaggio di 40 byte al processo figlio e aspettare da questo che il messaggio venga rispedito.
//Scopo dell'esercizio e' di verficare quanto tempo viene impiegato per il “ping” di 100000 messaggi su pip

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

int main(){
	int parent_fd[2];
	int child_fd[2];
	int pid;
	char mess[40];
	char parReadbuff[40];
	char childReadbuff[40];
	int i;
	struct timeval tval_before, tval_after, tval_result;
	
	if((pipe(parent_fd)) == -1){
		perror("Parent Pipe");
		return(EXIT_FAILURE);
	}
	if((pipe(child_fd)) == -1){
		perror("Child Pipe");
		return(EXIT_FAILURE);
	}

	memset(mess,1,40);
	pid=fork();
	if(pid==0){
		
		close(parent_fd[1]);
		close(child_fd[0]);
		while(1){
			
			if(read(parent_fd[0],childReadbuff,40)==-1) {
				printf("Oh dear, something went wrong with child read()! %s\n", strerror(errno));
			}
			if(write(child_fd[1],childReadbuff,40)==-1){
				printf("Oh dear, something went wrong with child write()! %s\n", strerror(errno));
			}
		}
	}
	else{
		close(parent_fd[0]);
		close(child_fd[1]);
		
		gettimeofday(&tval_before, NULL); //begin message passing time
		for(i=0;i<100000;i++){
			if(write(parent_fd[1],mess,40)==-1){
				
				printf("Oh dear, something went wrong with child write()! %s\n", strerror(errno));
			}
			if(read(child_fd[0],parReadbuff,40)==-1){
				printf("Oh dear, something went wrong with parent read()! %s\n", strerror(errno));
			}


		}
		gettimeofday(&tval_after, NULL); //end message passing
		
		timersub(&tval_after, &tval_before, &tval_result);

		printf("Ping: %ld sec and %06ld usec\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
		
		kill(pid,SIGTERM);

	}
	
	return 0;
}