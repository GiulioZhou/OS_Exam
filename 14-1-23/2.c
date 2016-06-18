//Scrivere un programma in C “linean” che prenda come parametro il pathname di un file e un numero intero (che chiameremo n). Il programma deve stampare come output il numero di caratteri presenti nella n-ma riga del file se il file e' un file regolare di testo, non deve stampare nulla negli altri casi. Un file viene considerato di testo se tutti i suoi byte hanno valori compresi nel range 1-127. Per controllare se il file e' “regolare” usare la system call lstat.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <dirent.h>


int main (int argc, char *argv[]){
	
	if (argc!=2){
		fprintf(stderr, "Error: Expected 1 parameter.\n"
				"Usage: %s <pathname>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	
	struct stat filestat;
	FILE *f;
	char buf[512];
	int len = 0;
	int m = atoi(argv[1]);
	int n;
	int tmp;
	int i;
	int strl;
	DIR* FD;
	struct dirent* in_file;
	int text;
	
	if (NULL == (FD = opendir ("."))){
		fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
		return -1;
	}
	
	while ((in_file = readdir(FD))){
		n=m;
		text=1;
		if(!strncmp(in_file->d_name,".",1)) continue;

		if(lstat(in_file->d_name, &filestat) == -1) {
			perror("stat");
			return errno;
		}
		
		if(S_ISREG(filestat.st_mode)){
			f = fopen(in_file->d_name, "r");
			if (f == NULL){
				perror("cannot open the file\n");
				return errno;
			}
			
			while(fgets(buf,512,f) && text){
				n--;
				strl=strlen(buf);
				if(n==0) tmp=strl;
				for (i=0;i<strl;i++){
					if (!isascii(buf[i])){
						text=0;
						break;
					}
				}
			}
			if(text) len +=tmp;
			fclose(f);

		}
	}
	printf("%d\n",len);
	
	
	return 0;
}
