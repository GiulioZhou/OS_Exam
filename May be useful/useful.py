import os, sys, hashlib
from collections import defaultdict


#MD5 AND DEFAULTDICT - DICT

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
#create a default dic (dic with list), for each md5 there's a list of file with this md5
#PS this version look at all the subdirectories; if you want to check only the directory passed by parameter, just use listdir instead of walk
def list_files(startpath):
	all_md5=defaultdict(list) #create a dictionary of lists
	for root, dirs, files in os.walk(startpath):
		for filename in files:
			path = os.path.join(root, filename)
			checksum = md5(path)
			all_md5[checksum].append(path)
	return all_md5

#Remember! To check the items of a dictionary, you have to use the iteritems() function
for key, value in dic.iteritems():

#create a dictionary
dic = dict()
#or
dic = {}

--------------------------------

#LIST

lista = [] #empty list
lista.append(item) #add an item
lista.extends(listb) #concatenate two lists
#sort a list, if reverse=True it will order in a descendant way
#key=lambda tup: tup[1] means that, in case of a list of tuples, it will sort by the second element of the tuple
#lambda means something abount lambda calculus (functional progamming), I don't know much about it but I put it cause i think it's better in this way
lista.sort(key=lambda tup: tup[1], reverse = True)

#look only the first "number" element of the list
for elem in lista[:number]:
	do something


--------------------------------

#filecmp.cmp( file1, file2) -> compare 2 files and returns true if the files are equivalent, it checks  os.stat(), if differs, it will check the content of the files
import filecmp
filecmp.cmp( f1,f2)

-----------------------------------

#FILE MANIPULATION

with open(path,"w"/"r") as file: #open file for writing
	file.write("Something"")
	content file.read() #read the content of the file
			   
	os.path.getmtime(file) #returns the last modification time of the file
	size=os.path.getsize(path) #get the size of the file

	
   os.remove(file) #delete the file
   os.link(file, dest) #create hard link of file in dest directory
			   
   fnmatch.fnmatch(file, reg_exp) #return true if the filename match the regular expression
			   
	file.close()

			   
try:
   #Something -> es create hard link
except OSError, e:		#just ignore errno 17 -> race condition problem
	if e.errno != 17:
		raise
	pass

----------------------------------
			   
#STRING MANIPULATION
	
devided = str.split(".") #split a string in two (firstpart, secondpart), delimitated by de argument

filename, file_extension = os.path.splitext(path) #split a path and return the filename and its extension






