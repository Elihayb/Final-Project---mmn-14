#include <stdio.h>

void intToBinStr(int num, char* binSTR){
	int i;
	int value = num;
	binSTR[32] = '\0';
	for (i = 31; i >= 0; --i, value >>= 1){
		binSTR[i] = (value & 1) + '0';
	}
}

void charToBinStr(int num, char* binSTR){
	int i;
	int value = num;
	binSTR[8] = '\0';
	for (i = 7; i >= 0; --i, value >>= 1){
		binSTR[i] = (value & 1) + '0';
	}
}
int main(int argc, char **argv) {

	unsigned int a = 1023;
	unsigned char b = a;
	char strA[33];
	char strB[9];
	printf("int: %d ,char: %d\n",a,b);
	intToBinStr(a,strA);
	charToBinStr(b,strB);

	printf("a: %s\nb: %s",strA,strB);

	return 0;
}
