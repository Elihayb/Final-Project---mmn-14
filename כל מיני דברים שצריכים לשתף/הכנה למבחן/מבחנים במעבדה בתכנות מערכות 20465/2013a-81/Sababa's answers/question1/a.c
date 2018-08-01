#include <stdio.h>

int main(int argc, char **argv) {

	float x = 20.5;
	float y = 4.0;
	float z = x%y;/* working only of int */
	float a = (int)x%(int)y
	printf("%f",z);
	return 0;
}
