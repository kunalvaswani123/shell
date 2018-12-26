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

void interpretCommands(char* input_given)
{
	char** commands=split_firstdelim(input_given);
	int i,j;
	int fildes[2];
	for(i=0;commands[i]!=NULL;i++)
	{
		char** args=split_pipes(commands[i]);
	    int prev=0,next=0;
		for(j=0;args[j]!=NULL;j++)
		{
		    if(j==0&&args[j+1]!=NULL)
		    {
		    	prev=0;next=1;
		    }
		    else if(args[j+1]==NULL&&j!=0)
		    {
		    	prev=1;next=0;
		    }
		    else if(j>0&&args[j+1]!=NULL)
		    {
		    	prev=1;next=1;
		    }
		    if(prev==1)
		    {
		    	close(fildes[1]);
		    	if(dup2(fildes[0],0)!=0)
				{ 
			    	perror("dup2 fail");
					return;
				}
				close(fildes[0]);	
		    }
		    if(next==1)
		    {
			    if(pipe(fildes)!= 0)
			    {
			     	perror("pipe failed");
			    	return;
			    }
			    if(dup2(fildes[1],1)!=1) 
				{
			    	perror("dup2 fail");
					return;
				}
		    }
			char** args2=split_seconddelim(args[j]);
			check_command(args2);
		}
	}	
}