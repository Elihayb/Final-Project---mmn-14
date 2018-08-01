#include <stdio.h>
#include <stdilib.h>
#include <alloc.h>

void main()
{
	int i, *p;
	p=(*int)malloc(sizeof(int)*5);
	if (p==NULL)
		exit(1);
	for( i=0; i<5; i++)
		p[i]=i;

	p=(*int)realloc(p, sizeof(int)*10);
	if (p==NULL)
		exit(1);
	for( i=5; i<10; i++)
		p[i]=i;

	for( i=0; i<10; i++)
		printf( "%d ", p[i]);
	free(p);
}
