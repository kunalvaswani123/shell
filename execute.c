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

void execute(char** args)
{
	pid_t pid = fork(); 
 	int i;
 	int background_flag=0;
    int run_flag=0;
 	char* command=args[0];
    for(i=0;args[i]!=NULL;i++)
        command=args[i];

 	int st;

 	if(command[strlen(command)-1]=='&')
 	{
 		args[i-1][strlen(command)-1]='\0';
 		command=args[0];
 		background_flag=1;
 	}
    if (pid == -1)
    {
		fprintf(stderr,"Forking Failed\n");
		return;
    }
    else if(pid == 0)
    {
        if(background_flag==1)
        {
            setpgid(0,0);
        }
        if(execvp(args[0],args)<0)
        {
            fprintf(stderr,"%s: command not found\n",args[0]);
            run_flag=-1;
        }
        exit(0);
    } 
    else 
    {
    	if(background_flag==0&&run_flag==0)
        {
	        fgpid=pid;
            fgcommand=command;
            signal(SIGTSTP, sighandler2);
            signal(SIGINT, sigintHandler2); 
            waitpid(pid,&st,WUNTRACED); 
        }
	    if(background_flag==1&&run_flag==0)
        {
            if(!strcmp(command,"vi"))
            {
                kill(pid,SIGSTOP);  
                printf("STOPPED   vi\n");
                printf("vi with pid %d exited normally\n",pid);
            }
            else
            {
                pidnames[pid]=command;
                pids[pidcount++]=pid;    
            }
            return;
        }
        return;
    }
}