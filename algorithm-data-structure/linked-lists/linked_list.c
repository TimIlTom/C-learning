#include <stdio.h>
#include <stdlib.h>

//1. Define the structure of one node
typedef struct node{

    int value;
    struct node *next;
}node;

//Add new element to the first position of the linked list
node *add_to_list(node *list, int n);
//Build a linked list based on user input
node *read_members(void);
node *search_list(node *list, int n);

int main(){

    //2. Pointere that points to the first element of the list
    node *first = NULL;

    first = read_members();

    printf("Trovato il numero: %d \n", search_list(first, 10)->value);

    return 0;
}

node *add_to_list(node *list, int n){

    node *new_node = malloc(sizeof(node));

    if(new_node == NULL){

        printf("Error: malloc failed during add_node!\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = n;
    new_node->next = list;
    
    return new_node;
}

node *read_members(void){

    node *first = NULL;
    int n;

    printf("Enter a series of number, 0 to exit!\n");

    for(;;){

        scanf("%d", &n);
        if(n == 0) return first;
        first = add_to_list(first, n);
    }
}

node *search_list(node *list, int n){

    while(list != NULL && list->value != n) list = list->next;

    return list;
}