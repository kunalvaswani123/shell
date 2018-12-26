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

void print_detail(char* location,struct stat buff,char* dirname)
{
    struct passwd *user;
	struct group *group;
	struct tm *starttime;
	unsigned char s[14];
	int return_value=stat(location,&buff);
	if(return_value)
	{
		fprintf(stderr,"Could not open directory or file..\n");
		return;
	}
	printf( (S_ISDIR(buff.st_mode)) ? "d" : "-");
	printf( (buff.st_mode & S_IRUSR) ? "r" : "-");
	printf( (buff.st_mode & S_IWUSR) ? "w" : "-");
	printf( (buff.st_mode & S_IXUSR) ? "x" : "-");
	printf( (buff.st_mode & S_IRGRP) ? "r" : "-");
	printf( (buff.st_mode & S_IWGRP) ? "w" : "-");
	printf( (buff.st_mode & S_IXGRP) ? "x" : "-");
	printf( (buff.st_mode & S_IROTH) ? "r" : "-");
	printf( (buff.st_mode & S_IWOTH) ? "w" : "-");
	printf( (buff.st_mode & S_IXOTH) ? "x" : "-");
	printf(" %8d",(int)buff.st_nlink);
	user=getpwuid(buff.st_uid);
	printf(" %8s", user->pw_name);
	group=getgrgid(buff.st_gid);
	printf(" %8s", group->gr_name);
	ll size=buff.st_size;
	printf(" %8lld",size);
	strftime(s,13,"%b %e %R",localtime(&(buff.st_ctime)));
	printf(" %16s",s);
	printf(" %20s",dirname);
	printf("\n");
}