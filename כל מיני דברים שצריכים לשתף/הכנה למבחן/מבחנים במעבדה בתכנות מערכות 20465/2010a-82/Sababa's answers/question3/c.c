#include <stdio.h>
enum party{a,b,c};
struct ABC
{const char *name;party affil;}A[]=
{
		{"Dan Smith",b},
		{"Jack Cohen",a},
		{"Mary Brown",c}
		/*...*/
};
int main()
{
	struct ABC *p;
	for(p=A;p;p++)
	{
		if(p->affil == c)
			printf("%s(c)\n",p->name);
	}
	return 0;
}
