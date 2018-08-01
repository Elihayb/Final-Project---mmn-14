#include <stdio.h>
#include <string.h>

void print( const char * );
int main()
{
print( "Dina Romney" );
print( "Bill Genovich" );
print( "Rina Banshoon" );
print( "Dan Paul" );
return 0;
}
void print( const char *name )
{
int indent = 100 / (strlen(name) - 8) / 2;

for( int i = 0; i < indent; i++ )
printf( " " );
printf( "%s\n", name );
}
