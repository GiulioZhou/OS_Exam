#!/usr/bin/env python

import sys
import os
import re
import time
import subprocess

def parse(name):
	res = re.search(r'.*\.([0-9]+)$', name)
	if res == None:
		return None
	else:
		return int(res.group(1))

def list_filtered_files(path):
	return [f for f in os.listdir(path) if parse(f) != None ]

if len(sys.argv) != 2:
	print 'Usage:', sys.argv[0], 'path'
	sys.exit(1)

path = sys.argv[1]

# Get the file list
files = list_filtered_files(path)

sorted_files = sorted(files, key=lambda s: parse(s))
#for f in files:
#	ext = parse(f)
#	if ext == None: continue
#	sorted_files[ext] = f

last = 0
for f in sorted_files:
	time.sleep((parse(f)-last)/1000.0)
	last = parse(f)
	fullpath = os.path.join(path, f)
	print 'Starting', fullpath
	try:
		subprocess.Popen(fullpath)
	except Exception, e:
		print 'Cannot run', fullpath
		print e
