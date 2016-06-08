//Una gara fra processi.
//Scrivere un programma C che prenda in input (da standard input) alcune righe contenenti comandi con relativi parametri. La lista dei comandi termina quando viene inserita una riga vuota.
//A questo punto tutti i comandi vengono eseguiti in modo concorrente e deve venir stampato l'ordine di terminazione.
//(E' vietato usare system, popen o simili)
// Es.
// $ prorace
// sleep 30
// sleep 10
// sleep 20
// ls -l
// input di una riga vuota .... output di ls -l ....
// 1 arrivato: ls -l
// 2 arrivato: sleep 10
// 3 arrivato: sleep 20
// 4 arrivato: sleep 30


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "mylib.h"

struct comList{
	const char *command;
	struct comList *next;
};typedef struct comList *list;

list insert (list head, const char *cm)
{
	
	if(head==NULL) {
		head =(list)malloc(sizeof(list));
		head->command = cm;
		head->next=NULL;

	}	else{
		list tmp = head;
		while (tmp->next != NULL) tmp=tmp->next;
		tmp->next=(list)malloc(sizeof(list));
		tmp=tmp->next;
		tmp->command = cm;
		tmp->next=NULL;

	}
	return head;
}

void print (list lista){
	
	while (lista!=NULL) {
		printf("%s\n", lista->command);
		lista=lista->next;
	}
}

int main(){
	
	list lista = NULL;
	char input[254];
	
	fgets(input,254,stdin);
	while (input[0]!='\n'){
		lista=insert(lista, input);
		printf("%s", lista->command);
		fgets(input,254,stdin);
	}
	
	printf("%s\n", lista->command);
	print(lista);
	printf("%s\n", lista->command);


}