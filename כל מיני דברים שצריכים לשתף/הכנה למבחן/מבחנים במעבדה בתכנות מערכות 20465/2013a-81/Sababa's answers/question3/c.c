#include <stdio.h>
#include <stdlib.h>

#define FOREVER while(1)
#define MYEXIT()\
printf("The sum is %d\n",sum);\
exit(8);

int func(int);

void main(void)
{
	int value,sum=0;
	FOREVER
	{
		scanf("%d",&value);
		if(value < 0)
			MYEXIT();
		printf("Non negative value, you may continue.\n");
	}
	sum+=value;
}
