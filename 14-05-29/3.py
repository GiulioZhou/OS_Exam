#Il comando che dovrete implementare come script shell o programma python e' statlen.
#Data una directory statlen fa una statistica sulla lunghezza dei nomi dei file presenti in tutto il sottoalbero con radice nella directory passata come parametro.
#es.
#$ statlen /tmp 2: 2
#3: 10
#5: 4
#...
#significa che in tmp (e in tutte le sottodir.ectory di /tmp) ci sono 2 file con nome di due caratteri, 10 con nomi di 3 caratteri e cosi' via.


import os, sys

count = dict()

p = len(sys.argv)

if p > 1 :

	for files in os.walk(sys.argv[1]): #os.walk generate a 3-tuple (dirpath, dirnames, filenames) for each file in the directory tree
		for file in files[2]:
			length = len(file.split(".")[0]) #split() devide the string into two delimited by str -> str.split(str, num)   num is the number of lines to be made
			if length in count:
				count[length] += 1
			else: #if the key does not exist, it'll be created with value 1
				count[length] = 1

else:
	print "no path"
	sys.exit()


for elem in count.items(): #print tuple (lenght, number_of_file)
	print elem