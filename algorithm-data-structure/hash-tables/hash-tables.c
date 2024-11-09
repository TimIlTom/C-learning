#include <stdio.h>
#define SIZE 100000

void identify_identical(int values[][6], int n);
int identical_right(int snow1[], int snow2[], int start);
int identical_left(int snow1[], int snow2[], int start);
int are_identical(int snow1[], int snow2[]);
int code(int snowflake[]);

typedef struct snowflake_node{

    int snowflake[6];
    struct snowflake_node *next;
} snowflake_node;

int main(){

    int n;
    static int snowflakes[SIZE][6];

    scanf("%d", &n);

    for(int i = 0; i < n; i++){

        for(int j = 0; j < 6; j++){

            scanf("%d", &snowflakes[i][j]);
        }
    }

    identify_identical(snowflakes, n);

    return 0;
}

void identify_identical(int values[][6], int n){

    for(int i = 0; i < n; i++){

        for(int j = i + 1; j < n; j++){

            if(are_identical(values[i], values[j])){
                
                printf("Twin snowflakes found.\n");
                return;
            }
        }
    }
    printf("No two snowflakes are alike.\n");
}

int identical_right(int snow1[], int snow2[], int start){

    int offset;

    for(offset = 0; offset < 6; offset++){

        if(snow1[offset] != snow2[(start + offset)%6]) return 0;
    }

    return 1;
}

int identical_left(int snow1[], int snow2[], int start){

    int offset, snow_index;

    for(offset = 0; offset < 6; offset++){

        snow_index = start - offset;

        if(snow_index <= -1) snow_index += 6;
        if(snow1[offset] != snow2[snow_index]) return 0;
    }

    return 1;
}

int are_identical(int snow1[], int snow2[]){

    int start;

    for(start = 0; start < 6; start++){

        if(identical_left(snow1, snow2, start)) return 1;
        if(identical_right(snow1, snow2, start)) return 1;
    }

    return 0;
}

int code(int snowflake[]){

    return(snowflake[0] + snowflake[1] + snowflake[2] + snowflake[3] + snowflake[4] + snowflake[5]) % SIZE;
}