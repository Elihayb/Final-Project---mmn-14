#include <stdio.h>

#define ARR_SIZE 5

int main()
{
	int array[ARR_SIZE] = {1,-2,3,4,-5};
	unsigned sum;
	int i;

	for ( i = 0, sum=0; i < ARR_SIZE; i++ )
	sum += array[i];

	if( sum > -1 ) printf ("non-negative");
	else printf ("negative");
	return 0;
}
