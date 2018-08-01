#include <stdio.h>

#define NUM_BITS(X,Y,COUNT){		\
	int  mask = 1;					\
	COUNT = 0;						\
	while(mask){					\
		if((x & mask)&&(Y & mask)){	\
			COUNT++;				\
		}							\
		mask <<= 1;					\
	}								\
}

void intToBinStr(int num, char* binSTR){
	int i;
	int value = num;
	for (i = 31; i >= 0; --i, value >>= 1){
		binSTR[i] = '0'+(value & 1);
	}
	binSTR[32] = '\0';
}

void arrNumBits(int y,int * arrB,int * arrC){
	int i;
	int count;
	int x;
	for(i = 0; i < 7; i++){
		x = arrB[i];
		NUM_BITS(y,x,count);
		arrC[i] = count;
	}
}
int main(int argc, char **argv) {

printf("\n--------------------- question A ------------------\n");
	int x = 63;
	int y = 127;
	char strX[33];
	char strY[33];
	intToBinStr(x,strX);
	intToBinStr(y,strY);
	printf("x: %s \ny: %s\n",strX,strY);
	int count;
	NUM_BITS(x,y,count);
	printf("num bits: %d\n",count);
printf("\n--------------------- question B ------------------\n");
	int arrB[] = {45,71,97,39,102,25,6};
	int arrC[7];
	arrNumBits(y,arrB,arrC);
	printf(" y %s\n",strY);
	int i;
	for(i = 0; i < 7; i++){
		intToBinStr(arrB[i],strX);
		printf("%d) %s arr[%d] count: %d\n",i,strX,i,arrC[i]);
	}
	return 0;
}
