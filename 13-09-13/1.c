//Lo scopo del programma che dovrete scrivere e' di confrontare fra loro i file di una directory, se ne trovate due (o piu') che hanno lo stesso contenuto dovete unificarli. Alla fine del processo l'elenco dei file della directory deve rimanere invariato ma i nomi dei file che avevano lo stesso contenuto devono essere link fisici che indicano lo stesso file.
//In questo esercizio si richiede che l'intero contenuto dei file venga confrontato.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <dirent.h>

off_t fsize(const char *filename) {
	struct stat st;
	
	if (stat(filename, &st) == 0){
		return st.st_size;
	}
	
	fprintf(stderr, "Cannot determine size of %s: %s\n",
			filename, strerror(errno));
	
	return -1;
} //questa funzione non la uso più

int checkStat(const char *filename1,const char *filename2) {
	struct stat st1,st2;
	
	if ((stat(filename1, &st1) == 0) && (stat(filename2, &st2) == 0)){
		if(st1.st_size != st2.st_size)return 1;
		if(st1.st_ino == st2.st_ino)return 1;
	}
	
	return 0;
}

int equal(char fname1[],char fname2[]){
	
	FILE *fp1, *fp2;
	int ch1, ch2;
	
	fp1 = fopen(fname1, "r");
	fp2 = fopen(fname2, "r");

	if (fp1 == NULL) {
		printf("Cannot open %s for reading ", fname1);
		exit(1);
	}
	if (fp2 == NULL) {
		printf("Cannot open %s for reading ", fname2);
		exit(1);
	}
	
	ch1 = getc(fp1);
	ch2 = getc(fp2);

	while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
	}
	
	fclose(fp1);
	fclose(fp2);

	if (ch1 == ch2)	return 1;
	else  return 0;

}

int main (int argc, char* argv[]){
	
	if (argc!=2){
		fprintf(stderr, "Error: Expected 1 parameter.\n"
				"Usage: %s <pathname>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	
	DIR* FD1,*FD2;
	struct dirent* in_file, *check_file;
	
	chdir(argv[1]);
	
	if (NULL == (FD1 = opendir ("."))){
		fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
		return -1;
	}
	
	if (NULL == (FD2 = opendir ("."))){
		fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
		return -1;
	}
	
	while ((in_file = readdir(FD1))){
		if(!strncmp(in_file->d_name,".",1)) continue;							//ignoro file nascosti
		while ((check_file = readdir(FD2))){
			if(!strncmp(check_file->d_name,".",1)) continue;					//ignoro file nascosti
			if(!strcmp(in_file->d_name,check_file->d_name)) continue;			//se si vuol confrontare con se stesso passo
			//if (fsize(in_file->d_name)!=fsize(check_file->d_name)) continue;	//se i file hanno dim diversa passo
			
			if (checkStat(in_file->d_name,check_file->d_name)continue;			//se i file hanno dim diversa o hanno lo stesso inode(già hard link uno dell altro) allora passo
			
			if(equal(in_file->d_name,check_file->d_name)){
				printf("File con lo stesso contenuto! %s, %s\n", in_file->d_name,check_file->d_name);
				link(in_file->d_name,check_file->d_name);
			}
		}
		rewinddir(FD2);
	}
	
	return 0;
}







