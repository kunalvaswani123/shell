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
/*
bg
ctrl stuff
vi&
sleep &
fg of stopped process
kjob
*/
int main()
{
	root=getenv("PWD");
	pidnames=malloc(sizeof(char*)*1000000);
	saved_stdout=dup(1);
	saved_stdin=dup(0);
	int i;
	while(1)
	{
	    signal(SIGINT, sigintHandler); 
	    signal(SIGTSTP, sighandler); 
		checkexit();
		displayprompt();
		char* input=readinput();
		if(!strcmp(input,"quit"))
			return 0;
		interpretCommands(input);
		int count=0;
	}
	return 0;
}