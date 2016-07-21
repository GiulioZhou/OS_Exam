#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>


extern char **get_user_groups(void){
	
	struct passwd *pw;
	pw = getpwuid(geteuid());
	gid_t *groups = NULL;
	int i,ng=0;
	char str[15];
	
	char **listofgroups;

	if (getgrouplist(pw->pw_name, pw->pw_gid, NULL, &ng) < 0) {
		groups = (gid_t *) malloc(ng * sizeof (gid_t));
		//have to do it again to get the actuwal list of groups
		getgrouplist(pw->pw_name, pw->pw_gid, groups, &ng);
	}


	listofgroups = malloc(ng * sizeof (char));
	
	for(i = 0; i < ng; i++){
		sprintf(str,"%d",groups[i]); //convert int to str
		listofgroups[i] = (char *)malloc(strlen(str));
		listofgroups[i] = str;
	}
	
	return listofgroups;
}


extern void free_user_groups(char ** v){
	if (v) {
		free(*v);
		*v = NULL;
	}
}
