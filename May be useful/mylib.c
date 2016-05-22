#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "mylib.h"

//split a string into arguments, if **command is NULL it returns only the number of token in the string
int split(char line[], char **command){
	
	int counter=0;
	char *token;
 
	strtok(line, "\n");
	token = strtok(line, " ");
	counter++;
	while( token != NULL )
	{
		if(command){
			command[counter-1] = token;
		}
		token = strtok(NULL, " ");
		counter++;
	}
	
	
	return counter;
}

void myexec (const char *line){
	
	char *buf=strdup(line);
	int argc=split(buf,NULL);
	char **command=calloc(argc+1,sizeof(char *));
	buf=strdup(line);
	split(buf,command);
	execvp(command[0], command);
	
}

