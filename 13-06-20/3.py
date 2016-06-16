#Scrivere un programma python o uno script bash per cercare all'interno della directory corrente tutti i file che abbiano lo stesso contenuto.


import os, sys, hashlib, filecmp
from collections import defaultdict

#Functions got from 15-01-21
def md5(fname):
	hash_md5 = hashlib.md5()
	with open(fname, "rb") as f:
		for chunk in iter(lambda: f.read(4096), b""):
			hash_md5.update(chunk)
	return hash_md5.hexdigest()

def list_files(startpath):
	all_md5=defaultdict(list)
	sameFile=[]
	for f in os.listdir(startpath):
		path = os.path.join(startpath, f)
		if os.path.isdir(path):
			continue

		checksum = md5(path)
		all_md5[checksum].append(path)

	for checksum, path in all_md5.iteritems():
		if len(path)>1:
			sameFile.append(path)
	return sameFile

#PS there's a possibility that files with same md5 don't have the same content, it would be better to check with filecmp if that's true

if __name__ == "__main__":

	path = sys.argv[1]
	print list_files(path)

#Not efficient way
#
#import sys, os ,filecmp
#
#def cmpT(t1, t2):
#	return sorted(t1) == sorted(t2)
#
#couple=[]
#
#for f in os.listdir("."):
#	for l in os.listdir("."):
#		if filecmp.cmp(f,l) and f != l:
#			if not couple:
#				couple.append((f,l))
#			else:
#				for elem in couple:
#					if not cmpT(elem, (f,l)):
#						couple.append((f,l))
#
#print couple