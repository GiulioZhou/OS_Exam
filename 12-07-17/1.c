//Il programma lancian deve far attivare un programa in n copie concorrenti.
//es. lancian 10 ls -l
//deve lanciare 10 copie di “ls -l”.
//Per ogni copia la variabile di ambiente (environment) NCOPIA deve contenere un numero diverso (per la prima copia vale 0 e cosi' via fino al numero di copie -1).
//il programma lancian deve finire solo quando tutte le copie hanno terminato l'esecuzione.


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){
	
	if(argc<3){
		fprintf(stderr,"expected 1 parameter");
		return(EXIT_FAILURE);
	}
	
	
	int copie=atoi(argv[1]);
	int pid;
	char * word = strtok (argv[2], " ");
	char path[128] = "/bin/";
	strcat (path, word);
	for(int i=0;i<copie;i++){
		if ( (pid = fork()) == -1) {
			printf("fork fail\n");
			return(EXIT_FAILURE);
		}
		
		if(pid==0){
			
			char NCOPIA[10];
			sprintf(NCOPIA,"NCOPIA=%d",i);
			char *env[2]={NCOPIA,0};
			execve(path,argv+2,env);
			
			perror(path);
			return(EXIT_FAILURE);
			
		}
		
	}
	for(int i=0;i<copie;i++){
		wait(NULL);
	}
}