#include <stdio.h>
#include <stddef.h>

#define MAX_LIST 16

typedef struct employee * emp;
typedef struct employee{
	int number;
	int year;
	int class;
	emp next;
	emp prev;
}em;

typedef struct classes{
	char * name;
	char * admin;
	char * phone;

}cls;

cls classTable[] = {
		{"class1","admin3","182-127-9173"},
		{"class2","admin63","182-497-9261"},
		{"class3","admin14","182-920-0913"},
		{"class4","admin9","182-843-2468"},
		{"class5","admin12","182-002-4568"},
};

emp listTable[MAX_LIST];

void printList(int listNum){
	if(listTable[listNum] == NULL)
		return;
	emp prv = listTable[listNum];
	do{
		printf("%d,",prv->number);
		prv = prv->next;
	}while(prv != listTable[listNum]);

}

void add(int listNum ,emp node){

	if(listTable[listNum] == NULL){
		node->next = node;
		node->prev = node;
		listTable[listNum] = node;
	}else{
		emp head = listTable[listNum];
		node->next = head;
		node->prev = head->prev;
		head->prev->next = node;
		head->prev = node;
	}
}

void AandBtoA(int a,int b){
	if(listTable[a] == NULL){
		listTable[a] = listTable[b];
		listTable[b] = NULL;
		return;
	}else if(listTable[b] == NULL){
		return;
	}

	emp prvA = listTable[a];
	emp prvB = listTable[b];
	emp temp;
	prvB->prev->next = NULL;
	while(prvB != NULL){

		if(prvA->number > prvB->number){
			temp = prvB->next;
			prvB->next = prvA;
			prvB->prev = prvA->prev;
			prvB->next->prev = prvB;
			prvB->prev->next = prvB;
			prvB = temp;
		}else{
			prvA = prvA->next;
		}
	}

	if(listTable[a]->number > listTable[a]->prev->number){
		listTable[a] = listTable[a]->prev;
	}

	listTable[b] = NULL;
}

int main(int argc, char **argv) {

	em a1 = {3,1,2,NULL,NULL};
	em a2 = {6,3,2,NULL,NULL};
	em a3 = {33,5,2,NULL,NULL};
	em a4 = {102,2,2,NULL,NULL};
	add(0,&a1);

	add(0,&a2);
	add(0,&a3);
	add(0,&a4);

	em b1 = {1,1,2,NULL,NULL};
	em b2 = {67,1,2,NULL,NULL};
	em b3 = {79,1,2,NULL,NULL};
	em b4 = {91,1,2,NULL,NULL};
	add(1,&b1);
	add(1,&b2);
	add(1,&b3);
	add(1,&b4);

	int a = 0;
	printf("\nlist a:\n");
	printList(a);

	int b = 1;
	printf("\nlist b:\n");
	printList(b);

	AandBtoA(a,b);

	printf("\nlist a:\n");
	printList(a);

	return 0;
}
