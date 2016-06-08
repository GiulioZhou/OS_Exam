//Scrivere un programma che per ogni file .c nella directory corrente chiami il compilatore gcc per generare il file oggetto (.o) a meno che esista gia' nella directory un file oggetto relativo allo stesso sorgente che sia piu' nuovo (ultima modifica) del sorgente.
//Tutti I parametri devono essere passati al compilatore.
//Es:
//genobj -I . -ggdb
//se nella directory corrente esistono I file uno.c e due.c e il file due.o deve richiamare gcc -I. -ggdb -c uno.c
//e, solo se due.o ha ultima modifica precedente a due.c, deve chiamare gcc -I. -ggdb -c due.c


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>


//returns the extension of
const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.'); //Returns a pointer to the last occurrence of character in the C string str
	if(!dot || dot == filename) return "";
	return dot + 1;
}


int main (int argc, char *argv[]){
	
	char *command[argc+3];
	int i;
	DIR* FD,*FD2;
	struct dirent* in_file,*check_o;
	struct stat f1,f2;
	time_t t1,t2;
	int found=0;
	
	//creating the base argv to pass to execvp
	command[0]="gcc";
	for(i=1;i<argc;i++){
		command[i]=argv[i];
	}
	command[argc]="-c";
	
	//open the current directory
	if (NULL == (FD = opendir ("."))){
		fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
		return -1;
	}
	
	//need for scan the directory in search of a file .o
	if (NULL == (FD2 = opendir ("."))){
		fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
		return -1;
	}
	
	//scan all the files in the directory
	while ((in_file = readdir(FD)))
	{
		//if it's not a file c, ignore
		if(strcmp(get_filename_ext(in_file->d_name),"c")) continue;
		
		//finish the command argv
		command[argc+1]=in_file->d_name;
		command[argc+2]=NULL;

		//try to find an o file with same name
		while ((check_o = readdir(FD2))) {
			if(strcmp(get_filename_ext(check_o->d_name),"o")) continue;
			if(!strncmp(in_file->d_name, check_o->d_name,strlen(in_file->d_name)-2)){
				
				found=1;
				
				//get the last mod time of the c file
				stat(in_file->d_name, &f1);
				t1 = f1.st_mtime;
				
				//get the last mod time of the o file
				stat(check_o->d_name, &f2);
				t2 = f2.st_mtime;
				printf("%s %s\n", in_file->d_name, ctime(&f1.st_mtime));
				printf("%s %s\n", check_o->d_name, ctime(&f2.st_mtime));

				if (difftime(t1,t2)>0) {
					printf("file o meno recente del sorgente\n");
					execvp(command[0],command);
				}
				else {
					printf("file o più recente\n");
					break;
				}
			}
		}
		
		//if there's no file o with same name, do the gcc
		if(!found){
			printf("nessun file o\n");
			execvp(command[0],command);
		}
		found=0;
	}
	
	return 0;
}