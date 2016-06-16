#Lo script o il programma Python deve fornire una lista dei file all'interno di un sottoalbero ordinati secondo la profondita nell'albero (prima tutti quelli nella radice del sottoalbero, poi tutti quelli al secondo livello), in ordine alfabetico fra quelli allo stesso livello.

import sys,os

file_depth = {}

path = sys.argv[1]
start=path.count(os.sep)

for root, dirnames, filenames in os.walk(path, topdown= True):
	depth = root.count(os.path.sep) - start
	if depth not in file_depth:
		file_depth[depth]=[]
	for file in filenames:
		file_depth[depth].append(file)

for key, value in file_depth.iteritems():
	value.sort()

print file_depth
