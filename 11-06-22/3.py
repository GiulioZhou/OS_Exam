#Scrivere uno script bash o un programma python che metta in ordine tutti i file di un sottoalbero dal piu' vecchio al piu' recente.
#La stampa finale deve mostrare solamente il path relativo dei file.

#Piu vecchio in che senso? Ultima modifica o data creazione?

import sys, os

all_file = []

for root, directories, files in os.walk(sys.argv[1]): #dovevo fare il controllo dei parametri ma non avevo voglia
	for filename in files:
		path = os.path.join(root, filename)
		time = os.path.getmtime(path)
		all_file.append( (filename, time)) #se li mettevo gia in ordine era meglio

all_file.sort(key=lambda tup: tup[1])

#for elem in all_file:
print all_file
