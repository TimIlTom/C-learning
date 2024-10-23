#include <stdio.h>
#include <stdlib.h>


int main(){

    int a, b, c;

    a = 0;
    b = 1;
    printf("%d ", a);
    printf("%d ", b);
    for(int i = 0; i < 10; i++){

        c = a+b;
        a = b;
        b = c;

        printf("%d ", c);
    }

    return 0;
}