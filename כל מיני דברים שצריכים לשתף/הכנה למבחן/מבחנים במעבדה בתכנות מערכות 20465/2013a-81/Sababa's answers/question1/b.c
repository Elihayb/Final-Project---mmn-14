#include <stdio.h>
#define A 5
//const int a = 5;

int main(int argc, char **argv) {

	if(A == 5){
		const int a = 5;
	}
	int arr[A+a];
	arr[9] = 55;

	printf("%d",arr[9]);
	return 0;
}
