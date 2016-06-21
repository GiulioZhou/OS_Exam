#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>

// The list that will hold the file list, ordered by ext desc
typedef struct file file;

struct file {
	char *name;
	int ext;
	file *next;
};

// Insert a file element into the list, ordered by ext desc
file *insert(file *head, file *f) {

	// List is empty
	if (!head) {
		f->next = NULL;
		return f;
	}
	
	// The new file extension is less then the head extension
	if (f->ext < head->ext) { 
		f->next = head;
		return f;
	}

	file *n = head;
	do {
		// Append
		if (!n->next) {
			n->next = f;
			f->next = NULL;
			break;
		}
		
		// Insert
		if (n->next->ext > f->ext) {
			f->next = n->next;
			n->next = f;
			break;
		}
	} while ((n = n->next));
	
	return head;
}

// Allocate a file instance
file *alloc(char *name, int ext) {
	file *f = (file *) malloc(sizeof(file));
	f->name = strdup(name);
	f->ext = ext;
	return f;
}

// Check if a char is a digit
char is_digit(char c) {
	return c >= 48 && c <= 57;
}

// Parse a file name and returns its numeric extension
// Returns -1 if there is no extension, or if the extension is not a number >= 0
int parse(const char *name) {
	int len = strlen(name);
	int ext_len = 0; // The extension length
	char valid = 0; // Whether there is a valid (numeric) extension
	int i;
	
	for (i = len-1; i >= 0; i--) {
		if (is_digit(name[i])) {
			ext_len++;
		} else {
			if (name[i] == '.' && ext_len) {
				valid = 1;
				break;
			} else {
				break;
			}
		}
	}
	
	
	if (!valid)
		return -1;
	else {
		return atoi(&name[len-ext_len]);
	}
}

file *scan(DIR *folder) {

	struct dirent *entity;
	file *list = NULL;
	while ((entity = readdir(folder))) {
		// Skip directories
		if (entity->d_type == DT_DIR)
			continue;
		
		// Parse the numeric extension
		int ext = parse(entity->d_name);
		if (ext < 0) {
			continue;
		}
		
		// Insert the file into the ordered list
		list = insert(list, alloc(entity->d_name, ext));
	}
	closedir(folder);
	
	return list;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s path\n", argv[0]);
		return 1;
	}
	
	// Try to list the folder contents
	DIR *folder = opendir(argv[1]);
	if (!folder) {
		printf("Cannot open %s\n");
		return 1;
	}
	
	// Scan the files and put them into an ordered list
	file *list = scan(folder);
	
	// Run the programs
	file *n = list;
	int last = 0;
	while (n) {
		#ifdef DEBUG
			printf("Sleeping %d milliseconds\n", n->ext-last);
		#endif
		usleep((n->ext - last)*1000);
		last = n->ext;
		
		printf("Starting %s\n", n->name);
		if (!fork()) {
			
			// Prepare the full path
			char fullpath[strlen(argv[1])+strlen(n->name)+2];
			strcpy(fullpath, argv[1]);
			strcat(fullpath, "/");
			strcat(fullpath, n->name);
			
			execl(fullpath, NULL);
			
			// If execl returns, an error has occured
			#ifdef DEBUG
				printf("Cannot run %s\n", fullpath);
			#endif
			return 1;
		}
		n = n->next;
	}
	
	
	return 0;
}
