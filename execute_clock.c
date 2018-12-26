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

void execute_clock(char** args)
{
	printf("\n");
	if(args[1]==NULL||args[2]==NULL||args[3]==NULL||args[4]==NULL)
	{
		fprintf(stderr,"Error: Wrong Argument Format\n");
		return;
	}

	if(strcmp(args[1],"-t"))
	{
		fprintf(stderr,"Error: Argument Not Found\n");
		return;	
	}

	if(strcmp(args[3],"-n"))
	{
		fprintf(stderr,"Error: Argument Not Found\n");
		return;	
	}
	int interval=0;
	int duration=0;
	char* timepath=malloc(100*sizeof(char *));
	char* datepath=malloc(100*sizeof(char *));
	FILE* rtc_filet;
	FILE* rtc_filed;
	sprintf(timepath,"/sys/class/rtc/rtc0/time");
	sprintf(datepath,"/sys/class/rtc/rtc0/date");
	if(sscanf(args[2], "%d", &interval) == EOF) 
	{
	    fprintf(stderr, "WARNING: Incorrect value for interval\n");
	    return;
	}
	if(sscanf(args[4], "%d", &duration) == EOF) 
	{
	    fprintf(stderr, "WARNING: Incorrect value for duration\n");
	    return;
	}
	int count=0;
	int endcount=duration/interval;
	int lefttime=duration%interval;
	while(1)
	{
    	char line1[1000];
    	char line2[1000];
    	if(!fopen(timepath,"r"))
		{
			fprintf(stderr,"Error: could not open rtc file\n");
			return;
		}
		if(!fopen(datepath,"r"))
		{
			fprintf(stderr,"Error: could not open rtc file\n");
			return;
		}
		rtc_filet=fopen(timepath,"r");
		rtc_filed=fopen(datepath,"r");
		while(fgets(line1,1000, rtc_filed))
		{
			char* date;
			char* month;
			char* year;
			int monthint=0;
			year=strtok(line1,delimdash);
			month=strtok(NULL,delimdash);
			date=strtok(NULL,delimdash);
			date[strlen(date)-1]='\0';
			char* monthprint;
			sscanf(month,"%d",&monthint);
			if(monthint==1)
				monthprint="January";
			if(monthint==2)
				monthprint="February";
			if(monthint==3)
				monthprint="March";
			if(monthint==4)
				monthprint="April";
			if(monthint==5)
				monthprint="May";
			if(monthint==6)
				monthprint="June";
			if(monthint==7)
				monthprint="July";
			if(monthint==8)
				monthprint="August";
			if(monthint==9)
				monthprint="September";
			if(monthint==10)
				monthprint="October";
			if(monthint==11)
				monthprint="November";
			if(monthint==12)
				monthprint="December";
			printf("%s %s %s, ",date,monthprint,year);
			break;
		}
		while(fgets(line2,1000, rtc_filet))
		{
	    	printf("%s\n",line2);
			break;
		}
		count++;
		if(count>endcount)
			break;
		sleep(interval);
	}
	sleep(lefttime);
}