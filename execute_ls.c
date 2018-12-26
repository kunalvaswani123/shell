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

void execute_ls(char** args)
{
    int flag_a=0;
    int flag_l=0;
    int i,count=0;
    int buffer_size=64;
    char** dirs=(char**)malloc(sizeof(char*)*buffer_size);
    for(i=1;args[i]!=NULL;i++)
    {
	    if(!strcmp(args[i],"-l"))
	    	flag_l=1;
		else if(!strcmp(args[i],"-a"))
	    	flag_a=1;
	    else if(strcmp(args[i],"-al")==0||strcmp(args[i],"-la")==0)
	    {
	    	flag_a=1;
	    	flag_l=1;
	    }
	    else
	    	dirs[count++]=args[i];
    	if(count>=buffer_size)
    	{
	    	buffer_size+=64;
			dirs=(char**)realloc(dirs,buffer_size);
    	}
    }
    dirs[count]=NULL;
    if(flag_l==0)
    	print_files(flag_a,dirs);
    else
    	print_files_l(flag_a,dirs);
}