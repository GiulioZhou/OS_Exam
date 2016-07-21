#!/usr/bin/env python

import os, sys, operator
from collections import defaultdict


nomi={}

path="/home/students"

for f in os.listdir(path):

	filename, file_extension = os.path.splitext(f)
	if (file_extension==".tgz" or file_extension==".old" or file_extension==""):
		continue
	
	if filename not in nomi:
		nomi[filename]=1
	else:
		nomi[filename]+=1

#a dictionary can't be sorted, so I need to convert in a list of tuple
sorted_dic= sorted(nomi.items(), key=operator.itemgetter(1), reverse=True)

#top 5
for elem in sorted_dic[:5]:
	print elem
