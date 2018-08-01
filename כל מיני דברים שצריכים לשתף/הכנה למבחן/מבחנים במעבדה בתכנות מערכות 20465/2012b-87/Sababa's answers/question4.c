#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct members * memp;
typedef struct members{
	int number;
	int money;
	int month;
	memp next;
	memp prev;
}mem;

memp head = NULL;

void delete(memp member){
	memp prv = head;
	while(prv != NULL){
		if(prv->number == member->number){
			prv->prev->next = prv->next;
			prv->next->prev = prv->prev;
			free(prv);
			printf("\nmember number is delete from the list");
			return;
		}
		prv = prv->next;
	}
	printf("\nmember number not found in the list");
}

void add(memp member){
	if(head != NULL){
		head->prev = member;
		member->next = head;
		head = member;
	}else{
		head = member;
		member->prev = NULL;
		member->next = NULL;
	}
}

void freeList(){
	memp temp;
	while(head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}
}

int main(int argc, char **argv) {
	memp a1 = (memp)malloc(sizeof(mem));
	a1->number = 1254;
	a1->money = 120;
	a1->month = 12;
	add(a1);

	memp a2 = (memp)malloc(sizeof(mem));
	a2->number = 1111;
	a2->money = 129;
	a2->month = 6;
	add(a2);

	memp a3 = (memp)malloc(sizeof(mem));
	a3->number = 989;
	a3->money = 115;
	a3->month = 20;
	add(a3);

	memp a4 = (memp)malloc(sizeof(mem));
	a4->number = 4895;
	a4->money = 100;
	a4->month = 1;
	add(a4);

	printf("\nfirst time delete a3:");
	delete(a3);
	printf("\nsecond time delete a3:");
	delete(a3);
	freeList();

	return 0;
}
