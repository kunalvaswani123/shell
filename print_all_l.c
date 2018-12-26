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

void print_all_l(int flag_a,int flag_for_no,char* dirfile)
{
	struct dirent *d_entry; 
    DIR *dir = opendir(dirfile);
	char* location=malloc(1024*sizeof(char));
	if(dir==NULL)
	{
		fprintf(stderr,"Could not open directory or file\n");
		return;
	}
	if(flag_for_no==1)
		printf("%s:\n",dirfile);
    if(!strcmp(dirfile,"."))
    {
		char cwd[1024];
		getcwd(cwd,sizeof(cwd));
		dirfile=cwd;
    }
    while ((d_entry = readdir(dir))!= NULL)
    {
        if(d_entry->d_name[0]=='.'&&flag_a==0)
	        continue;
    	else
    	{
			sprintf(location,"%s/%s",dirfile,d_entry->d_name);
			struct stat buff;
			print_detail(location,buff,d_entry->d_name);
    	}
    }
    closedir(dir);
}