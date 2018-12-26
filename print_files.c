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

void print_files(int flag_a,char** dirs)
{
    int i;
    if(dirs[0]==NULL)
    	print_all(flag_a,0,".");
    else if(dirs[1]==NULL)
    {
    	if(!strcmp(dirs[0],"~"))
	    	print_all(flag_a,0,root);
    	else
	    	print_all(flag_a,0,dirs[0]);
    	return;
    }

    for(i=0;dirs[i]!=NULL;i++)
    {
    	if(!strcmp(dirs[i],"~"))
	    	print_all(flag_a,1,root);
    	else
	    	print_all(flag_a,1,dirs[i]);
		if(dirs[i+1]!=NULL)
			printf("\n");
	}
}