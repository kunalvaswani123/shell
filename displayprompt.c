#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<ctype.h>
#include "shellheader.h"

void displayprompt()
{
	char* username=getenv("USER");
	char hostname[1024];
	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	char* path=displaypath(cwd);
	printf("<%s@%s:%s> ",username,hostname,path);
}