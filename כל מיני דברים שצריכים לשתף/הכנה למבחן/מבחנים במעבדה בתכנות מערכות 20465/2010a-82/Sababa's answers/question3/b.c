#include <stdio.h>

const int month[31] = {
		8,5,7,2,-1,-2,-1,4,-1,0,
		0,2,5,7,2,4,-1,7,4,-2,
		1,7,2,2,-2,-3,-1,6,-1,3,9};

int main()
{
	unsigned i, count=31;
	int sum=0;

	for(i=0;i<count;i++)
	{
		sum +=month[i];
	}
	printf("The average low temperature was");
	printf(" %d degrees\n",sum/count);
	return 0;
}
