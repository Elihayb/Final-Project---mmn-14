#include <stdio.h>
#include <string.h>
enum type {H=1/* herbivore */,C=2/* carnivore */,
			S=4/* sweet tooth */,D=8/* Drinker */};

char * dish(int x)
{
	char buf[100];char *p = buf;*p=0;
	if(x & D)strcat(p,"rum-soaked ");/*H|D*/
	if(x & S)strcat(p,"sugared ");/*C|S*/
	if(x & C)strcat(p,"turkey ");/*C|S*/
	if(x & H)strcat(p,"broccoli ");/*H|D*/
	return p;
}
int main()
{
	printf("please pass the %s and the %s.",
			dish(C|S),dish(H|D));
	return 0;
}
