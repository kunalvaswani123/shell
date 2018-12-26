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

void checkexit()
{
	int status;
	pid_t pid=waitpid(-1,&status,WNOHANG);
	if(pid>0)
	{
		if(WIFEXITED(status))
		{
			printf("%s with pid %d exited normally\n",pidnames[pid],pid);
			pidrunnings[pid]=1;	
		}
	}
}	

void sigintHandler(int sig_num) 
{ 
	return;
} 

void sigintHandler2(int sig_num) 
{ 
	kill(fgpid,SIGINT);
}

void sighandler(int sig_num) 
{ 
	return;
} 

void sighandler2(int sig_num) 
{ 
	kill(fgpid,SIGSTOP);
	int i,f=0;
	for(i=0;i<pidcount;i++)
	{
		if(pids[i]==fgpid)
			f=1;
	}
	if(f==0)
	{
		pidnames[fgpid]=fgcommand;
	    pids[pidcount++]=fgpid;     
    }
    pidrunnings[fgpid]=10;
}