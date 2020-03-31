#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

struct NODE{
    char data[MAX];
    struct NODE *left;
    struct NODE *right;
    struct NODE *children;
};
struct NODE *root = NULL;
struct NODE *parent_found = NULL;
/*Functions and global arrays */

int main(int argc, char * argv[]) {
    int i = 0, j = 0;									// i keeps track of number of nodes in tree

    FILE *node_file = fopen(argv[1], "r");
    
    if (node_file == NULL) {									// if file cannot be opened
        printf("Error opening file: %s\n", argv[1]);			
        return 0;
    }
    while(fgets(tree,MAX,node_file) != NULL){            		// put data into the tree
        tree[strlen(tree)-1] = '\0';
        strcpy(list[i],tree);
        insert(tree);
        i++;
    }
    fclose(node_file);									// done with node file
    
    FILE *command_file;
    command_file = fopen(argv[2],"r");
        
    if (command_file == NULL) {									// if final cannot be opened
        printf("Error opening file: %s\n", argv[1]);
        return 0;
    }
    while(fgets(command,MAX,command_file) != NULL) {        	// read the command
        command[strlen(command)-1] = '\0';
        strcpy(commands[j],command);
        // check which command is called
       	split(instruction,combo,command);
	    check_condition(command);				// runs through if statements that run the didffernt functions for each command
        j++;
    }
    fclose(command_file);   
}

/* inserts a new node into the tree structure the input is the data/name of the node  *********/
void insert(char info[300]){
    struct NODE *new_node;

    split(parent, child,info);
    printf("%s %s\n", parent, child);

    if ((root == NULL) && (child[0] == '\0')){				// if the tree is empty
        new_node = malloc(sizeof(struct NODE));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->children = NULL;							// no children

        strcpy(new_node->data, parent);
        root = new_node;									// new node is the root of the tree
    }
    else{
        parent_found = NULL;
        find_parent(root, parent);				// otherwise check if this new_node is a child of a previos node
        if(parent_found != NULL){
            add_children(child);				// if true, add the node to propere postion
        }
    }
}
/* Splits the line of input into command or nodes; takes 3 pointers to strings as input */
void split(char *a, char *b, char *c) {
	int i ,a_index = 0, b_index = 0;			// a is the first node and b is the second node that are derived from c
	int first = 0;

	for(i = 0; i < strlen(c); i++){				// for each index of c
		if(c[i] != ' '){					// if at the end
			if (first == 0){
       			a[a_index] = c[i];			// add to a string
				a_index++;
			}
			if (first == 1){
				b[b_index] = c[i];			// add to b string
				b_index++;
			}
        }
        else{
			first = 1;
		}
	}
	a[a_index] = '\0';					// set the end of a and b strings to avoid accessing junk
	b[b_index] = '\0';

}