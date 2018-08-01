#include <stdio.h>
#define BUF_LEN 200
#define LINE_NUMBER 3
int line_len( char *filename, int n )
{
	FILE *f;
	char buf[BUF_LEN];
	int j, i=0;
	if( (f = fopen( filename, "r" )) )
	{
	for( j = 0; j < n; j++ )
		fgets( buf, BUF_LEN, f );
	for( i = 0; buf[i]; i++ ) /* find end of buf */;
		fclose(f);
	}
	return i;
}

int main()
{
printf( "%d\n", line_len( "text.txt", LINE_NUMBER ) );
return 0;
}
