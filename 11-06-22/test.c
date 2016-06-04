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


int main(int argc, char *argv[]){
	
	int pid = atoi(argv[1]);
	
	kill(pid,10);
	
	return 0;
}