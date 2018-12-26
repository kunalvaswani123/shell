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

void funcsetenv(char **args)
{
	if(args[1]==NULL||(args[2]!=NULL&&args[3]!=NULL))
	{
		fprintf(stderr,"Error: Wrong Argument Format\n");
		return;
	}
	if(args[2]==NULL)
		args[2]="";
	if(setenv(args[1],args[2],1)==-1)
	{
		fprintf(stderr,"Error: Wrong Argument Format\n");
	}
}

void funcunsetenv(char **args)
{
	if(args[1]==NULL)
	{
		fprintf(stderr,"Error: Wrong Argument Format\n");
		return;
	}
	if(unsetenv(args[1])==-1)
	{
		fprintf(stderr,"Error: Wrong Argument Format\n");
	}
}