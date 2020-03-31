/* Erika Ambrioso
	CSE2010
	Assignment 3c 
	Prints tree nodes in pre-order, postorder, in order, and level-order traversals
	with an array implementation
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define MAXSIZE 20


void preorder(char tree[], int); // node is an index to the tree array  
void postorder(char tree[], int); // node is an index to the tree array  
void inorder(char tree[], int); // node is an index to the tree array  
void level_order(char tree[], int); // node is an index to the tree array

int main(void){

char tree[] = {'R', 'S', 'T', 'X', 'Y', 'U', 'V', ' ', ' ', ' ', 'Z', ' ', ' ', 'W', ' '};

level_order(tree, 0);
printf("Pre-order: ");			// print first 2 nodes
preorder(tree, 0);
printf("\nPost order: ");
postorder(tree, 0);
printf("\nIn-order: ");
inorder(tree, 0);
}
/********prints the tree in pre-order traversal**********************************/
void preorder(char tree[MAXSIZE], int node){
	printf("%c ", tree[node]);		//print the node
	
	if((tree[node*2+1] == '\0' && tree[node*2+2] == '\0') || (tree[node*2+1] == ' ' && tree[node*2+2] == ' ')){		// if node has no children
		return;
	}

	//two recursive cases: left and right subtree
	if(tree[node*2+1] != (' '|| '\0')){					//if the left node is empty
		preorder(tree, node*2+1);
	}
	if(tree[node*2 +2] != (' ' || '\0')){					// if the right node is empty
		preorder(tree, node*2+2);
	}

}

/********prints the tree in post-order traversal**********************************/
void postorder(char tree[MAXSIZE], int node){
	if((tree[node*2+1] == '\0' && tree[node*2+2] == '\0') || (tree[node*2+1] == ' ' && tree[node*2+2] == ' ')){		// if node has no children
		printf("%c ", tree[node]);
		return;
	}

	//two recursive cases: left and right subtree
	if(tree[node*2+1] != (' '|| '\0')){					//if the left node is empty
		postorder(tree, node*2+1);
	}
	if(tree[node*2 +2] != (' ' || '\0')){					// if the right node is empty
		postorder(tree, node*2+2);
	}
	printf("%c ", tree[node]);
}
/********prints the tree in in-order traversal************************************/
void inorder(char tree[MAXSIZE], int node){
	if((tree[node*2+1] == '\0' && tree[node*2+2] == '\0') || (tree[node*2+1] == ' ' && tree[node*2+2] == ' ')){		// if node has no children
		printf("%c ", tree[node]);
		return;
	}

	//two recursive cases: left and right subtree
	if(tree[node*2+1] != (' '|| '\0')){					//if the left node is empty
		inorder(tree, node*2+1);
	}
	printf("%c ", tree[node]);
	if(tree[node*2 +2] != (' ' || '\0')){					// if the right node is empty
		inorder(tree, node*2+2);
	}
	
}
/********prints the tree in level-order traversal*********************************/
void level_order(char tree[MAXSIZE], int node){
	int i = 0;
	//work across left to right then top to bottom
	printf("Level order: ");
	while(tree[i+2] != -1){
		if(tree[i] != ' '){
			printf("%c ", tree[i]);
			i++;
		}
		else{
			i++;
		}
	}
	printf("\n");
}