#include <stdio.h>
char lower(char c){
	return c >= 'A' && c <= 'Z'?c+'a'-'A':c;
}

int main(int argc, char **argv) {

	printf("%c\n",lower('F'));
	printf("%c\n",lower('f'));

	return 0;
}
