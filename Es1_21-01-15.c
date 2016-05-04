/*
 Scrivere un programma C di nome filepipe che abbia come unico parametro il pathnae di un file di testo.
 Questo file contiene due comandi con I rispettivi parametri, uno per riga.
 Il programma deve mettere in esecuzione concorrente I due comandi in modo che l'output del primo venga fornito come input del secondo usando una pipe.
 Il programma deve terminare quando entrambi I comandi sono terminati.
 Esempio: se il file ffff contiene:
 ls -l
 tac
 il comando:
 filepipe ffff
 deve restituire lo stesso output del comando:
 ls -l | tac
 */

#include <stdio.h>
#include <stdlib.h>
#include <s2argv.h>

int main(int argc, char *argv[]) {
	
	if (argc != 2){
		fprintf(stderr, "Expected 1 parameter");
		return(EXIT_FAILURE);
	}
	FILE *f;
	int fd[2];  //fd[0] is set up for reading, fd[1] is set up for writing
	char *command = NULL;
	size_t n;
	
	//The fopen() function shall open the file whose pathname is the string pointed to by filename, and associates a stream with it. -> r stands for read only
	
	if((f = fopen(argv[1], "r")) == NULL){
		fprintf(stderr, "Cannot open the file");
		return(EXIT_FAILURE);
	}
	else{
		
		getline(&command, &n, f);
		
		if((pipe(fd)) == -1){
			perror("Pipe");
			return(EXIT_FAILURE);
		}
		else{
			
			
			switch (fork()) {
				case -1:
					
					fprintf(stderr, "Fork error");
					return(EXIT_FAILURE);
					
					break;
					
				case 0:
					
					close(fd[0]);
					
					//The dup() system call creates a copy of the file descriptor oldfd,useing the file descriptor number specified in newfd
					dup2(fd[1], STDOUT_FILENO); //redirect STDOUT to write to fd[1]->fd[0]
					execsp(command);
					return(EXIT_FAILURE); //???
					
				default:
					
					close(fd[1]);
					dup2(fd[0], STDIN_FILENO);	//redirect STDIN to read from fd[0]<-fd[1]
					wait(NULL);	//wait for child to terminate
					lseek (fd[1], 0, SEEK_SET);	//reposition STDOUT read offset to the start
					free(command);
					command = NULL;
					getline(&command, &n, f);	//get second command
					execsp(command);
					return(EXIT_FAILURE);
			}
			
		}
		
		
		
	}
	
	return 0;
}