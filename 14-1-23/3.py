#Il comando che dovrete implementare come script shell o programma python e' updatedir. Updatedir prende due directory come parametri.
#updatedir dira dirb
#deve copiare in dirb tutti i file regolari che sono in dira e non in dirb. Se un file regolare e' presente con lo stesso nome sia in dira sia in dirb, il file deve essere copiato dalla dira alla dirb solo se i contenuti differiscono.

import sys,os, filecmp
from shutil import copyfile

dira=sys.argv[1]
dirb=sys.argv[2]

dest=[]

for f in os.listdir(dirb):
	path=os.path.join(dirb,f)
	if os.path.isfile(path):
		dest.append(f)

for f in os.listdir(dira):
	path=os.path.join(dira,f)
	if os.path.isfile(path):
		path2=os.path.join(dirb,f)
		if f in dest:
			if(filecmp.cmp(path,path2)):
				continue
		copyfile(path, path2)
