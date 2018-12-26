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

void execute_jobs()
{
	ll i;
	int count=0;
	for(i=0;i<pidcount;i++)
	{
		if(pidrunnings[pids[i]]!=1)
			pids[count++]=pids[i];
	}
	pidcount=count;
	for(i=0;i<pidcount;i++)
	{
		if(pidrunnings[pids[i]]!=1)
		{
			char* state;
			char* status;
			char line[1000];
			FILE* status_file;
			char* statuspath=malloc(1024*sizeof(char));
			sprintf(statuspath,"/proc/%d/status",pids[i]);
			if(!fopen(statuspath,"r"))
			{
				fprintf(stderr,"Error: could not open info file\n");
				return;
			}
			status_file=fopen(statuspath,"r");
			while(fgets(line,1000, status_file))
		    {
			    if(!strncmp(line, "State:", 6))
		    	{
		    		status=strtok(line,delim2);
		    		status=strtok(NULL,delim2);
		    		break;
		    	}
		    }
			if(!strcmp(status,"T"))
			{
				state="Stopped";
				printf("\t[%lld]\t%s\t%s[%d]\n",i+1,state,pidnames[pids[i]],pids[i]);
			}
			else if(!strcmp(status,"S"))
			{
				state="Running";
				printf("\t[%lld]\t%s\t%s[%d]\n",i+1,state,pidnames[pids[i]],pids[i]);
			}
		}
	}
}

void kill_job(char** args)
{
	if(args[1]==NULL||args[2]==NULL)
	{
		fprintf(stderr,"Wrong Argument Format\n");
        return;
	}
	int id;
	sscanf(args[1],"%d",&id);
	if(id>pidcount)
	{
		fprintf(stderr,"Invalid Job\n");
        return;	
	}
	pid_t pid=pids[id-1];
	int sig;
	sscanf(args[2],"%d",&sig);
	if(kill(pid,sig)==-1)
	{
		fprintf(stderr,"Invalid Signal\n");
        return;	
	}	
	if(sig==9)
		pidrunnings[pid]=1;	
	if(sig==17||sig==19||sig==23)
	{
		kill(pid,SIGSTOP);
		pidrunnings[pid]=-1;	
	}
	int count=0,i;
	for(i=0;i<pidcount;i++)
	{
		if(pidrunnings[pids[i]]!=1)
			pids[count++]=pids[i];
	}
	pidcount=count;
}

void fg(char** args)
{
	if(args[1]==NULL)
	{
		fprintf(stderr,"Wrong Argument Format\n");
        return;
	}
	int count=0,i;
	for(i=0;i<pidcount;i++)
	{
		if(pidrunnings[pids[i]]!=1)
			pids[count++]=pids[i];
	}
	pidcount=count;
	int id,status;
	sscanf(args[1],"%d",&id);
	if(id>pidcount)
	{
		fprintf(stderr,"Invalid Job\n");
        return;	
	}
	pid_t pid=pids[id-1];
	fgpid=pid;
	fgcommand=pidnames[pid];
    signal(SIGINT, sigintHandler2); 
	signal(SIGTSTP, sighandler2);
	kill(pid,SIGCONT);
	waitpid(pid,&status,WUNTRACED);
	if(pidrunnings[pid]!=10)
		pidrunnings[pid]=1;
}

void bg(char** args)
{
	if(args[1]==NULL)
	{
		fprintf(stderr,"Wrong Argument Format\n");
        return;
	}
	int count=0,i;
	for(i=0;i<pidcount;i++)
	{
		if(pidrunnings[pids[i]]!=1)
			pids[count++]=pids[i];
	}
	pidcount=count;
	int id,status;
	sscanf(args[1],"%d",&id);
	if(id>pidcount)
	{
		fprintf(stderr,"Invalid Job\n");
        return;	
	}
	pid_t pid=pids[id-1];
	kill(pid,SIGCONT);
}

void overkill()
{
	int i;
	for(i=0;i<pidcount;i++)
	{
		kill(pids[i],SIGKILL);
		pidrunnings[pids[i]]=1;
	}
}