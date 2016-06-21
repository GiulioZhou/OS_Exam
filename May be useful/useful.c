#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_ARGS 64
#define MAX_LINE 1024

//----------USEFUL FUNCTIONS---------

//returns the extension of
const char *get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.'); //Returns a pointer to the last occurrence of character in the C string str
	if(!dot || dot == filename) return "";
	return dot + 1;
}

//returns the size of the file named filename
off_t fsize(const char *filename) {
	struct stat st;
	if (stat(filename, &st) == 0){
		return st.st_size;
	}

	fprintf(stderr, "Cannot determine size of %s: %s\n",
			filename, strerror(errno));
	return -1;
}

//true if the size differ or are the same inode
int checkStat(const char *filename1,const char *filename2) {
	struct stat st1,st2;
	
	if ((stat(filename1, &st1) == 0) && (stat(filename2, &st2) == 0)){
		if(st1.st_size != st2.st_size)return 1;
		if(st1.st_ino == st2.st_ino)return 1;
	}
	return 0;
}

//returns true if the two files have the same content -> read char by char
int equal(char fname1[],char fname2[]){
	
	FILE *fp1, *fp2;
	int ch1, ch2;
	
	fp1 = fopen(fname1, "r");
	fp2 = fopen(fname2, "r");
	
	if (fp1 == NULL) {
		printf("Cannot open %s for reading ", fname1);
		exit(1);
	}
	if (fp2 == NULL) {
		printf("Cannot open %s for reading ", fname2);
		exit(1);
	}
	
	ch1 = getc(fp1);
	ch2 = getc(fp2);
	
	while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
		ch1 = getc(fp1);
		ch2 = getc(fp2);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	if (ch1 == ch2)	return 1;
	else  return 0;
	
}


//return true if the string is in ASCII form (range 1-127), or it control only if the first bit is 0
isascii("stringa");

//create a hard link
link(src , dest);

//reset the array -> put all the array to 0
memset(array, 0, arraysize);


//------------ERROR HANDLER----------

if (argc != 2){
	fprintf(stderr, "Expected 1 parameter");
	return(EXIT_FAILURE);
}


//-------------DIRECTORY-------------

//check all the file in the directory

#include <dirent.h>


/*struct dirent { // when _DARWIN_FEATURE_64_BIT_INODE is NOT defined
	ino_t      d_ino;                // file number of entry
	__uint16_t d_reclen;             // length of this record
	__uint8_t  d_type;               // file type, see below
	__uint8_t  d_namlen;             // length of string in d_name
	char    d_name[255 + 1];   // name must be no longer than this
}; */

struct dirent* in_file;
DIR* FD;

//open the current directory
if (NULL == (FD = opendir ("Directory path"))){
	fprintf(stderr, "Error : Failed to open directory - %s\n", strerror(errno));
	return -1;
}

//change directory to "directory path"
chdir("directory path");

//mkdir() attempts to create a directory named pathname.
mkdir("pathname",0777);

while ((in_file = readdir(FD))){
	
	FILE *indirFile;
	char a[2];
	
	/* we don't want current and parent directories */
	if (!strcmp (in_file->d_name, "."))
		continue;
	if (!strcmp (in_file->d_name, ".."))
		continue;

	//fai qualcosa con in_file->d_name
	
	/* Open directory entry file for common operation */
	indirFile = fopen(in_file->d_name, "r");
	
	//fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream)
	//The function fread() reads nitems objects, each size bytes long, from the stream pointed to by stream, storing them at the location given by ptr.
	
	//legge carattere per carattere
	while (fread(&a,1,1,indirFile) && a[0]!= '\0') { //dovrei fare più controlli ma non ho voglia ora
		strcat(buffer,a);
	}
	
	//chiudi il file
	fclose(indirFile);

	
}

//rewind the directory descriptor
rewinddir(FD);



//--------------FILE STAT---------------

#include <time.h>
#include <sys/stat.h>

struct stat statbuf;
time_t t;

stat("file name", &statubuf); //oppure lstat
t = file.st_mtime;
S_ISREG(statbuf.st_mode); //true se il file è un file regolare


//--------------INOTIFY---------------


#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int length, i = 0;
int fd;
int wd;
char buffer[BUF_LEN];

fd = inotify_init();	//initializes a new inotify instance and returns a file descriptor associated with a new inotify event queue.

if (wd=inotify_add_watch(fd, "directory/file path", "varie cose che si vuole controllare") == -1) { 	//adds a new watch, or modifies an existing watch
	fprintf(stderr, "inotify_init failed:%s\n", strerror(errno));
	return(EXIT_FAILURE);
}

//Flag -> IN_CREATE | IN_DELETE | IN_DELETE_SELF

while("qualche condizione"){
	i=0;
	length = read( fd, buffer, BUF_LEN ); //read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf, On success, the number of bytes read is returned
	
	if ( length < 0 ) {
		perror( "read" );
	}
	
	while ( i < length && poll ) {
		struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
		if ( event->len ) {
			if ( event->mask & "FLAG" ) {
				if ( event->mask & IN_ISDIR ) {
					printf( "The directory %s was created.\n", event->name );
				}
				else {
					printf( "The file %s was created.\n", event->name );
				}
			}
		}
		i += EVENT_SIZE + event->len;
	}
}
//close watch
inotify_rm_watch( fd, wd );
//close inotify file descriptor
close( fd );


//---------PIPE, POLL AND FORK-----------

#include <poll.h>

//in questa cosa faccio la poll solo per far partire il processo figlio

int fd[2]; //pipe fd for process sinc
struct pollfd fds; //struct for poll
int pid;
int status;


//opening the pipe for pollin
if((pipe(fd)) == -1){
	perror("Pipe");
	return(EXIT_FAILURE);
}
fds.fd = fd[0];
fds.events=POLLIN;

if ( (pid = fork()) == -1) { //faccio la fork
	printf("fork fail\n");
	return(EXIT_FAILURE);
}

if (pid == 0) {	//child
	
	poll(&fds,1,-1); //struct poll, size of fds array and -1 for block until interrupt call
	//wait until all processes are ready
	
	//some sort of exec
	
	perror(currComm);
	return(EXIT_FAILURE);
}

//father process

//tell to all the processes to start
write(fd[1], "g", 1);

wait(&status);








