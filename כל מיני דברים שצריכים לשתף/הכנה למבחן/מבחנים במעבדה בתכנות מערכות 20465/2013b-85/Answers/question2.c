#include <stdio.h>

#define FIND(VALUE,ARR,INDEX){\
	int i;\
	INDEX = -1;\
	for(i = 0;i <sizeof(ARR)/sizeof(VALUE); i++){\
		if(ARR[i] == VALUE){\
			INDEX = i;\
		}\
	}\
\
}

int main(int argc, char **argv) {
	int arr[] = {2,5,7,88,9,11};
	int index;
	FIND(7,arr,index);

	if(index != -1){
		printf("%d in index: %d\n",arr[index],index);
	}else{
		printf("the value is not found!\n");
	}

	return 0;
}
