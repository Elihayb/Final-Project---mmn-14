#include <stdio.h>
#include <malloc.h>
#include <string.h>

char * obtain_data()
{
	char *buf=malloc(100);
	FILE *f;
	size_t length=0;

	if(!buf)return NULL;
	f= fopen("data.dat","r");
	if(!f)return NULL;
	*buf = '\0';
	while(fgets(buf+length,100,f))
	{
		length = strlen(buf);
		realloc(buf,length+100);
	}
	fclose(f);
	return buf;
}
