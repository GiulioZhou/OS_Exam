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
	
	FILE    *tarFile;
	FILE    *indirFile;
	char a[2];
	char    buffer[BUFSIZ];
	struct stat buf;
	int dim;
	
	/* Openiing common file for reading */
	tarFile = fopen(argv[1], "r");
	if (tarFile == NULL)
	{
		fprintf(stderr, "Error : Failed to open tarFile - %s\n", strerror(errno));
		
		return 1;
	}
	
	mkdir(argv[2],0777);

	chdir(argv[2]);
	
	while (fread(&a,1,1,tarFile)) {

		strcat(buffer,a);
		while (fread(&a,1,1,tarFile) && a[0]!= '\0') { //dovrei fare più controlli ma non ho voglia ora
			strcat(buffer,a);
		}
		indirFile = fopen(buffer, "w");
		memset(buffer,0,BUFSIZ);
		
		while (fread(&a,1,1,tarFile) && a[0]!= '\0') {
			strcat(buffer,a);
		}
		dim = atoi(buffer);
		memset(buffer,0,BUFSIZ);
		
		while (fread(&a,1,1,tarFile) && a[0]!= EOF) {
			strcat(buffer,a);
		}
		fwrite(buffer,dim,1,indirFile);
		memset(buffer,0,BUFSIZ);

	}
	
	fclose(tarFile);
	
	
	return 0;
}