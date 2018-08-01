#include <stdio.h>
#include <stddef.h>

typedef enum{FALSE,TRUE}bool;

typedef struct member *memp;
typedef struct member{
	int number;
	char * name;
	bool debt;
	int money;
	memp next;
}mem;

memp _head = NULL;

void add(memp item){
	item->next = _head;
	_head = item;
}

void printList(){
	memp prv = _head;
	while(prv != NULL){
		printf("%d,",prv->number);
		prv = prv->next;
	}
}

void reverse(){
	if(_head == NULL || _head->next == NULL){
		return;
	}


	memp temp;
	memp newHead = _head;
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

int main(int argc, char **argv) {
	mem a1 = {52,"a1",TRUE,1644,NULL};
	mem a2 = {13,"a2",TRUE,1335,NULL};
	mem a3 = {98,"a3",FALSE,1291,NULL};
	mem a4 = {82,"a4",FALSE,1654,NULL};
	mem a5 = {71,"a5",TRUE,1083,NULL};
	mem a6 = {34,"a6",FALSE,1597,NULL};
	add(&a1);
	add(&a2);
	add(&a3);
	add(&a4);
	add(&a5);
	add(&a6);

	printf("\nlist befor reverse:\n");
	printList();

	reverse();

	printf("\nlist after reverse:\n");
	printList();

	return 0;
}
