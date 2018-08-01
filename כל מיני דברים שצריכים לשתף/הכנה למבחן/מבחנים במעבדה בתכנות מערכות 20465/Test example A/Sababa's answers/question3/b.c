#include <stdio.h>
#define MULa 2
#define MULb 3
#define NUM 10

int entry( int a, int b )
{
	return (a* MULa + b* MULb);
}

int sum(int num)
{
	int my_sum=0;
	int i=0,j=0;
	while (j<=num)
	{
		my_sum+=entry(i++,i++);
		j++;
	}
	return (my_sum);
}

int main()
{
	int my_sum = sum( NUM );
	printf("sum is %d\n", my_sum);
	return 0;
}
