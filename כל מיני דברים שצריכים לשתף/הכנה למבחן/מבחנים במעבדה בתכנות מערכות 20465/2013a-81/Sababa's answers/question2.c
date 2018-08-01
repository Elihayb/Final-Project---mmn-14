#include <stdio.h>

#define MAX_ZERO_BITS(A,B,T){\
	T mask = 1;\
	int count1 = 0;\
	int count2 = 0;\
	while(mask){\
		if(!(A & mask)){\
			count1++;\
		}\
		if(!(B & mask)){\
			count2++;\
		}\
		mask <<= 1;\
	}\
	if(count2 > count1){\
		B = count2;\
		A = 0;\
	}else{\
		A = count1;\
		B = 0;\
	}\
}

void intToBinStr(int num, char* strBIT){
    int i;
    int value = num;
    strBIT[32] = '\0';
    for (i = 31; i >= 0; --i, value >>= 1)
    {
        strBIT[i] = '0'+(value & 1);
    }
}

int arrMaxZeroBits(int * arr){
	int result = 0,i,a,b;
	for(i = 1;i < 8;i++){
		a = arr[result];
		b = arr[i];
		MAX_ZERO_BITS(a,b,int);
		if(b > a){
			result = i;;
		}
	}

	return result;
}

int main(int argc, char **argv) {
	printf("\n------------ Question A ------------\n");
	char aBIN[33];
	char bBIN[33];

	int a = 11;
	int b = 15;
	intToBinStr(a,aBIN);
	intToBinStr(b,bBIN);
	printf("a: %s\n",aBIN);
	printf("b: %s\n",bBIN);
	MAX_ZERO_BITS(a,b,int);
	if(b > a){
		printf("b is big - %d", b);
	}else{
		printf("a is big - %d", a);
	}
	printf("\n------------ Question B ------------\n");
	int arr[] = {33,15,45,12,1,74,58,22};
	int result = arrMaxZeroBits(arr);
	printf("\nresult: %d",result);

	return 0;
}
