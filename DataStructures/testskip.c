/* Skip Lists: A Probabilistic Alternative to Balanced Trees */
 
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
 
#define MAX_LEVEL 6
 
typedef struct Node {
    int key;
    int value;
    struct Node **next;
} Node;
 
typedef struct List {
    int level;
    int size;
    struct Node *header;
} List;
 
List *initialize(List *list) {
	list->level = 1;
    list->size = 0;

    Node *header = (Node *) malloc(sizeof(struct Node));
    list->header = header;
    header->key = INT_MAX;
    header->next = (Node **) malloc(sizeof(Node*) * (MAX_LEVEL + 1));
    for (int i = 0; i <= MAX_LEVEL; i++) {
        header->next[i] = list->header;
    }

 
    return list;
}
// retruns a random int as the levels that a node to be insertted will appear on
int rand_level() {
    int l = 1;
    while (rand() < RAND_MAX / 2 && l < MAX_LEVEL){
        l++;
	}
    return l;
}
 
int insert(List *list, int key, int value) {
    Node *update[MAX_LEVEL + 1];
    Node *x = list->header;
    int i, level;
    for (i = list->level; i >= 1; i--) {
        while (x->next[i]->key < key)
            x = x->next[i];
        update[i] = x;
    }
    x = x->next[1];
 
    if (key == x->key) {
        x->value = value;
        return 0;
    } else {
        level = rand_level();
        if (level > list->level) {
            for (i = list->level + 1; i <= level; i++) {
                update[i] = list->header;
            }
            list->level = level;
        }
 
        x = (Node *) malloc(sizeof(Node));
        x->key = key;
        x->value = value;
        x->next = (Node **) malloc(sizeof(Node*) * (level + 1));
        for (i = 1; i <= level; i++) {
            x->next[i] = update[i]->next[i];
            update[i]->next[i] = x;
        }
    }
    return 0;
}
 
Node *search(List *list, int key) {
    Node *x = list->header;
    int i;
    for (i = list->level; i >= 1; i--) {
        while (x->next[i]->key < key)
            x = x->next[i];
    }
    if (x->next[1]->key == key) {
        return x->next[1];
    } else {
        return NULL;
    }
    return NULL;
}
 
static void List_temp_free(Node *x) {
    if (x) {
        free(x->next);
        free(x);
    }
}
 
int remove_from(List *list, int key) {
    int i;
    Node *update[MAX_LEVEL + 1];
    Node *x = list->header;
    for (i = list->level; i >= 1; i--) {
        while (x->next[i]->key < key)
            x = x->next[i];
        update[i] = x;
    }
 
    x = x->next[1];
    if (x->key == key) {
        for (i = 1; i <= list->level; i++) {
            if (update[i]->next[i] != x)
                break;
            update[i]->next[1] = x->next[i];
        }
        List_temp_free(x);
 
        while (list->level > 1 && list->header->next[list->level]
                == list->header)
            list->level--;
        return 0;
    }
    return 1;
}
 
static void print_list(List *list) {
    Node *x = list->header;
    while (x && x->next[1] != list->header) {
        printf("%d[%d] ", x->next[1]->key, x->next[1]->value);
        x = x->next[1];
    }
    printf("NULL\n");
}
 
int main(void) {
    int arr[] = { 11, 22, 33, 44, 55, 66, 77 }, i;
    List list;
    initialize(&list);
 
    printf("Insert:--------------------\n");
    for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        insert(&list, arr[i], arr[i]);
    }
    print_list(&list);
 
    printf("Search:--------------------\n");
    int keys[] = { 3, 4, 7, 10, 111 };
 
    for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        Node *x = search(&list, keys[i]);
        if (x) {
            printf("key = %d, value = %d\n", keys[i], x->value);
        } else {
            printf("key = %d, not fouund\n", keys[i]);
        }
    }
 
    printf("Search:--------------------\n");
    remove_from(&list, 3);
    remove_from(&list, 9);
    print_list(&list);
 
    return 0;
}