all: esercizio2

esercizio2:	giulio_zhou-main-2.o giulio_zhou-2.o
	gcc -o esercizio2 giulio_zhou-main-2.o giulio_zhou-2.o


es1.o: giulio_zhou-2.c
	gcc -c giulio_zhou-2.c

main.o: giulio_zhou-main-2.c
	gcc -c giulio_zhou-main-2.c

.PHONY: clean

clean:
	rm *.o esercizio2

