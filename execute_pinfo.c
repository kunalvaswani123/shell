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

void execute_pinfo(char** args)
{
	int pid=getpid();
	char* statuspath=malloc(1024*sizeof(char));
	char* execpath=malloc(1024*sizeof(char));
	FILE* status_file;
	char line[1000];
	char* status;
	char* memory;
	char* memory2;
	char* p;
	if(args[1]==NULL)
	{
		printf("pid -- %d\n",pid);	
		sprintf(statuspath,"/proc/%d/status",pid);
		sprintf(execpath,"/proc/%d/exe",pid);
		status_file=fopen(statuspath,"r");
	}
	else
	{	
		sprintf(statuspath,"/proc/%s/status",args[1]);
		sprintf(execpath,"/proc/%s/exe",args[1]);
		if(!fopen(statuspath,"r"))
		{
			fprintf(stderr,"Error: could not open info file\n");
			return;
		}
		printf("pid -- %s\n",args[1]);		
		status_file=fopen(statuspath,"r");
	}
    while(fgets(line,1000, status_file))
    {
	    if(!strncmp(line, "State:", 6))
    	{
    		status=strtok(line,delim2);
    		status=strtok(NULL,delim2);
			printf("Process Status -- %s\n",status);
    		break;
    	}
    }
    while(fgets(line,1000, status_file))
    {
	    if(!strncmp(line, "VmSize:", 6))
    	{
    		memory=strtok(line,delim2);
    		memory=strtok(NULL,delim2);
    		memory2=strtok(NULL,delim2);
			printf("Memory -- %s %s\n",memory,memory2);
    		break;
    	}
    }
    if(readlink(execpath,statuspath,4200)==-1)
    	perror("Error");
    else
    {
		int root_length=strlen(root);
		int path_length=strlen(statuspath);
    	char* required_string;
    	if(!strncmp(statuspath,root,root_length))
		{
			required_string=(char*)malloc(sizeof(1024));
			required_string[0]='~';
			required_string[1]='/';
			int start=root_length+1,i;
			for(i=2;i<=path_length-root_length;i++)
				required_string[i]=statuspath[start++];
		}
    	printf("Executable Path -- %s\n",required_string);
    }
}