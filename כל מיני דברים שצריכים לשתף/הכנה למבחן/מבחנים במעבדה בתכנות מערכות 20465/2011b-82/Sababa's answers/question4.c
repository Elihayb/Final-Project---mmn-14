#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum{false,true}bool;

typedef struct guest * guep;
typedef struct guest{
	int number;
	char * name;
	bool approval;
	int guestsC;
	guep next;
}gue;

guep _head = NULL;

void add(guep item){
	item->next = _head;
	_head = item;
}

void reverse(){
	if(_head == NULL || _head->next == NULL){
		return;
	}

	guep temp;
	guep newHead = _head;
	_head = _head->next;
	newHead->next = NULL;

	while(_head->next != NULL){
		temp = _head;
		_head = _head->next;
		temp->next = newHead;
		newHead = temp;
	}
	_head->next = newHead;
}

void printList(){
	guep prv = _head;
	while(prv != NULL){
		printf("%d\n",prv->number);
		prv = prv->next;
	}
}

void freeList(){
	guep temp;
	while(_head != NULL){
		temp = _head;
		_head = _head->next;
		free(temp);
	}
}

int main(int argc, char **argv) {

	guep a1 = (guep)malloc(sizeof(gue));
	a1->number = 45;
	add(a1);
	guep a2 = (guep)malloc(sizeof(gue));
	a2->number = 31;
	add(a2);
	guep a3 = (guep)malloc(sizeof(gue));
	a3->number = 93;
	add(a3);
	guep a4 = (guep)malloc(sizeof(gue));
	a4->number = 65;
	add(a4);
	guep a5 = (guep)malloc(sizeof(gue));
	a5->number = 78;
	add(a5);

	printf("list befor reverse:\n");
	printList();

	reverse();

	printf("list after reverse:\n");
	printList();

	freeList();

	return 0;
}
