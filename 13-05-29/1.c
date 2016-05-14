//Scrivere un programma testeventfd che faccia uso della system call eventfd.
//In particolare il programma deve eseguire una fork, quando l'utente digita un numero letto dal processo padre, il processo figlio deve stampare un numero uguale di x. (negli esempi e' riportato in grassetto cio' che l'utente digita).
//$ testeventfd 3
//x
//x
//x
//2
//x
//

#include <sys/eventfd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>             /* Definition of uint64_t */



int main(){
	
	//       int eventfd(unsigned int initval, int flags);
	
	int efd = eventfd(0,0); //Provide semaphore-like semantics for reads from the new file descriptor
	int smp = eventfd(1, EFD_SEMAPHORE);
	int pid;
	uint64_t u = 1, v=1;
	int i=0;

	
	
	switch (pid=fork()) {
  case 0:
			while (1) {
				
				read(efd, &u, sizeof(uint64_t));
				for (i=0; i<u; i++){
					printf("x\n");
				}
				write(smp, &v, sizeof(uint64_t));
				
			}
			break;
			
  default:
			while (u){ //if the number in input is 0 it will end
				
				//If EFD_SEMAPHORE was specified and the eventfd counter has a nonzero value, then a read(2) returns 8 bytes containing the value 1, and the counter's value is decremented by 1
				read(smp,&v, sizeof(uint64_t));
				
				scanf("%d", &u);
				write(efd, &u, sizeof(uint64_t));
			}
			break;
			
			kill(pid,SIGTERM);
	}
	
	
	
	return 0;
}