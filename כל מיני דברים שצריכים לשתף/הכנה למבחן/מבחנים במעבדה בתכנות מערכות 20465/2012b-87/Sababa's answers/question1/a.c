#include <stdio.h>

void funcA(){
	return;
}

int main(int argc, char **argv) {

	if(funcA()){/* not compile void not return value */
		printf("return");
	}else{
		printf("not return");
	}
	return 0;
}
