#include <stdio.h>
#include <stdlib.h>

typedef struct _member {
	int number;
	int value;
	int time;
	struct _member *next;
	struct _member *prev;
} member;

member *list; //global variable

void print_list () { // for debug purposes only I didn't put it on test
	member *current=list;
	while (current!=NULL){
		printf("%d ", current->number);
		current=current->next;
	}
	printf("\n");
}

void print_list_reverse () {// for debug purposes only I didn't put it on test
	member *current=list;
	if (list==NULL) return;
	while (current->next!=NULL)
		current=current->next;
	while (current!=NULL){
		printf("%d ", current->number);
		current=current->prev;
	}
	printf("\n");
}

int searchDelete (int key) {
	member *current=list;
	while (current!=NULL && current->number !=key)
		current=current->next;
	if (current==NULL) {
		printf("none found!\n");
		return 0;
	}
	if (current == list)
		list = list->next;
	else
		current->prev->next=current->next;
	if (current->next != NULL)
		current->next->prev=current->prev;
	//free(current); // this will not work because I didn't use malloc to create nodes 
	return 1;
}

int main () {
	member m1={11,11,1,NULL,NULL};
	member m2={12,11,1,NULL,&m1};
	member m3={13,11,1,NULL,&m2};
	member m4={14,11,1,NULL,&m3};
	m1.next=&m2;
	m2.next=&m3;
	m3.next=&m4;
	list=&m1;
	print_list();
	print_list_reverse();
	searchDelete(15);
	searchDelete(14);
	print_list();
	print_list_reverse();
	searchDelete(12);
	print_list();
	print_list_reverse();
	searchDelete(11);
	print_list();
	print_list_reverse();
	getchar();
}
	

	
	