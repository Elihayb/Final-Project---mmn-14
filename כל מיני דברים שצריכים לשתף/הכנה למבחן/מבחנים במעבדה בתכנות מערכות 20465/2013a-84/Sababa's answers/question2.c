#include <stdio.h>

#define NUM_BITS(X,Y,COUNT){\
	unsigned long int mask = 1;\
	COUNT = 0;\
	while(mask){\
		if((X & mask)&& (Y & mask)){\
			COUNT++;\
		}\
		mask <<= 1;\
	}\
}

#define NUM_BITS2(X,Y,COUNT){\
	unsigned long int mask = (X & Y);\
	COUNT = 0;\
	while(mask){\
		if((mask & 1)){\
			COUNT++;\
		}\
		mask >>= 1;\
	}\
}

void intToBinStr(int num, char* binSTR){
	int i;
	int value = num;
	binSTR[32] = '\0';
	for (i = 31; i >= 0; --i, value >>= 1){
		binSTR[i] = (value & 1) + '0';
	}
}

void arrNumBits(int y, int * arr, int * result ){
	int i;
	int count;
	for(i = 0; i < 7; i++){
		NUM_BITS2(arr[i],y,count);
		result[i] = count;

	}
}

int main(int argc, char **argv) {
printf("\n--------------- question A ---------------\n");
	int x = 85;
	int y = 105;
	char xstr[33];
	char ystr[33];
	intToBinStr(x,xstr);
	intToBinStr(y,ystr);
	printf("%s\n",xstr);
	printf("%s\n",ystr);
	int count = 0;
	NUM_BITS2(x,y,count);
	printf("x & y count: %d\n",count);

printf("\n--------------- question B ---------------\n");
	int arr[] = {53,8,94,69,45,17,72};
	int result[7];
	arrNumBits(y,arr,result);
	char str[33];
	int i;
	intToBinStr(y,str);
	printf(" y %s\n",str);
	for(i = 0; i < 7;i++){
		intToBinStr(arr[i],str);
		printf("%d) %s | arr[%d] & y count: %d\n",i,str,i,result[i]);
	}
	return 0;
}
