/*
use string and pointer
*/
#include <stdio.h>
#include <stdlib.h>
void main(void)
{
	char *s;
	s = (char *)malloc(15);
	s = "Hello World";
	free(s);
}
