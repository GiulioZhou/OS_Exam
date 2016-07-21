all: esercizio1

esercizio1:	giulio_zhou-main.o giulio_zhou-1.o
	gcc -o esercizio1 giulio_zhou-main.o giulio_zhou-1.o


es1.o: giulio_zhou-1.c
	gcc -c giulio_zhou-1.c

main.o: giulio_zhou-main.c
	gcc -c giulio_zhou-main.c

.PHONY: clean

clean:
	rm *.o esercizio1

