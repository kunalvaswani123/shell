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

void check_command(char** args)
{
	if(args[0]==NULL)
		return;
	
	char** newargs=redirect(args);
	if(newargs[0]==NULL)
		return;

	if(!strcmp(newargs[0],"cd"))
		execute_cd(newargs);
	else if(!strcmp(newargs[0],"setenv"))
		funcsetenv(newargs);
	else if(!strcmp(newargs[0],"unsetenv"))
		funcunsetenv(newargs);
	else if(!strcmp(newargs[0],"pwd"))
		execute_pwd();
	else if(!strcmp(newargs[0],"jobs"))
		execute_jobs();
	else if(!strcmp(newargs[0],"overkill"))
		overkill();
	else if(!strcmp(newargs[0],"echo"))
		execute_echo(newargs);
	else if(!strcmp(newargs[0],"kjob"))
		kill_job(newargs);
	else if(!strcmp(newargs[0],"fg"))
		fg(newargs);
	else if(!strcmp(newargs[0],"bg"))
		bg(newargs);
	else if(!strcmp(newargs[0],"ls"))
		execute_ls(newargs);
	else if(!strcmp(newargs[0],"pinfo"))
		execute_pinfo(args);
	else if(!strcmp(newargs[0],"remindme"))
		execute_remindme(args);
	else if(!strcmp(newargs[0],"clock"))
		execute_clock(args);
	else if(!strcmp(newargs[0],"quit"))
		return;
	else
		execute(newargs);

	if(dup2(saved_stdout, 1) != 1) 
		dup2(saved_stdout, 1); 
	if(dup2(saved_stdin, 0) != 0) 
		dup2(saved_stdin, 0);
}