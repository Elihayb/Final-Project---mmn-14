
struct My_data {
int Books:1,
Pens:1,
Red:1,
Green:1;
/*etc*/
};
#define N 18
struct My_data Arr_data[N];

int Number_of_Books()
{
	int nof = 0;
	for( int i = 0; i < N; i++ )
	if( Arr_data[i].Books > 0 ) nof++;
	return nof;
}
