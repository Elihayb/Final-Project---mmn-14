#include <stdio.h>
#define FIND 'z'
void main (void)
{
	char array[] = "123qwezwerz1234z123456z";
	char *p;
	int count=0;

	p = array;
	while ( *p != '\0' )
	{
		if ( *p == FIND) count++;
		p++;
	}
	printf("the string appears %d times\n", count);
	free(p);

}
