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
	
	int efd = eventfd(0,0);
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
			while (u){
				read(smp,&v, sizeof(uint64_t));
				scanf("%d", &u);
				write(efd, &u, sizeof(uint64_t));
			}
			break;
	}
	
	
	
	return 0;
}