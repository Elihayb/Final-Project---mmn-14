#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF 128
#define MAX_NAME 32

typedef enum{
	LECTURE,SCREENING,MEETING
}typeRoom;

typedef struct room_order * rop;
typedef struct room_order{
	int number;
	char name[MAX_NAME];
	typeRoom type;
	int hour;
	rop next;
}ro;

rop _list = NULL;

void add(rop order){
	if(_list == NULL){
		_list = order;
		order->next = order;
	}else{
		order->next = _list->next;
		_list->next = order;
	}
}

void readOrder(FILE * file){
	char buf[MAX_BUF];
	rop temp;
	while(!feof(file)){
		if(!fgets(buf,MAX_BUF,file)){
			continue;
		}
		temp = (rop)malloc(sizeof(ro));
		if(!temp){
			fprintf(stderr,"error: memory");
			exit(1);
		}

		char * p;
		p = strtok(buf," ,");
		temp->number = atoi(p);
		p = strtok(NULL," ,");
		strcpy(temp->name,p);
		p = strtok(NULL," ,");
		temp->type = atoi(p);
		p = strtok(NULL," ,");
		temp->hour = atoi(p);
		add(temp);
	}
}

void findMinNum(){
	if(_list == NULL){
		fprintf(stderr,"error: list null");
		return;
	}

	rop prv = _list;
	rop min = _list;
	while(prv->next != _list){
		if(min->number > prv->number){
			min = prv;
		}
		prv = prv->next;
	}
	printf("\nmin number of order:\n");
	printf("number: %d \n",min->number);
	printf("name: %s \n",min->name);
	printf("type: %d \n",min->type);
	printf("hour: %d \n",min->hour);
}

void freeList(){
	rop prv = _list;
	rop temp;
	while(prv->next != _list){
		temp = prv;
		prv = prv->next;
		free(temp);
	}
}

int main(int argc, char **argv) {

	if(argc != 2){
		fprintf(stderr,"error: args - question4.c <data.txt>");
		exit(1);
	}

	FILE * file = fopen(*(argv+1),"r");

	if(!file){
		fprintf(stderr,"error: file");
		exit(1);
	}
	readOrder(file);
	findMinNum();
	freeList();
	return 0;
}
