#include <stdio.h>

int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

int sum(int a[3][3]){
	int i = 0,j = 0,k = 0;;

	for(i = 0; i < 3; i++){
		for(i = 0; i < 3; i++){
			k += a[i][j];
		}
	}
	return k;
}

int main(int argc, char **argv) {
	printf("sum: %d",sum(a));
	return 0;
}
