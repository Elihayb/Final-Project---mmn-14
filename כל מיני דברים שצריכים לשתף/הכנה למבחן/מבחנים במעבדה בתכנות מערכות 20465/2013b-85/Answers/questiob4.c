#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef enum{TREE,METAL,STONE,PLASTIC}mat;

typedef struct sculpture * sculp;
typedef struct sculpture{
	char * name;
	mat material;
	int weight;
	int artist;
	sculp next;
}scul;

typedef enum{CONPERE,PARTIAL,NAN}insu;

typedef struct artist{
	char * name;
	char * phone;
	insu insurance;
}art;

sculp _head = NULL;
art artTable[] = {
		{"a1","1822-25488-942",CONPERE},
		{"a1","1822-87634-355",PARTIAL},
		{"a1","1822-43278-456",CONPERE},
		{"a1","1822-13543-954",NAN}
};

sculp pop(){
	if(_head == NULL){
		return NULL;
	}
	sculp temp = _head;
	_head = _head->next;
	return temp;
}

void push(sculp item){
	item->next = _head;
	_head = item;
}

void count(char * name){
	int count = 0;
	sculp prv = _head;
	while(prv != NULL){
		if(!strcmp(name,prv->name)){
			printf("name: %s\n"
					"material: %d\n"
					"weight: %d\n"
					"artist: %s\n"
					"---------------\n",prv->name,prv->material,prv->weight,artTable[prv->artist].name);
			count++;
		}
		prv = prv->next;
	}
	printf("find count: %d\n",count);
}

void freeAll(){
	sculp prv = _head;
	sculp temp;
	while(prv != NULL){
		temp = prv;
		prv = prv->next;
		free(temp);
	}
}

int main(int argc, char **argv) {



	sculp a1 = (sculp)malloc(sizeof(scul));
	char name1[] = "no name";
	a1->name = name1;
	a1->material = METAL;
	a1->weight = 20;
	a1->artist = 2;
	push(a1);

	sculp a2 = (sculp)malloc(sizeof(scul));
	char name2[] = "lala";
	a2->name = name2;
	a2->material = TREE;
	a2->weight = 25;
	a2->artist = 1;
	push(a2);

	count("no name");
	freeAll();

	return 0;
}
