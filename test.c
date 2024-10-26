#include <stdio.h>
#include <stdlib.h>


int main(){

    int *a = malloc(5*sizeof(int));

    for (int i = 0; i < 5; i++){

        *(a+i) = i;
    }

    for(int i = 0; i < 5; i++){

        printf("%d ", *(a+i));
    }

    realloc(a, 6*sizeof(int));

    printf("\n");

    for(int i = 0; i < 6; i++){

        printf("%d ", *(a+i));
    }

    return 0;
}