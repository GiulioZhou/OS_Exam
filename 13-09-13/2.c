////Si migliori l'efficienza dell'esercizio 1.
//Prima di procedere al confronto si calcoli una chiave hash del contenuto di ogni file e si crei una struttura dati opportuna contenente tutte le chiavi hash dei file.
//Il confronto del contenuto dei file deve avvenire solo fra i file che hanno identico valore di hash.


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <dirent.h>
#include <openssl/md5.h>	//IMPORTANTE: quando si compila bisogna mettere il flag -lcrypto


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

struct md5_file{
	unsigned char hash[MD5_DIGEST_LENGTH]
	char *name;
	struct md5_file *next;
};typedef struct md5_file *list;

//head insert
void insert (list * head, char *cm, char *md)
{
	list tmp=(list)malloc(sizeof(struct md5_file));
	tmp->name = malloc(sizeof(char)*strlen(cm)+1);
	strcpy(tmp->name,cm);
	strcpy(tmp->hash, md);
	tmp->next= *head;
	*head=tmp;
}

int main (int argc, char* argv[]){
	
	if (argc!=2){
		fprintf(stderr, "Error: Expected 1 parameter.\n"
				"Usage: %s <pathname>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	
	DIR* FD1;
	struct dirent* in_file;
	list lista = NULL;
	unsigned char c[MD5_DIGEST_LENGTH];
	MD5_CTX mdContext;
	int bytes;
	unsigned char data[1024];
	FILE *inFile;
	
	chdir(argv[1]);
	
	if (NULL == (FD1 = opendir ("."))){
		fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
		return -1;
	}
	
	while ((in_file = readdir(FD1))){
		if(!strncmp(in_file->d_name,".",1)) continue;							//ignoro file nascosti
		inFile = fopen (in_file->d_name, "rb");
		MD5_Init (&mdContext);
		while ((bytes = fread (data, 1, 1024, inFile)) != 0)
			MD5_Update (&mdContext, data, bytes);
		MD5_Final (c,&mdContext);
		
		insert(&lista, in_file->d_name, c);
		
	}
	
	return 0;
}







