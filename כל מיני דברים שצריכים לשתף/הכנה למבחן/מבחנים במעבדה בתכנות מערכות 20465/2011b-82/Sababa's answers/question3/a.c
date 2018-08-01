#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5
const char * const names[N] =
{"Dan","Dina","Ban",
		"Tom","Guy"/* etc. */};
void find_name(char *x)
{
	x=(char*)malloc(100);
	if(!x)exit(1);
	strcpy(x,names[rand()%N]);
}
int main()
{
	char *x;
	find_name(x);
	printf("%s\n",x);
	free(x);
	return 0;
}
