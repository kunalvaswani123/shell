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

void execute_cd(char** args)
{
	if(args[1]==NULL||(strcmp(args[1],"~")==0))
		chdir(root);
	else if(chdir(args[1]))
		perror("Error");
}