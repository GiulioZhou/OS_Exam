#Il comando che dovrete implementare come script shell o programma python e' mytx. Tale comando elenca tutti i file di una directory.
#mytx ddd ddd.tx
#Ogni riga del file di output (secondo parametro) deve contenere la lunghezza, uno spazio e il nume del file. Dopo l'ultima riga deve inserire una riga bianca.
#ddd.t2 deve contenere l'elenco dei file regolari. Il primo campo e' un numero intero seguito da uno spazio, tutto cio' che segue fino alla fine riga e' il nome del file.
#es.
#12 file1
#235 file di prova


import sys, os

if len(sys.argv) > 2:

	with open(sys.argv[2],"w") as file: #open file for writing

		for f in os.listdir(sys.argv[1]):
			file.write(str(os.stat(f).st_size) + " " + f + "\n")
		file.close()

else:
	print "needed 2 arguments"





