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

char* readinput()
{
	int buffer_size=1024,pos=0;
	char* buffer=(char*)malloc(sizeof(char) * buffer_size);
	int single_char;
	if(!buffer)
	{
		fprintf(stderr,"allocation error\n");
		exit(EXIT_FAILURE);
	}
	while(1==1)
	{
		single_char=getchar();
		if(single_char!='\n'&&single_char!=EOF)
			buffer[pos++]=single_char;
		else
		{
			buffer[pos++]='\0';
			return buffer;
		}
		if(pos>=buffer_size)
		{
			buffer_size+=1024;
			buffer=(char*)realloc(buffer,buffer_size);
			if(!buffer)
			{
				fprintf(stderr,"allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}