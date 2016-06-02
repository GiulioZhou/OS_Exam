//Occorre scrivere due programmi: mytar myuntar.
//Mytar prende come parametro il nome di una directory e il nome di un file:
//mytar ddd ddd.mytar
//mytar crea il file indicato come secondo parametro e registra in esso tutti i file regolari presenti nella directory (ddd nell'esempio). Ogni file e' registrato nel secondo il seguente formato:
//nome del file (stringa ASCII terminata da un byte 0)
//lunghezza del file (stringa ASCII terminata da 0, la lunghezza e' registrata come stringa in rappresentazione in base 10 per non avere problemi di endianess e di ampiezza dei campi)
//contenuto del file (un numero di byte corrispondente alla lunghezza indicata sopra). Myuntar fa l'operazione inversa:
//myuntar ddd.mytar newddd
//crea la directory indicata come secondo parametro e, in essa, tutti i file registrati in ddd.mytar.
//Per provare i due programmi, al termine dell'esecuzione di due comandi simili a quelli degli esempi mostrati qui sopra per mytar e myuntar, tutti i file regolari presenti in ddd devono esistere in newddd e devono avere tutti lo stesso contenuto.
//Se create una directory ddd contenente solo file regolare l'output di “diff -R ddd newddd” deve essere vuoto.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main (int argc, char *argv[]){
	
	if (argc != 3){
		fprintf(stderr, "Expected 2 parameter");
		return(EXIT_FAILURE);
	}
	
	
	DIR* FD;
	struct dirent* in_file;
	FILE    *tarFile;
	FILE    *indirFile;
	char    buffer[BUFSIZ];
	char a;
	struct stat buf;
	
	/* Openiing common file for writing */
	tarFile = fopen(argv[2], "w");
	if (tarFile == NULL)
	{
		fprintf(stderr, "Error : Failed to open tarFile - %s\n", strerror(errno));
		
		return 1;
	}
	
	/* Scanning the in directory */
	if (NULL == (FD = opendir (argv[1])))
	{
		fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
		fclose(tarFile);
		
		return 1;
	}
	
	chdir(argv[1]);
	
	while ((in_file = readdir(FD)))
	{

		stat(in_file->d_name, &buf);
		/* we don't want current and parent directories */
		if (!strcmp (in_file->d_name, "."))
			continue;
		if (!strcmp (in_file->d_name, ".."))
			continue;
		
		
		/* Open directory entry file for common operation */
		indirFile = fopen(in_file->d_name, "r");
		if (indirFile == NULL)
		{
			fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
			fclose(tarFile);
			
			return 1;
		}
		
		const int n = snprintf(NULL, 0, "%llu", buf.st_size);
		char siz[n+1];
		int c = snprintf(siz, n+1, "%llu", buf.st_size);
		siz[n]='\0';
		fwrite(in_file->d_name , 1 , strlen(in_file->d_name) , tarFile );
		fwrite("\0" , 1 , sizeof(char) , tarFile );

		fwrite( siz, 1 , sizeof(siz) , tarFile );

		
		do {
				a = fgetc(indirFile);
				fputc(a, tarFile);
		}while (a != EOF);

		
		
		fclose(indirFile);
	}
	
	fclose(tarFile);
	
	
	return 0;
}