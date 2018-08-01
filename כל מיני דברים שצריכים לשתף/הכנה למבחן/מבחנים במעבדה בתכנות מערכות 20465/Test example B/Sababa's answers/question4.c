#include <stdio.h>
#include <string.h>

#define SWAP(A,B)  A ^= B; B ^= A; A ^= B;
#define MAX_BUF 128

void reverse(char * buf){
	int i, j = strlen(buf)-1;

	for(i= 0;i < j; i++, j--){
		SWAP(buf[i],buf[j]);
	}
}
void inputWord(char * buf){
	printf("input word (max word %d) to end ENTER\n",MAX_BUF);
	scanf("%127s",buf);
}

void inputChar(char * buf){
	int count = 0;
	char c;
	printf("input char (max char %d) to end ^\n",MAX_BUF);
	while((c = getchar()) != '^' && count < MAX_BUF-1){
		buf[count] = c;
		count++;
	}
	buf[count] = '\0';
}

int main(int argc, char **argv) {

printf("\n------------- question a -------------\n");
	char bufA[MAX_BUF];
	inputChar(bufA);
	printf("befor reverse:\n%s\n",bufA);
	reverse(bufA);
	printf("after reverse:\n%s\n",bufA);

printf("\n------------- question b -------------\n");
	char bufB[MAX_BUF];
	inputWord(bufB);
	printf("befor reverse:\n%s\n",bufB);
	reverse(bufB);
	printf("after reverse:\n%s\n",bufB);
	return 0;
}
