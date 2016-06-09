#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


//execvp from a const string (e.g. got from getline)
void myexec (const char *line);

//returns the extension of filename
const char *get_filename_ext(const char *filename)