#include <stdlib.h>

int main(int argc, char **argv) {
	int **p1;
	int **p2;
	p1 = (int **)malloc(100*sizeof(int *));
	p2 = p1;
	p1 = (int **)malloc(100*sizeof(int *));

	if(p1 == NULL)
	{
		puts("Fail allocation error");
		exit(1);
	}

	int i;
	for(i=0;i<100;i++)
		p1[i]=p2[i];

	free(p2);

	return 0;
}
