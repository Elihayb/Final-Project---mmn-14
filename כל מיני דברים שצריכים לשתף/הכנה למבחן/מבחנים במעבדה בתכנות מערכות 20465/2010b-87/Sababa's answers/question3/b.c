#include <stdio.h>

char code1[6] = "123456";
char code2[6] = "123455";

void main()
{
	if(code1 == code2)
		printf(" code1 is equal to code2 \n ");
	else
		printf("code1 is  not equal to code2 \n ");

}
