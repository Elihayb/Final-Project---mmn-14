#include <stdio.h>

#define double(a,b) { \
	long i,mask; \
	for (i=0,mask=1,b=0; i<8*sizeof(a)-1;i++,mask<<=1) { \
		if ((a&mask) && (a&mask<<1)) {\
			i++; mask<<=1; continue; \
		} \
		b|=(a&mask); \
	} \
	b|=(a&mask); printf("mask=%u\n",mask);\
}

void printbin (unsigned int x) {
	unsigned int i,mask = 0x80000000;
	for (i=0; i<8*sizeof(int); i++, mask>>=1) {
		if (x&mask)
			printf ("1");
		else
			printf("0");
	}
	printf ("\n");
}

int main () {
	int a1=0x53b2fe53,a2=0x7baf6475,a3=0xf6cdba33;
	int b1,b2,b3;
	double (a1,b1)
	double (a2,b2)
	double (a3,b3)
	if (a1!=b1) {
		printbin (a1); //for demo purposes but not on test
		printbin (b1); }
	if (a2!=b2) {
		printbin (a2); //for demo purposes but not on test
		printbin (b2); }
	if (a3!=b3) {
		printbin (a3); //for demo purposes but not on test
		printbin (b3); }
	getchar();
}


