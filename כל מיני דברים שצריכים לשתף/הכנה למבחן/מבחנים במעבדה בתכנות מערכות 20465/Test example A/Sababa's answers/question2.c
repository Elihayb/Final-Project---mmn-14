#include <stdio.h>

#define ROUND(NUM)(NUM >= 0 ? (int)(NUM+0.5) : (int)(NUM-0.5))

void arrRound(double * arrD, int * arrI,int length){

	int i;
	for(i = 0; i < length;i++){
		arrI[i] = ROUND(arrD[i]);
	}
}

int main(int argc, char **argv) {
	printf("\n--------------------- question A ------------------\n");

	double numD = 5.9;
	int numI = ROUND(numD);
	printf("ROUND(%f) = %d\n",numD,numI);

	printf("\n--------------------- question B ------------------\n");

	double arrD[] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9};
	int arrI[9];
	arrRound(arrD,arrI,sizeof(arrD)/sizeof(double));
	int i;
	for(i = 0; i < 9; i++){
		printf("ROUND(%f) = %d\n",arrD[i],arrI[i]);
	}
	return 0;
}
