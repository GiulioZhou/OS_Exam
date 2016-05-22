#include "shared.h"

shared_data *openShared(){
	int fd;
	shared_data *data;
	
	fd = shm_open(("/shared"), O_RDWR, S_IRUSR|S_IWUSR);;
	if (fd == -1) {
		fprintf(stderr, "Open failed : %s\n",
				strerror(errno));
		return NULL;
	}
	
	data = (shared_data*)mmap(0, sizeof(shared_data), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED) {
		fprintf(stderr, "mmap failed:%s\n", strerror(errno));
		return NULL;
	}
	close(fd);
	
	
	
	return data;
}




shared_data *createShared(){
	int fd;
	shared_data* data;

	
	shm_unlink("/shared");
	fd = shm_open("/shared", O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
	if (fd == -1) {
		fprintf(stderr, "Open failed : %s\n",
				strerror(errno));
		return NULL;
	}
	if(ftruncate(fd, sizeof(shared_data)) == -1){
		fprintf(stderr, "ftruncate : %s\n", strerror(errno));
		return NULL;
	}
	
	data = (shared_data*)mmap(0, sizeof(shared_data), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED) {
		fprintf(stderr, "mmap failed:%s\n", strerror(errno));
		return NULL;
	}
	close(fd);
	return data;
}
