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

char** redirect(char** args)
{			
	char** newargs=args;
	int i,j;
	int fdin;
	int fdout;
	int inflag=0;
	int outflag=0;
	for(i=0;args[i]!=NULL;i++)
	{
		if(!strcmp(args[i],">"))
		{
			if(args[i+1]==NULL)
			{
		        fprintf(stderr,"shell: No File Found\n");
				char** emptyargs=malloc(sizeof(char*)*1);
				emptyargs[0]=NULL;
				return emptyargs;
			}
		    newargs[i]=NULL;
		    fdout=open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		    if(i==0)
		    {
			    char** emptyargs=malloc(sizeof(char*)*1);
			    emptyargs[0]=NULL;
				return emptyargs;
		    }
			outflag=1;
		}
		else if(!strcmp(args[i],"<"))
		{
			if(args[i+1]==NULL)
			{
		        fprintf(stderr,"shell: No File Found\n");
				char** emptyargs=malloc(sizeof(char*)*1);
				emptyargs[0]=NULL;
				return emptyargs;
			}
		    newargs[i]=NULL;
		    fdin=open(args[i+1], O_RDONLY , 0644);
			if(fdin<0)
			{
			    fprintf(stderr,"shell: %s: No such file or directory\n",args[i+1]);
				char** emptyargs=malloc(sizeof(char*)*1);
				emptyargs[0]=NULL;
				return emptyargs;
			}
			if(i==0)
		    {
			    char** emptyargs=malloc(sizeof(char*)*1);
			    emptyargs[0]=NULL;
				return emptyargs;
		    }		    
			inflag=1;
		}
		else if(!strcmp(args[i],">>"))
		{
			if(args[i+1]==NULL)
			{
		        fprintf(stderr,"shell: No File Found\n");
				char** emptyargs=malloc(sizeof(char*)*1);
				emptyargs[0]=NULL;
				return emptyargs;
			}
		    newargs[i]=NULL;
		    if(i==0)
		    {
			    char** emptyargs=malloc(sizeof(char*)*1);
			    emptyargs[0]=NULL;
				return emptyargs;
		    }
		    fdout=open(args[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			outflag=1;
		}
		// char command[100];
		// if(inflag!=1&&outflag!=1)
		// {
		// 	int j=0;
		// 	for(j=0;args[i][j]!='\0';j++)
		// 	{
		// 		if(args[i][j]=='<')
		// 		{
		// 			if(args[i][j+1]=='\0')
		// 			{
		// 		        fprintf(stderr,"shell: No File Found\n");
		// 				char** emptyargs=malloc(sizeof(char*)*1);
		// 				emptyargs[0]=NULL;
		// 				return emptyargs;
		// 			}
		// 			char temp1[100];
		// 			int tc;
		// 			int c=0;
		// 			for(tc=j+1;args[i][tc]!='>'&&args[i][tc]!='<'&&args[i][tc]!='\0';tc++)
		// 				temp1[c++]=args[i][tc];
		// 			j=tc-1;
		// 			fdin=open(temp1, O_RDONLY , 0644);
		// 			if(fdin<0)
		// 			{
		// 			    fprintf(stderr,"shell: %s: No such file or directory\n",temp1);
		// 				char** emptyargs=malloc(sizeof(char*)*1);
		// 				emptyargs[0]=NULL;
		// 				return emptyargs;
		// 			}
		// 			inflag=1;
		// 		}
		// 		else if(args[i][j+1]!='\0'&&args[i][j]=='>'&&args[i][j+1]=='>')
		// 		{
		// 			if(args[i][j+1]=='\0')
		// 			{
		// 		        fprintf(stderr,"shell: No File Found\n");
		// 				char** emptyargs=malloc(sizeof(char*)*1);
		// 				emptyargs[0]=NULL;
		// 				return emptyargs;
		// 			}
		// 			char temp1[100];
		// 			int tc;
		// 			int c=0;
		// 			for(tc=j+1;args[i][tc]!='>'&&args[i][tc]!='<'&&args[i][tc]!='\0';tc++)
		// 				temp1[c++]=args[i][tc];					
		// 			j=tc-1;
		// 			fdout=open(temp1, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// 			outflag=1;
		// 		}
		// 		else if(args[i][j]=='>')
		// 		{
		// 			if(args[i][j+1]=='\0')
		// 			{
		// 		        fprintf(stderr,"shell: No File Found\n");
		// 				char** emptyargs=malloc(sizeof(char*)*1);
		// 				emptyargs[0]=NULL;
		// 				return emptyargs;
		// 			}
		// 			char temp1[100];
		// 			int tc=j+1;
		// 			int c=0;
		// 			for(tc=j+1;args[i][tc]!='>'&&args[i][tc]!='<'&&args[i][tc]!='\0';tc++)
		// 				temp1[c++]=args[i][tc];					
		// 			j=tc-1;
		// 			fdout=open(temp1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// 			outflag=1;
		// 		}
		// 		else
		// 			command[j]=args[i][j];
		// 	}
		// }
		// if(inflag==1||outflag==1)
		// {
		// 	if(command[i]=='\0')
		// 		args[i]=NULL;
		// 	else
		// 		args[i]=command;
		// }
	}
	if(inflag==1&&dup2(fdin, 0) != 0) 
    	perror("dup2 fail");
	if(outflag==1&&dup2(fdout, 1) != 1) 
     	perror("dup2 fail");
	return newargs;
}