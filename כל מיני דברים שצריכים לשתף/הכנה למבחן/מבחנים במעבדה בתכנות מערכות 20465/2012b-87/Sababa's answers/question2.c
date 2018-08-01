#include <stdio.h>

#define TWO_BIT_TO_ZERO(TYPE,ITEM){\
	TYPE RESULT = 0;\
	int i = 0;\
	for (;ITEM; ITEM >>= 1,i++) {\
	if((ITEM & 3) == 3){\
	ITEM >>= 1;\
	i++;\
	}else if((ITEM & 1)){\
	RESULT |= (1<<i);\
	}\
	}

void intToBinStr(int num, char* binSTR){
	int i;
	int value = num;
	for (i = 31; i >= 0; --i, value >>= 1){
		binSTR[i] = '0'+(value & 1);
	}

	binSTR[32] = '\0';
}

void twoBitsAndView(int a){
	char str[33];
	int num = a;
	TWO_BIT_TO_ZERO(int,num);
	if(num != a){
		intToBinStr(a,str);
		printf("befor: %s\n",str);
		intToBinStr(num,str);
		printf("after: %s\n",str);

	}
}

int main(int argc, char **argv) {

printf("\n--------------------- question A ------------------\n");
	char str[33];
	int num = 125;
	intToBinStr(num,str);
	printf("befor: %s\n",str);
	TWO_BIT_TO_ZERO(int,num);
	intToBinStr(num,str);
	printf("after: %s\n",str);

printf("\n--------------------- question B ------------------\n");
	int a1 = 124,a2 = 63,a3 = 89;
	twoBitsAndView(a1);
	twoBitsAndView(a2);
	twoBitsAndView(a3);
	return 0;
}
