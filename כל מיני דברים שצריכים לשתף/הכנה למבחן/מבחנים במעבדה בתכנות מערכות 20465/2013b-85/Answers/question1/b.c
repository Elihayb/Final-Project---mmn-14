#include <stdio.h>

int main(int argc, char **argv) {
	int x = 1234567;
	int y = 1234567;
	int *p;
	p = ((int)(&x)-1);
	printf("x = %d y = %d\n",&x,&y);
	printf("p: %d = %d",(int)(&x)-1,*p);
	return 0;
}
