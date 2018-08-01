#include <stdio.h>

#define SUMMARY(ARR,COUNT,SUM){\
	SUM = 0;\
	int i;\
	for(i = 0; i < COUNT; i++){\
		SUM += ARR[i];\
	}\
}

int main(int argc, char **argv) {

printf("\n--------------------- question A ------------------\n");
int arr[] = {5,5,4};
int count = 3;
int sum;
SUMMARY(arr,count,sum);
printf("array sum: %d\n",sum);

printf("\n--------------------- question B ------------------\n");
int arr2[] = {5,5,4,4,4};
int count2 = 5;
int sum2;
SUMMARY(arr2,count2,sum2);
printf("array sum: %d\n",sum2);
	return 0;
}
