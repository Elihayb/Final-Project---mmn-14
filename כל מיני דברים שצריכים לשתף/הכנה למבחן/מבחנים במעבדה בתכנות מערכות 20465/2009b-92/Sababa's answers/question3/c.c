#include <stdio.h>
#include <string.h>

unsigned a[100] = {0};

int main()
{
	char buf[200];
	unsigned n = 0;

	while(fgets(buf, 200, stdin))
	{
		if(n < 100)a[n++] = strlen(buf);
	}
	while(--n >= 0)
	{
		printf("%d\n",a[n]);
	}
	return 0;
}
