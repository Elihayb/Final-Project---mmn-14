#include <stdio.h>
#define MESSAGE3 3
#define MESSAGE4 4
#define MESSAGE5 5
void f( int i )
{
if( i != MESSAGE4 || i != MESSAGE5 ) return;
printf ( "hello hello \n" );
}

int main()
{
f(MESSAGE3);
f(MESSAGE4);
f(MESSAGE5);
return 0;
}
