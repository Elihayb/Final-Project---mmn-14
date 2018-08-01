#include <stdio.h>
#include <stdlib.h>

#define COUNT_ODD_ZERO(NUM,COUNT){\
	COUNT = 0;\
	while(NUM){\
		if((NUM & 1)){\
			count++;\
		}\
		NUM >>= 2;\
	}\
}

void intToBinStr(int num, char* strBIN){
    int i;
    int value = num;
    strBIN[32] = '\0';
    for (i = 31; i >= 0; --i, value >>= 1)
    {
        strBIN[i] = '0'+(value & 1);
    }
}


int countOddZero(char num){
	int count = 0;
	while((num >>= 2)){
		if(((num>>1) & 1)){
			count++;
		}
	}
	return count;
}

int * sumArrCountOddZero(int * arr){
	int i;
	int * arrC = (int*)malloc(sizeof(int)*10);
	int num;
	int count;
	for(i = 0; i < 10; i++){
		num = arr[i];
		COUNT_ODD_ZERO(num,count);
		arrC[i] = count;
	}

	return arrC;
}

int main(int argc, char **argv) {
	printf("\n--------------- question a ---------------\n");
	char str[33];
	intToBinStr(125,str);
	printf("\n%s",str);
	int count;
	char a = 125;
	COUNT_ODD_ZERO(a,count);
	printf("\ncount: %d",count);

	printf("\n--------------- question b ---------------\n");
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	int * arrC = sumArrCountOddZero(arr);
	int i;
	char strC[33];
	for(i = 0; i < 10; i++){
		intToBinStr(arr[i],strC);
		printf("%s | %d \n",strC,arrC[i]);
	}
	return 0;
}
