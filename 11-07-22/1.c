//Scrivere il programma lanciatutto che esegua in modo concorrente tutti i file “eseguibili” della directory corrente passando ad ognuno gli stessi parametri (quelli usati nell'invocazione di lanciatutto).
//NB: eseguibili=che possono essere eseguiti, script o binari
//modo concorrente=il programma attiva tutti un processo per ogni file eseguibile (senza aspettare che termini il precedente per lanciare il successivo).
//Il programma deve terminare quando tutti i processi attivati sono terminati.
//Nota importante: In tutti gli esercizi in C e' vietato l'uso delle funzioni di libreria “system” e “popen”.


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

//returns the extension of
char *get_filename_ext(const char *filename) {
	char *dot = strrchr(filename, '.'); //Returns a pointer to the last occurrence of character in the C string str
	if(!dot || dot == filename) return "";
	return dot + 1;
}

int main (int argc, char *argv[]){
	
	DIR *FD;
	struct dirent* in_file;
	int pid;
	int count=0;

	//open the current directory
	if (NULL == (FD = opendir ("."))){
		fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
		return -1;
	}

	
	while ((in_file = readdir(FD))){
		
		if (!strcmp (in_file->d_name, "."))
			continue;
		if (!strcmp (in_file->d_name, ".."))
			continue;
		if (!strncmp(in_file->d_name, ".",1))
			continue;
		
		printf("%s\n",in_file->d_name);
		/*char *extension = get_filename_ext(in_file->d_name);
		printf("%s\n",extension);
		if(strcmp(extension,"sh")||strcmp(extension,"")){ //or other possible file
			*/if ( (pid = fork()) == -1) {
				printf("fork fail\n");
				return(EXIT_FAILURE);
			}
			
			if (pid == 0) {	//child
				
				/*execv(in_file->d_name,argv+1);
				
				perror(in_file->d_name);
				return(EXIT_FAILURE);*/
			}
			count++;
		
	}
	printf("%d",count);
	for(int i=0;i<count;i++){
		wait(NULL);
	}
	
	
	
	
	return 0;
}