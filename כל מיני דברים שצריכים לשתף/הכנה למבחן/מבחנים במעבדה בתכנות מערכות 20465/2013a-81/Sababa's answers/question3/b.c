#include <stdio.h>

void main()
{
	int a,b,c,i;
	a = 0;
	b = 1;
	for(i=0;i<10;i++)
	{
		printf("%d",a);
		c = a+b;
		a = b;
		b = c;
	}
	putchar('\n');
}
