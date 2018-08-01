#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef enum {a,b,c,d,e,f}st; /* stations */

typedef struct member * memp;
typedef struct member{
	char * name;
	char * phone;
	char * address;
}mem;

typedef struct subscribers * subp;
typedef struct subscribers{
	int number;
	int member; /* in member table */
	int countTake;
	st lastStation;
	subp next;
	subp prev;
}sub;

mem memberTable[] = {
		{"bob M","054-7892432","tel-aviv"},
		{"bill G","054-3849845","modiin"},
		{"roy D","054-5465466","tel aviv"},
		{"david P","054-3628754","bar sheva"},
		{"jon F","054-2746705","jerusalem"},
		{"gel D","054-3458903","jerusalem"}
};

subp _head = NULL;

void add(subp item){
	if(_head == NULL){
		_head = item;
		_head->next = item;
		_head->prev = item;
	}else{
		item->next = _head;
		item->prev = _head->prev;
		_head->prev->next = item;
		_head->prev = item;
	}
}

void fileToList(char * fName){

	FILE * file = fopen(fName,"r");
	if(!file){
		fprintf(stderr,"error: file");
		exit(1);
	}

	while(!feof(file)){
		subp item = (subp)malloc(sizeof(sub));
		if(!item){
			fprintf(stderr,"error: memory");
			exit(1);
		}
		fscanf(file,"%d,%d,%d,%d,\n",&item->number,&item->member,&item->countTake,&item->lastStation);
		add(item);
	}
}

void maxTakeMember(){
	if(_head == NULL){
		printf("List is NULL.");
		return;
	}
	int index = 1;
	subp prv = _head->next;
	subp max = _head;
	int maxLoc = 0;
	do{
		if(prv->countTake > max->countTake){
			max = prv;
			maxLoc = index;
		}
		index++;
		prv = prv->next;
	}while(prv != _head);

	printf("max take %d in loc %d in list\n",max->countTake,maxLoc);
	printf("member details:\n"
			"name: %s\n"
			"phone: %s\n"
			"address: %s\n",memberTable[max->member].name,memberTable[max->member].phone,memberTable[max->member].address);
}

void printList(){
	if(_head == NULL){
		printf("List is NULL.");
		return;
	}

	subp prv = _head;
	do{
		printf("subscriptions %d:\n"
				"last station: %d\n"
				"take: %d\n",prv->number,prv->lastStation,prv->countTake);
		printf("member details:\n"
					"name: %s\n"
					"phone: %s\n"
					"address: %s\n",memberTable[prv->member].name,memberTable[prv->member].phone,memberTable[prv->member].address);
		printf("----------------\n");
		prv = prv->next;
	}while(prv != _head);
}

void freeList(){
	if(_head == NULL)
		return;

	_head->prev->next = NULL;
	subp temp;
	while(_head != NULL){
		temp = _head;
		_head = _head->next;
		free(temp);
	}
}

int main(int argc, char **argv) {

	if(argc < 2){
		fprintf(stderr,"error: args - question4 <data.csv>");
		exit(1);
	}
	fileToList(argv[1]);
	printList();
	maxTakeMember();
	freeList();
	return 0;
}
