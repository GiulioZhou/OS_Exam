#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>


extern int checkgroup(const char* user, const char* group){
	
	int i, ng = 0;
	gid_t *groups = NULL;
	//get a pointer to the user structure in passwd
	struct passwd *pw = getpwnam(user);
	char str[15];

	if (pw == NULL) return -1; //user non esiste
	
	//getgrouplist(const char *user, gid_t group, gid_t *groups, int *ngroups);
	//get list of groups to which a user belongs

	//returns -1 if the user has more than ng (0) groups
	if (getgrouplist(user, pw->pw_gid, NULL, &ng) < 0) {
		groups = (gid_t *) malloc(ng * sizeof (gid_t));
		//have to do it again to get the actuwal list of groups
		getgrouplist(user, pw->pw_gid, groups, &ng);
	}

    for(i = 0; i < ng; i++){
		sprintf(str,"%d",groups[i]); //convert int to str
        if(!strcmp(str,group)) return 1;
	}
	return 0;
}
