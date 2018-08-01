#include <stdio.h>

int main(int argc, char **argv) {
	int arr[]={1,2,3,4};
	int * d = arr;
	int * e = arr+1;
	printf("\n%d",e-d);

	return 0;
}
