//Scrivere un programma che abbia come primo parametro un numero di segnale e come successivi parametri un comando coi rispettivi argomenti.
//Ad esempio
//sigstart 10 xclock -update 1
//sigstart deve rimanere in attesa e lanciare una istanza del comando ogni volta che riceve un segnale del tipo indicato (in questo caso SIGUSR1=10).

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>



char *command[10];

static void signalHandler (int sig, siginfo_t *siginfo, void *context)
{

	int pid;
	if ( (pid = fork()) == -1) {
		fprintf(stderr, "fork error");
	}
	
	if (pid == 0) {	//child
		execvp(command[0], command);
		fprintf(stderr, "exec error");
		
	} 	exit(0);
}


int main(int argc, char *argv[]){
	
	
	if (argc < 2){
		fprintf(stderr, "Expected at least 2 parameters");
		return(-1);
	}
	
	int j=0,i;
	int sig=atoi(argv[1]);
	struct sigaction signalStruct;
	
	int pid=getpid(); //only for test reason
	printf("my pid is: %d\n", pid);

	
	for ( i =2; i<argc;i++){
		
		command[j]=argv[i];
		j++;
	}
	command[j]=NULL;
	
	signalStruct.sa_sigaction = &signalHandler;
	signalStruct.sa_flags = SA_RESTART;

	sigaction(sig,&signalStruct,NULL);

	while(1){
	}
	
	return 0;
}
