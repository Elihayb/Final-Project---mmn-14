#include <stdio.h>

#define LEN sizeof(int)-1
#define TOWPOWER(n)(2<<(n))
//typedef enum{false,true}bool;
bool isNegative(int n){
	if(TOWPOWER(LEN)& n){
		return true;
	}
	return false;
}

int main()
{
	int num = -33333333;
	printf("%d %s",num,isNegative(num)?"Negative":"Positive");

	return 0;
}
