//Scrivere un programma in C “linean” che prenda come parametro il pathname di un file e un numero intero (che chiameremo n). Il programma deve stampare come output il numero di caratteri presenti nella n-ma riga del file se il file e' un file regolare di testo, non deve stampare nulla negli altri casi. Un file viene considerato di testo se tutti i suoi byte hanno valori compresi nel range 1-127. Per controllare se il file e' “regolare” usare la system call lstat.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

int main (int argc, char *argv[]){
	
	if (argc!=3){
		fprintf(stderr, "Error: Expected 2 parameter.\n"
				"Usage: %s <pathname>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	
	struct stat filestat;
	FILE *f;
	char buf[512];
	int len = 0;
	int n = atoi(argv[2]);
	int i;
	int strl;
	
	if(lstat(argv[1], &filestat) == -1) {
		perror("stat");
		return errno;
	}
	
	if(S_ISREG(filestat.st_mode)){
		
		f = fopen(argv[1], "r");
		if (f == NULL){
			perror("cannot open the file\n");
			return errno;
		}
		
		while(fgets(buf,512,f)){
			n--;
			strl=strlen(buf);
			if(n==0) len = strl;
			for (i=0;i<strl;i++){
				if (!isascii(buf[i])) return 0;
			}
		}
		
		printf("%d\n",len);
		
	}
	
	
	return 0;
}