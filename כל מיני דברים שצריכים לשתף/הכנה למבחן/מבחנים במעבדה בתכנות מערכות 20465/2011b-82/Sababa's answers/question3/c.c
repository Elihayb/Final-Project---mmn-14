const int KMAX = 30;
double q[KMAX];

void f(double limit)
{
	double s = 1;
	int k = 0;
	q[0]=0;
	while(q[k]<=limit&&k<KMAX)
	{
		k++;
		s = s *(k+1);
		q[k]=q[k-1]+s;
	}
}
