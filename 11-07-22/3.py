#Siano date due sottoalberi del file system (il programma e' pensato per due versioni di una gerarchia sorgente). Lo script deve cercare i file .c e .h presenti nei due sottoalberi evidenziando:
# quali sono presenti in un solo sottoalbero
# quali sono presenti in entrambi i sottoalberi ma hanno contenuto differente.
#Es:
#cmpsource so.1.0 so.1.1
#so.1.0/file.c not in so.1.1
#so.1.0/p/q/search.c
#so.1.1/p/q/search.c differ
#so.1.1/h/head.h not in so.1.0

import sys,os, filecmp

cindira=[]
cindirb=[]
hindira=[]
hindirb=[]

def addFile (treepath, clist,hlist):
	for root, dirs, files in os.walk(treepath):
		for file in files:
			path=os.path.join(root,file)
			filename, file_extension = os.path.splitext(path)
			if file_extension==".c":
				clist.append((path,file))
			else:
				if file_extension==".h":
					hlist.append((path,file))

def checkFile( clista, clistb, treeb):
	for path, name in clista:
		for elem in clistb:
			if path in elem:
				if not filecmp.cmp(path,elem[0]):
					print path
					print elem[0]+" differ"
				cindira.remove((path,name))
				cindirb.remove(elem)
			else:
				print path + " not in" + treeb

addFile(sys.argv[1],cindira,hindira)
addFile(sys.argv[2],cindirb,hindirb)
checkFile(cindira,cindirb,sys.argv[2])
checkFile(cindirb,cindira,sys.argv[1])
checkFile(hindira,hindirb,sys.argv[2])
checkFile(hindirb,hindira,sys.argv[1])




