#include <stdio.h>
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
int main(int argc, char **argv)
{
	FILE *fp = fopen(argv[1], "r");
	fseek(fp, -1L, SEEK_END);
	while (ftell(fp)) {
		putchar(fgetc(fp));
		fseek(fp, -2L, SEEK_CUR);
	}
	putchar(fgetc(fp));
}
