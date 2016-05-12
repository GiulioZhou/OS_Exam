//Scrivere un programma che per ogni file .c nella directory corrente chiami il compilatore gcc per generare il file oggetto (.o) a meno che esista gia' nella directory un file oggetto relativo allo stesso sorgente che sia piu' nuovo (ultima modifica) del sorgente.
//Tutti I parametri devono essere passati al compilatore.
//Es:
//genobj -I . -ggdb
//se nella directory corrente esistono I file uno.c e due.c e il file due.o deve richiamare gcc -I. -ggdb -c uno.c
//e, solo se due.o ha ultima modifica precedente a due.c, deve chiamare gcc -I. -ggdb -c due.c


