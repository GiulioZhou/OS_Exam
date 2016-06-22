#Lo script o il programma python da realizzare deve fornire l'occupazione totale in byte dei file della directory corrente che corrispondono alla espressione regolare passata come parametro.
#e.s. sizere 'l[az]x'
#444
#significa che la somma delle ampiezze dei file di tre lettere alfabetiche minuscole che iniziano per l finiscono per x, e' di 444 byte.

import sys, os,fnmatch
size=0

path="."
start=path.count(os.sep)

for root, dirs, files in os.walk(".", topdown=True):
	depth = root.count(os.path.sep) - start
	if depth>0:
		continue
	for file in files:
		path = os.path.join(".",file)
		if fnmatch.fnmatch(file, sys.argv[1]):
			print path

			size += os.path.getsize(path)

print size