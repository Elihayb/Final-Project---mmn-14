#include <stdio.h>
#include <stddef.h>
#include <string.h>

typedef enum{TREE,METAL,STONE,PLASTIC}mat;

typedef struct furniture * furp;
typedef struct furniture{
	char * name;
	mat material;
	int weight;
	int manufacturer;
	furp next;
}fur;

typedef enum{LONG,SHORT,NAN}war;

typedef struct manufacturer{
	char * name;
	char * phone;
	war warranty;
}man;

man manTable[] = {
		{"a1","1890-926-7319",LONG},
		{"a2","1890-048-4952",NAN},
		{"a3","1890-210-7893",NAN},
		{"a4","1890-592-5736",LONG},
		{"a5","1890-315-1058",SHORT}
};

furp _head = NULL;

void push(furp item){
	item->next = _head;
	_head = item;
}

furp pop(){
	furp temp = _head;
	_head = _head->next;
	return temp;
}

void find(char * name){
	furp prv = _head;
	int count = 0;
	while(prv != NULL){
		if(!strcmp(name,prv->name)){
			printf("name: %s\n"
					"material: %d\n"
					"weight: %d\n"
					"manufacturer: %s\n"
					"---------------\n",prv->name,prv->material,prv->weight,manTable[prv->manufacturer].name);
			count++;
		}
		prv = prv->next;
	}
	printf("find %d %s in the list",count,name);
}

int main(int argc, char **argv) {

	fur a1 = {"a1",PLASTIC,89,0};
	fur a2 = {"a2",TREE,12,1};
	fur a3 = {"table",STONE,124,3};
	fur a4 = {"a4",METAL,2,0};
	fur a5 = {"a5",TREE,95,3};
	fur a6 = {"table",TREE,30,2};
	push(&a1);
	push(&a2);
	push(&a3);
	push(&a4);
	push(&a5);
	push(&a6);

	find("table");
	return 0;
}
