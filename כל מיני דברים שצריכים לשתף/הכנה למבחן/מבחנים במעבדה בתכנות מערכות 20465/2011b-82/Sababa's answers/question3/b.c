int a[100];

void f(int n)
{
	int i;
	int sum = 0;
	int *p;
	p = &a[0];
	a[10]=0;
	for(i=0;i<n;i++)
	{
		p=&a[i];
		sum+=a[i];
		if(i>a[i])break;
	}
	*p=sum;
}

