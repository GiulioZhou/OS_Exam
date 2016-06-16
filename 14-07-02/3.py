#Il comando che dovrete implementare come script shell o programma python e' maxfreq. Maxfreq ha come parametro un carattere alfanumerico e una directory.
#Es:
#maxfreq q mydir 10
#Cerca in tutto il sottoalbero del file system originato da mydir i 10 file che hanno la maggior frequenza della lettera indicata (in questo caso la maggior frequenza di 'q'). Fornisce in output i nomi dei file e le frequenze in percentuale.


import sys, os
from collections import Counter


if len(sys.argv) > 3:

	frequency = []
	for root, subdir, files in os.walk(sys.argv[2]):
		for filename in files:
			path = os.path.join(root, filename)
			with open(path) as f:
				t=f.read()
				leng = len(t)
				c = Counter(t.strip())
				if leng > 0:
					frequency.append((filename, "{0:.2f}".format(float(c[sys.argv[1]])*100/leng)))
					#add to the list the filename and the frequency in percentage (but formatted to show only 2 decimals
	frequency.sort(key=lambda tup: tup[1], reverse = True)

	for elem in frequency[:int(sys.argv[3])]: #slice the list
		print elem

else:
	print "needed 3 arguments"





