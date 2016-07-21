#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <pwd.h>


extern char **get_user_groups(void);

extern void free_user_groups(char ** v);
