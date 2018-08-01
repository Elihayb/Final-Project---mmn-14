#include <stdio.h>

#define MORE_ZERO_BITS(A,B){	\
	int mask = 1;				\
	int countA = 0,countB = 0;	\
	while(mask){				\
		if(!(mask & A))			\
			countA++;			\
		if(!(mask & B))			\
			countB++;			\
		mask <<=1;				\
	}							\
	if(countB > countA){		\
		B = countB;				\
		A = 0;					\
	}else{						\
		A = countA;				\
		B = 0;					\
	}							\
}								

void intToBinStr(int num, char* binSTR){
	int i;
	int value = num;
	for (i = 31; i >= 0; --i, value >>= 1){
		binSTR[i] = '0'+(value & 1);
	}

	binSTR[32] = '\0';
}

int arrMoreZeroBits(int * arr){
	int i;
	int index = 0;
	int a;
	int b;
	for(i = 1; i < 8;i++){
		a = arr[index];
		b = arr[i];
		MORE_ZERO_BITS(a,b);
		if(b > a){
			index = i;
		}
	}

	return index;
}
int main(int argc, char **argv) {

printf("\n--------------------- question A ------------------\n");
int a = 92;
int b = 126;
char strA[33];
char strB[33];
intToBinStr(a,strA);
intToBinStr(b,strB);
printf("a: %s\nb: %s\n",strA,strB);
MORE_ZERO_BITS(a,b);
if(b > a){
	printf("b have more zero count: %d",b);
}else{
	printf("a have more zero count: %d",a);
}

printf("\n--------------------- question B ------------------\n");
	int arr[] = {45,26,89,1,94,13,86,102};
	int result = arrMoreZeroBits(arr);
	printf("more zero bits in index: %d",result);
	return 0;
}
