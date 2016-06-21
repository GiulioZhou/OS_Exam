//Scrivere un programma che inverta i byte di un file: il file primo byte del file in output sia l'ultimo del file in input, il secondo in output sia il penultimo dell'input e cosi' via. Il programma deve operare su file di ogni dimensione usando un buffer di 4K byte.
//(usare stat o fstat per leggere la dimensione del file, leggere blocchi da 4k con pread, invertirli localmente e scriverli nella posizione giusta nel nuovo file con pwrite).
//Sintassi: inverti file_input file_output.
//Se si vuole creare un file con 1MB di dati random per fare una prova usare:
//dd if=/dev/urandom of=file_input bs=1024 count=1024
//applicando inverti due volte al file casuale deve tornare il file dato.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 4096


void invert (char buf[])


int main(int argc, char* argv[]){

	if (argc != 3){
		fprintf(stderr, "Expected 2 parameter");
		return(EXIT_FAILURE);
	}

	FILE    *inputFile;
	FILE    *outputFile;
	char    buffer[BUF_SIZE];

	outputFile = fopen(argv[2], "w");
	if (outputFile == NULL)	{
		fprintf(stderr, "Error : Failed to open tarFile - %s\n", strerror(errno));
		return 1;
	}

	inputFile = fopen(argv[1], "r");
	if (outputFile == NULL)	{
		fprintf(stderr, "Error : Failed to open tarFile - %s\n", strerror(errno));
		return 1;
	}

	invert(inputFile,outputFile);
	

	
	return 0;
}
