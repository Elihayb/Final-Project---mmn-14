/*#include <stdio.h>*/
#define swap(A,B){int temp=(A);(A)=(B);(B)=temp;}

void main(void)
{
	int array[] = {2,5,79,81,0,4};
	int i;

	i=5;
	swap(i,array[i]);
	/*int j;
	for(j = 0; j <= 5; j++){
		printf("%d ",array[j]);
	}*/
}
