#include <stdio.h>

void func(char * str){
	printf("%s",str);
}

int main(int argc, char **argv) {

	char str[] = "lala";
	int x = (int)&str;
	printf("%d == %d\n",x,(int)&str);
	func((x));
	return 0;
}
