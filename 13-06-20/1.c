//Scrivere un programma che stampi il numero di inode di ogni file presente in una direcotory passata come argomento (o della direcotry corrente se il programma viene chiamato senza parametri) e stampi l'elenco in ordine crescente di numero di i-node.
//Es:
//$ lsino demo
//demo/. 1972484
//demo/.. 1971834
//demo/1.c 1972528
//demo/a.out 1972485
//demo/l1 1972486
//demo/l2 1972486
//demo/l3 1972486
//demo/link.c 1972528




#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

struct node
{
	int inodenum;
	char name[1024];
};





void merge(struct node a[], int left, int center, int right)
{
	int i, j, k;
	//vettore di appoggio
	struct node b[100]; //se questo array è troppo piccolo non funziona
	i = left;
	j = center+1;
	k = 0;
	//fusione delle 2 meta'
	while ((i<=center) && (j<=right))
	{
		if (a[i].inodenum <= a[j].inodenum)
		{
			b[k] = a[i];
			i++;
		}
		else
		{
			b[k] = a[j];
			j++;
		}
		k++;
	}
	
	//se i e' minore di center significa che alcuni elementi
	//della prima meta' non sono stati inseriti nel vettore
	while (i<=center)
	{
		//allora li aggiungo in coda al vettore
		b[k] = a[i];
		i++;
		k++;
	}
 
	//se j a' minore di right significa che alcuni elementi
	//della seconda meta' non sono stati inseriti nel vettore
	while (j<=right)
	{
		//allora li aggiungo in coda al vettore
		b[k] = a[j];
		j++;
		k++;
	}
 
	//alla fine copio il vettore di appoggio b nel vettore a
	for (k=left; k<=right; k++)
	{
		a[k] = b[k-left];
	}
}

void mergesort(struct node a[], int left, int right)
{
	//indice dell'enemento mediano
	int center;
	//se ci sono almeno di 2 elementi nel vettore
	if(left<right)
	{
		//divido il vettore in 2 parti
		center = (left+right)/2;
		//chiamo la funzione per la prima meta'
		mergesort(a, left, center);
		//chiamo la funzione di ordinamento per la seconda meta'
		mergesort(a, center+1, right);
		//chiamo la funzione per la fusione delle 2 meta' ordinate
		merge(a, left, center, right);
	}
}

int main (int argc, char *argv[]){
	
	if (argc != 2){
		fprintf(stderr, "Expected 1 parameter");
		return(-1);
	}
	
	
	DIR* FD;
	struct dirent* in_file;
	int count=0;
	int i=0;

	
	/* Scanning the in directory */
	if (NULL == (FD = opendir (argv[1])))
	{
		fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
		
		return -1;
	}
	
	chdir(argv[1]);
	
	while ((in_file = readdir(FD)))
	{
		count++;
	}
	
	struct node nodeArray[count];
	rewinddir(FD);
	
	while ((in_file = readdir(FD)))
	{

		memset(nodeArray[i].name,0,1024); //Need to reset the name, without it there may be some rubbish in memory
		//Insert every file name-ino in a list
		strcat(nodeArray[i].name, argv[1]);
		strcat(nodeArray[i].name, "/");
		strcat(nodeArray[i].name, in_file->d_name);
		nodeArray[i].inodenum=in_file->d_ino;
		i++;
	}
	
	mergesort(nodeArray,0,count-1);
	
	for(i=0;i<count;i++){
		printf("%s %d\n",nodeArray[i].name, nodeArray[i].inodenum);
	}
	
	
	return 0;
}