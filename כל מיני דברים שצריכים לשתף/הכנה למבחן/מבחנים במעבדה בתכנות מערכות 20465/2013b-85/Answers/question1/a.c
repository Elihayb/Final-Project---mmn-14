#include <stdio.h>

void func(double e){
	printf("%d",sizeof(e));
}

int main(int argc, char **argv) {
	int g = 5;
	func(g);
	return 0;
}
