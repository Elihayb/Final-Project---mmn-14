#define NUM 500

int arr[NUM];
int *get_end(int);

int main()
{
	for(int *p = arr;p < get_end(NUM+1);p++)
	{
		*p=1; //initiallize array to 1
	}
	return 0;
}

int *get_end(int n)
{
	return arr+n;
}
