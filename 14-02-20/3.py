#Il comando che dovrete implementare come script shell o programma python e' linkdir. linkdir prende due directory come parametri.
#linkdir dira dirb
#e deve creare in dirb un link fisico (non simbolico) a tutti i file regolari che sono in dira e non in dirb. Se un file regolare e' presente con lo stesso nome sia in dira sia in dirb, nella directory dirb deve rimanere il file originariamente presente se e' piu' recente di quello in dira altrimenti un link al file di dira con lo stesso nome.



#SYMBOLIC LINK -> link to another name in the file system -> if we delete the name pointed by symlink, symlink will point to nothing
#HARD LINK -> link to the inode of a file -> even if we delete the original pointer, we can access to the file, because all files refer to that
#INODE -> the inode is a data structure used to represent a filesystem object


import sys, os

#os.link(source, link_name) -> Create a hard link pointing to source named link_name.

if len(sys.argv) > 2:
	path1=sys.argv[1]
	path2=sys.argv[2]


	dira = []
	dirb = []

	#get all files from the directories -> walk generate all files in the directory tree, break is needed to check only the files in the root directory
	for (dirpath, dirnames, filenames) in os.walk(path1):
		dira.extend(filenames) #extend() appends the contents of seq to list.
		break

	for (dirpath, dirnames, filenames) in os.walk(path2):
		dirb.extend(filenames)
		break

	for file in dira:
		f1=os.path.join(path1, file) #join path with filename
		f2=os.path.join(path2, file)
		try:
			if file in dirb:
				if os.path.getmtime(f1) > os.path.getmtime(f2): #os.path.getmtime(path) -> return the time of last modification of path
					os.remove(f2) #remove the file if it is less recent
					os.link(f1, f2)
			else:
				os.link(f1, f2) #create hard link -> os.link(src, dst)
		except OSError, e:		#just ignore errno 17 -> race condition problem
			if e.errno != 17:
				raise
				pass

else:
	print "needed 2 arguments"





