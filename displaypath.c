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

char* displaypath(char* cwd)
{
	int i;
	int root_length=strlen(root);
	int cwd_length=strlen(cwd);
	if(!strcmp(root,cwd))
		return (char*)"~";
	else if (!strncmp(cwd,root,root_length))
	{
		char* required_string=(char*)malloc(sizeof(1024));
		required_string[0]='~';
		required_string[1]='/';
		int start=root_length+1;
		for(i=2;i<=cwd_length-root_length;i++)
			required_string[i]=cwd[start++];
		return required_string;
	}
	else 
		return cwd;
}

