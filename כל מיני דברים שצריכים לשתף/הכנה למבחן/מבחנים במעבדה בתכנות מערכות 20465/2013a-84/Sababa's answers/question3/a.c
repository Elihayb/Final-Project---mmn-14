#include <stdio.h>

char *my_scopy(char *s1, char *s2)
{
	*s1 = *s2;

	if (*s2 != '\0')
	my_scopy(s1+1, s2+1);

	return (s1);
}

void main()
{
	char s[100];

	my_scopy(s, "abcdefghi");
	puts(s);

}
