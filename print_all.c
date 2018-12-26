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

void print_all(int flag_a,int flag_for_no,char* dirfile)
{
	struct dirent *d_entry; 
    DIR *dir = opendir(dirfile);
	if(dir==NULL)
	{
		fprintf(stderr,"Could not open directory or file\n");
		return;
	}

	if(flag_for_no==1)
		printf("%s:\n",dirfile);
    
    while ((d_entry = readdir(dir))!= NULL)
    {
        if(d_entry->d_name[0]=='.'&&flag_a==0)
	        continue;
    	else
	        printf("%s\n",d_entry->d_name);
    }
    closedir(dir);
}