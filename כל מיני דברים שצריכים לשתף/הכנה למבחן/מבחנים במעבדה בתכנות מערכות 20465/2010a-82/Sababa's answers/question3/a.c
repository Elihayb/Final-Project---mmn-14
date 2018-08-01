#include <stdio.h>
#include <stdlib.h>
#define MY_SIZE 30
void getname(char *fname);

void main()
{
	char *fname;
	FILE *fp;

	getname(fname);
	fp=fopen(fname,"r");
	if(!fp)
	{
		fprintf(stderr,"can not open file %s",fname);
		exit(1);
	}
	while(!feof(fp))
		putchar(fgetc(fp));
	fclose(fp);
}

void getname(char *fname)
{
	fname=(char*)malloc(MY_SIZE);
	gets(fname);
}
