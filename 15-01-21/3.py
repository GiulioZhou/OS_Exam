#Scrivere un programma python o uno script bash che scandisca il sottoalbero relativo alle directory passate come parametri (o alla direcotry corrente se non ci sono parametri) e fornisca in output l'elenco dei file che hanno la stessa somma MD5 (i.e. l'output del comando md5sum).
#In output ogni riga deve mostrare un elenco di pathname realtivi a file che hanno la stessa somma MD5 (che quindi sono molto molto probabilmente uguali).

import os, sys, hashlib
from collections import defaultdict

#return the md5 of fname
#note sometimes you won't be able to fit the whole file in memory. In that case, you'll have to read chunks of 4096 bytes sequentially and feed them to the Md5 function
#fonte: http://stackoverflow.com/questions/3431825/generating-an-md5-checksum-of-a-file
def md5(fname):
	hash_md5 = hashlib.md5()
	with open(fname, "rb") as f:
		for chunk in iter(lambda: f.read(4096), b""):
			hash_md5.update(chunk)
	return hash_md5.hexdigest()

#https://docs.python.org/2/library/collections.html
def list_files(startpath):
	all_md5=defaultdict(list)
	for root, dirs, files in os.walk(startpath):
		for filename in files:
			path = os.path.join(root, filename)
			checksum = md5(path)
			all_md5[checksum].append(path)

	for checksum, path in all_md5.iteritems():
		if len(path)>1:
			print "md5: " + checksum
			for item in path:
				print item


if __name__ == "__main__":
	if len(sys.argv)==1:
		path = "."
	else:
		path = sys.argv[1]

	list_files(path)