/* Erika Ambrioso
   CSE2010
   Assignment 6b 
   AVL tree (the print function prints the tree in preorder)
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

typedef struct Node{
   int value;
   struct Node *left;
   struct Node *right;
}Node;

void insert(int, Node**);
int get_height(Node **, int);
int check_balance(Node**);
void print_list(Node**);

// by Shakre
int is_balanced(Node*);
int get_node_height(Node*);



int main(void){
   struct Node *header = NULL;

    insert(10, &header);               
    insert(15, &header);
    insert(12, &header);
   // insert(7, &header); // adding this makes the tree balanced
    insert(9, &header);
    insert(4, &header);
    insert(22, &header);
    insert(1, &header);
    insert(6, &header);

/*
Without the 7 (not an AVL @9):

      10
     /  \
    9    15
   /    /  \
  4    12  22
 / \
1   6

With 7 (AVL):

       10
     /    \
    7      15
   / \    /  \
  4   9  12  22
 / \
1   6

*/   
   print_list(&header);
   
   //printf("h: %d\n", get_height(&header, 10));
   printf("\n");
   //printf("h(10)= %d\n", get_node_height(header));
   //printf("h(9)= %d\n", get_node_height(header->left));
   //printf("h(4)= %d\n", get_node_height(header->left->left));
   //printf("h(1)= %d\n", get_node_height(header->left->left->left));
   
   printf("BALANCED: %d\n", is_balanced(header));

}

// compares the height of the left and right subtree and checks if it follows AVL
int check_balance(Node **header){
   Node *temp = (*header);
   
   if((get_height(header, temp->left->value) - get_height(header, temp->right->value)) > 1 || 
      (get_height(header, temp->left->value) - get_height(header, temp->right->value)) < 1) {
      return 0;
   }

   check_balance(&temp->right);      // recurse right
   check_balance(&temp->left);       // recurse left
   return 1;
   
}

// returns 1 if balanced, 0 otherwise
int is_balanced(Node *subtree){
   //Node *temp = *header;
   if (subtree == NULL) { // an empty tree is balanced
      return 1;
   }
   //printf("checking %d\n", temp->value);

   int left_height = 0;
   if (subtree->left) { // only check the height of the left subtree if there's a left child
     left_height = get_node_height(subtree->left);
   }
   int right_height = 0;
   if (subtree->right) {
      right_height = get_node_height(subtree->right);
   }

   if(abs((left_height - right_height)) > 1) { // abs() makes it easier to read!
      return 0;
   }

   int left_balanced  = is_balanced(subtree->left);       // recurse left
   int right_balanced = is_balanced(subtree->right);      // recurse right

   //printf("%d is ", subtree->value);
   if (left_balanced && right_balanced) {
      //printf("balanced\n");
      return 1;
   }
   else {
      //printf("NOT balanced\n");
      return 0;
   }
}

int get_node_height(Node *subtree){
   if(subtree == NULL){
      return 0;
   }
   int left_height  = get_node_height(subtree->left);       // recurse left
   int right_height = get_node_height(subtree->right);      // recurse right
   //printf("height of %d: left = %d, right = %d\n", subtree->value, left_height, right_height);

   return 1 + ( (left_height > right_height) ? left_height : right_height );
}


/*
 * By Shakre: I think the following function should be called something like "get_level_number", not "get_height"
 * node(9) below has height of 2, but it's on level number 1 (root is level 0). This function will return 1, not 2

      10
     /  \
    9    15
   /    /  \
  4    12  22
 / \
1   6

*/

// returns the height of a given node in the tree given the header and the value we want to know the height of
int get_height(Node **header, int compare){
   if((*header) == NULL){
      return 0;
   }
   Node *temp = (*header);
      while(temp != NULL){
         if(compare > temp->value ){                     // if the value we are checking is greater than current node, go right
               if(temp->right->value == compare){
                  return 1;
               }
               return  1 + get_height(&temp->right, compare);         // recursion
         }
         else if(compare < temp->value){                  // if less, go left
            if(temp->left->value == compare){
               return 1;
            }
            return 1 + get_height(&temp->left, compare);         // recursion

         }
         else{ // that is, compare == temp->value
            //printf("Error\n"); // commented out by Shakre
            return 0; // if we're looking for the root
         }   
   }
}

// inserts a new node based on AVL trees
void insert(int data, Node **header){

   if((*header) == NULL){
      (*header) = (Node*)malloc(sizeof(Node));
      (*header)->value = data;
      (*header)->right = NULL;
      (*header)->left = NULL;
      return;
   }
   Node *temp = (*header);
      while(temp != NULL){
         if(data > temp->value ){               // if we need to go right
               if(temp->right ==NULL){
                  Node *new_node = (Node*)malloc(sizeof(Node));
                  temp->right = new_node;
                  
                  new_node->value = data;         // adjust pointers
                  new_node->right = NULL;
                  new_node->left = NULL;
                  return;
               }
               temp = temp->right;               // continue until at a leaf node
         }
         else if(data < temp->value){            // if we need to go left
            if(temp->left ==NULL){   
                  Node *new_node = (Node*)malloc(sizeof(Node));
                  temp->left = new_node;
                  
                  new_node->value = data;            // adjust pointers
                  new_node->right = NULL;
                  new_node->left = NULL;
                  return;
               }
         
            temp = temp->left;
         }
         else{
            printf("Error\n");
         }
      
   }

}
// prints the tree in preorder
void print_list(Node **header){

   if((*header) != NULL){
      Node *temp = (*header);
      printf("%d ", temp->value);
      print_list(&temp->left);
      print_list(&temp->right);
   }
}
   
