#Scrivere un programma python o uno script bash che cataloghi per nome tutti i file presenti in un sottoalbero.
#nameindex dir1 dir2
#crea nel file dir2 un link simbolico ad ogni file contenuto nell'albero che ha come radice dir1. Quando sono presenti piu' file con lo stesso nome in diverse directory all'interno di dir1, viene posto un suffisso numerico al nome del link simbolico
#se dir1 contiene i file pippo, pluto e paperino e la directory paperopoli e quest'ultima contiene i file paperino, qui quo e qua, all'interno di dir2 divranno essere contenuti i seguenti link simbolici:
#pippo  dir1/pippo
#pluto  dir1/pluto
#paperino  dir1/paperino
#paperino1  dir1/paperopoli/paperino
#qui  dir1/paperopoli/qui
#quo  dir1/paperopoli/quo
#qua  dir1/paperopoli/qua

import sys, os

if len(sys.argv)!=2:

	path1=sys.argv[1]
	path2=sys.argv[2]
	
	all=[]
	for dirname, dirnames, filenames in os.walk(path1):
		# print path to all subdirectories first.
		
		# print path to all filenames.
		for filename in filenames:
			all.append((os.path.join(dirname, filename),filename))
	for file in all:
		f2=os.path.join(path2, file[1])
		while os.path.islink(f2):
			f2+='1'
		print f2
		os.symlink(file[0],f2)
else:
	print "Need 2 arguments"