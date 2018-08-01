#include <stdio.h>

int main(int argc, char **argv) {

	typedef struct d{
		int g;
		int h;
	}f;

	f b = {4};
	printf("%d",b.h);

	return 0;
}

