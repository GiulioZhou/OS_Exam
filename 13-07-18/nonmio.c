#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <poll.h>
#include <string.h>

struct list_el
{
	pid_t pid;
	char* comando;
	struct list_el* next;
};

void insert_el(struct list_el** head, char* command, pid_t id)
{
	struct list_el *new_el = malloc(sizeof(struct list_el));
	new_el->comando = malloc(sizeof(char) * strlen(command) + 1);
	strcpy(new_el->comando, command);
	new_el->next = NULL;
	new_el->pid = id;
 
 
	if(*head == NULL)
	{
		*head = new_el;
	}
	else
	{
		struct list_el* tmp = (*head)->next;
		(*head)->next = new_el;
		new_el->next = tmp;
	}
 
}

int strspl(char*** split, char* string, const char* delim)
{
	char* result;
	char* parsed = malloc(strlen(string)+1);
	char* tofree = parsed;
	int size = 2;
 
	char* ptr = string;
	while(*ptr != 0)
	{
		if(*ptr == *delim) size++;
		ptr++;
	}
 
	if(*split == NULL)
	{
		*split = malloc(sizeof(char*) * size);
	}
 
	strcpy(parsed, string);
 
	int i = 0;
	while((result = strtok(parsed, delim)) != NULL)
	{
		//subsequent calls to strtok must have NULL in the first
		//parameter
		parsed = NULL;
		
		//(*split)[i] = result;
		(*split)[i] = malloc(strlen(result) * sizeof(char) + 1);
		strcpy((*split)[i], result);
		
		i++;
	}
 
	(*split)[i] = (char*) 0;
 
	free(tofree);
	return i;
}

struct list_el* head = NULL;

char* printNamePid(pid_t pid)
{
	struct list_el* p = head;
	while(p != NULL)
	{
		if(p->pid == pid) return p->comando;
		p = p->next;
	}
	return NULL;
}

int main(int argc, char* argv[])
{
	int n;
	char *string;
	string = NULL;//malloc(MAX_BUFF * sizeof(char));
	int bytes_read;
	pid_t pid;
	char** splitargs = NULL;
	char delim = ' ';
	int nFork = 0;
	int err;
	int pipe_read = 0;
	char pipe_char = ' ';
 
	int pipefd[2];
	pipe(pipefd);
 
	struct pollfd pipe_read_poll;
	pipe_read_poll.fd = pipefd[0];
	pipe_read_poll.events = POLLIN;
 
	while((bytes_read = getline(&string,(size_t*) &n, stdin)) != 0)
	{
		if(strcmp(string, "\n") == 0) break;
		
		string[strlen(string)-1] = 0;
		strspl(&splitargs, string, &delim);
		
		pid = fork();
		switch(pid)
		{
			case -1:
				printf("Error fork: %s (%d)", strerror(errno), errno);
				exit(2);
				break;
			case 0:
				//pipe_read = read(pipefd[0], &pipe_read, 1);
				poll(&pipe_read_poll, 1, -1);
				err = execvp(splitargs[0], splitargs);
				if(err < 0)
				{
					printf("Error exec: %s (%d)", strerror(errno), errno);
					exit(1);
				}
				exit(0);
				break;
			default: //PADRE, continua pure
				nFork++;
				insert_el(&head, string, pid);
				break;
		}
		
		
		//free(splitargs); //TODO anche di tutte le stringhe all'interno
		splitargs = NULL;
	}
 
	int status = 0;
	char buf = 'g';
	char* comando = NULL;
	int ordineArrivo[nFork];
	int i = 0;
 
	write(pipefd[1], &buf, 1);
 
	while(i < nFork)
	{
		pid = wait(&status);
		ordineArrivo[i] = pid;
		i++;
	}
 
	printf("\n\n");
	for(i = 0; i < nFork; i++)
	{
		comando = printNamePid(ordineArrivo[i]);
		printf("%d : %s Terminated", i, comando);
	}
	return 0;
}