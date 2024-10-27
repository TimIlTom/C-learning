#include <stdio.h>
#include <stdlib.h>


int main(){

    int **a = malloc(5*sizeof(int**));

    for(int i = 0; i < 5; i++){

        printf("%d ", *(a+i));
    }

    printf("a before realloc: %p\n", a);

    realloc(a, 6*sizeof(int));

    printf("a after realloc: %p\n", a);

    realloc(a, 7*sizeof(int));

    printf("a after 2 realloc: %p\n", a);

    printf("\n");

    for(int i = 0; i < 6; i++){

        printf("%d ", *(a+i));
    }

    return 0;
}