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

void execute_echo(char** args)
{
	int i,j;
	for(i=1;args[i]!=NULL;i++)
	{
		char newstring[1000]={'\0'};
		if(args[i][0]=='$')
		{
			int count=0;
			for(j=1;args[i][j]!='\0';j++)
				newstring[count++]=args[i][j];
			if(getenv(newstring)!=NULL)
				printf("%s ",getenv(newstring));
		}
		else
			printf("%s ",args[i]);
	}
	printf("\n");
}