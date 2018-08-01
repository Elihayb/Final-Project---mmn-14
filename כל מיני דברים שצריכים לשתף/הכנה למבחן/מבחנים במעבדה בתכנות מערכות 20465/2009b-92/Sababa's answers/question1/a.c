#include <stdio.h>

int main(int argc, char **argv) {
	int a = 8;
	int b = &a;
	printf("\na address: %d",(int)b);
	int * p = &a;
	printf("\np address: %d",(int)p);
	printf("\np value: %d",*p);
	return 0;
}
