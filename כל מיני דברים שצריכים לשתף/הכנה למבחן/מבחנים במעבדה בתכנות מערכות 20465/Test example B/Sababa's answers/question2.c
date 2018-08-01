#include <stdio.h>

int find_c(char * str, char c){
	int count;
	while(*str){
		if(*str == c){
			count++;
		}
		str++;
	}
	return count;
}

int main(int argc, char **argv) {
	char str[] = "fighjudredifind";
	char c = 'd';
	int count = find_c(str,c);
	printf("string: '%s', find: '%c', count: %d",str,c,count);
	return 0;
}
