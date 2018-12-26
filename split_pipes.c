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

char** split_pipes(char* linegiven)
{
	int buffer_size=64,pos=0;
	char** splits=(char**)malloc(sizeof(char*)*buffer_size);
	if(!splits)
	{
		fprintf(stderr,"allocation error\n");
		exit(EXIT_FAILURE);
	}
	char* split=strtok(linegiven,"|");
	while(split!=NULL)
	{
		splits[pos++]=split;
		if(pos>=buffer_size)
		{
			buffer_size+=64;
			splits=(char**)realloc(splits,buffer_size);
		}
		if(!splits)
		{
			fprintf(stderr,"allocation error\n");
			exit(EXIT_FAILURE);
		}
		split=strtok(NULL,"|");
	}
	splits[pos]=NULL;
	return splits;
}