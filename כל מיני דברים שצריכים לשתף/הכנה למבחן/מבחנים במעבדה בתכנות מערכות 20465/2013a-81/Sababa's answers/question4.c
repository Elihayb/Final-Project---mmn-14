#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct suppliers *sup;
typedef struct suppliers{
	int number;
	int month;
	int money;
	sup next;
}su;

void equal(sup A, sup B){
	int mark = 0;
	int count = 0;
	while(A != NULL && B != NULL){
		if(A->number != B->number){
			mark++;
		}
		count++;
		A = A->next;
		B = B->next;
	}
	if(!mark && !A && !B){
		printf("\nlist equals");
	}else if(mark == count){
		printf("\nlist not equals");
	}else{
		printf("\nlist equals partially");
	}
}

void freeList(sup head){
	sup temp = head;;
	while(head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
}

int main(int argc, char **argv) {
	/*a1*/
	sup a = (sup)malloc(sizeof(su));
	a->number = 14;
	a->next = (sup)malloc(sizeof(su));
	a->next->number = 150;
	a->next->next = NULL;
	/*b*/
	sup b = (sup)malloc(sizeof(su));
	b->number = 14;
	b->next = (sup)malloc(sizeof(su));
	b->next->number = 150;
	b->next->next = NULL;
	/*c*/
	sup c = (sup)malloc(sizeof(su));
	c->number = 15;
	c->next = (sup)malloc(sizeof(su));
	c->next->number = 150;
	c->next->next = NULL;
	/*d*/
	sup d = (sup)malloc(sizeof(su));
	d->number = 34;
	d->next = (sup)malloc(sizeof(su));
	d->next->number = 90;
	d->next->next = NULL;

	printf("\na == b:");
	equal(a,b); /* equals */
	printf("\na == c:");
	equal(a,c); /* partially */
	printf("\na == d:");
	equal(a,d); /* not equals */

	freeList(a);
	freeList(b);
	freeList(c);
	freeList(d);

	return 0;
}
