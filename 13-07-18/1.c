//Una gara fra processi.
//Scrivere un programma C che prenda in input (da standard input) alcune righe contenenti comandi con relativi parametri. La lista dei comandi termina quando viene inserita una riga vuota.
//A questo punto tutti i comandi vengono eseguiti in modo concorrente e deve venir stampato l'ordine di terminazione.
//(E' vietato usare system, popen o simili)
// Es.
// $ prorace
// sleep 30
// sleep 10
// sleep 20
// ls -l
// input di una riga vuota .... output di ls -l ....
// 1 arrivato: ls -l
// 2 arrivato: sleep 10
// 3 arrivato: sleep 20
// 4 arrivato: sleep 30


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <poll.h>
#include <sys/wait.h>
#include "mylib.h"

struct comList{
	char *command;
	pid_t pid;
	struct comList *next;
};typedef struct comList *list;

//head insert
void insert (list * head, char *cm, pid_t p)
{
	list tmp=(list)malloc(sizeof(struct comList));
	tmp->command = malloc(sizeof(char)*strlen(cm)+1);
	strcpy(tmp->command,cm);
	tmp->pid=p;
	tmp->next= *head;
	*head=tmp;
}

void printNamePid(pid_t pid, list head, int i)
{
	list p = head;
	while(p != NULL)
	{
		if(p->pid == pid) printf("%d: %s", i, p->command);
		p = p->next;
	}
}


int main(){
	
	list lista = NULL;
	char input[254];
	int pid;
	int count=0;
	int status;
	int fd[2]; //pipe fd for process sinc
	struct pollfd fds; //struct for poll

	
	//opening the pipe for pollin
	if((pipe(fd)) == -1){
		perror("Pipe");
		return(EXIT_FAILURE);
	}
	fds.fd = fd[0];
	fds.events=POLLIN;
	
	fgets(input,254,stdin);

	while (input[0]!='\n') {
		
		if ( (pid = fork()) == -1) {
			printf("fork fail\n");
			return(EXIT_FAILURE);
		}
		
		if (pid == 0) {	//child

			char *currComm = malloc(sizeof(char)*strlen(input));
			strcpy(currComm,input);
			poll(&fds,1,-1); //struct poll, size of fds array and -1 for block until interrupt call
							//wait until all processes are ready
			
			myexec(currComm);
			
			perror(currComm);
			return(EXIT_FAILURE);
		}
		count++;
		insert(&lista, input, pid);

		fgets(input,254,stdin);
	}
	pid_t arrival[count];
	
	//tell to all the processes to start
	write(fd[1], "g", 1);
	
	for(int i=0;i<count;i++){
		arrival[i]=wait(&status);
	}
	
	for(int i=0;i<count;i++){
		printNamePid(arrival[i], lista, i);
	}

	return 0;
}











