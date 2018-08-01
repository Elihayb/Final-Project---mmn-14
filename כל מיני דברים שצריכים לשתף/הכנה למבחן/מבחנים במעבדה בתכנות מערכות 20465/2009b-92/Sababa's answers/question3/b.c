#include <stdio.h>

struct {int a[3],b;}w[]={{1,2,3},2};

int main()
{
	printf("w[0].b = %d\n",w[0].b);
	return 0;
}
