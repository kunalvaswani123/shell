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

void execute_remindme(char** args)
{
	pid_t pid = fork(); 
    if (pid == -1)
    {
		fprintf(stderr,"Forking Failed\n");
		return;
    }
    else if(pid == 0)
    {
    	int time=0;
    	char** message;
		if(sscanf(args[1], "%d", &time) == EOF) 
		{
		    fprintf(stderr, "WARNING: Incorrect value for time argument\n");
		    return;
		}
    	int count=0,i;
        char complete_message[10000];
        if(args[2]==NULL)
    	{
    		printf("Enter Message\n");
    		return;
    	}
        else 
            strcpy(complete_message,args[2]);
        for(i=3;args[i]!=NULL;i++)
        {
            strcat(complete_message," ");
            strcat(complete_message,args[i]);
        }
        
    	sleep(time);
    	
        printf("\nReminder: %s\n",complete_message);
    } 
}