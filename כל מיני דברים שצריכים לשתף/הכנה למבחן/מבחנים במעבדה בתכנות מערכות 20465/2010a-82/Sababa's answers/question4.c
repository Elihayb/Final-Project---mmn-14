#include <stdio.h>
#include <stddef.h>

typedef struct tree_node * nodep;
typedef struct tree_node{
	char * name;
	int number;
	nodep left;
	nodep right;
}node;

void preOrder(nodep tree){
	printf("%d,",tree->number);
	if(tree->left)
		preOrder(tree->left);
	if(tree->right)
		preOrder(tree->right);
}

void inOrder(nodep tree){
	if(tree->left)
		inOrder(tree->left);
	printf("%d,",tree->number);
	if(tree->right)
		inOrder(tree->right);
}

void postOrder(nodep tree){

	if(tree->left)
		postOrder(tree->left);
	if(tree->right)
		postOrder(tree->right);
	printf("%d,",tree->number);
}

int main(int argc, char **argv) {
	node n9 = {"name9",9,NULL,NULL};
	node n8 = {"name8",8,NULL,NULL};
	node n7 = {"name7",7,NULL,NULL};
	node n6 = {"name6",6,&n8,&n9};
	node n5 = {"name5",5,NULL,&n7};
	node n4 = {"name4",4,NULL,NULL};
	node n3 = {"name3",3,&n5,&n6};
	node n2 = {"name2",2,&n4,NULL};
	node n1 = {"name1",1,&n2,&n3};

	printf("\npreorder:\n");
	preOrder(&n1); /* 1,2,4,3,5,7,6,8,9 */


	printf("\ninorder:\n");
	inOrder(&n1);
	printf("\npostorder:\n");
	postOrder(&n1);
	return 0;
}
