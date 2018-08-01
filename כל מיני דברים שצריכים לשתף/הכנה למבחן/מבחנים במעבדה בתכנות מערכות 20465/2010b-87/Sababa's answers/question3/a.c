#include <stdio.h>

#define NUM1 80
#define NUM2 99

void max(int *p,int a,int b)
{
	if(a>b)
		*p=a;
	else
		*p=b;
}

void main()
{
	int my_max;
	max(&my_max,NUM1,NUM2);
	printf("the max is: %d",my_max);
}
