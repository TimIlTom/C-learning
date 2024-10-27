#include <stdio.h>
#include <stdlib.h>

int height = 5;
int length = 7; //lenght size = height + 2 -> for the \n character and \0

void printWorld(char **world);
char **copyWorld(char **startWorld);
void evolve(char **startWorld, char **endWorld);
void reallocWorldHeight(char **world);

int main(){

    // creation of the empty world
    char **world = (char **)malloc(height * sizeof(char *));

    for(int i = 0; i < height; i++){

        *(world+i) = (char *)malloc(length * sizeof(char));
    }

    // populating the world with data in the world.txt file
    FILE *worldFile = fopen("world.txt", "r");

    for(int i = 0; i < height; i++){

        fgets(*(world+i), length, worldFile);
    }

    char **worldCopy;

    int n_generations = 1;

    for(int i = 0; i < n_generations; i++){

        printWorld(world);

        worldCopy = copyWorld(world);

        for(int i = 0; i < height; i++){

            printf("Pointer to p row %d: %p\n", i, world+i);
            printf("Pointer to row %d: %p\n\n", i, *(world+i));
        }
        //printWorld(world);

        height += 1;

        printf("----------------------------------\n");
        printf("REALLOC 1\n");
        printf("----------------------------------\n\n");

        reallocWorldHeight(world);

        for(int i = 0; i < height; i++){

            printf("Pointer to p row %d: %p\n", i, world+i);
            printf("Pointer to row %d: %p\n\n", i, *(world+i));
        }
        //printWorld(world);

        height += 1;

        printf("----------------------------------\n");
        printf("REALLOC 2\n");
        printf("----------------------------------\n\n");

        reallocWorldHeight(world);

        for(int i = 0; i < height; i++){

            printf("Pointer to p row %d: %p\n", i, world+i);
            printf("Pointer to row %d: %p\n\n", i, *(world+i));
        }
        //printWorld(world);

        //evolve(world, worldCopy);

        //world = copyWorld(worldCopy);

        //printWorld(world);
    }
    

    return 0;
}

void printWorld(char **world){

    printf("\n");
    printf("heigth: %d\n", height);
    for(int i = 0; i < height; i++){

        for (int j = 0; j < length-2; j++){

            printf("%c ", world[i][j]);
        }
        printf("\n");
    }
}

char **copyWorld(char **startWorld){

    char **worldCopy = (char **)malloc(height * sizeof(char **));

    for(int i = 0; i < height; i++){

        *(worldCopy+i) = (char *)malloc(length * sizeof(char));
    }

    for(int i = 0; i < height; i++){

        for(int j = 0; j < length - 2; j++){

            worldCopy[i][j] = startWorld[i][j];
        }
    }

    return worldCopy;
}

void evolve(char **startWorld, char **endWorld){

    int n_neighbour = 0;

    int worldYBorder = height - 2;
    int worldXBorder = length - 3;

    for(int i = 1; i <= worldYBorder; i++){

        printf("Iterazione startworld[%d]\n", i);

        for(int j = 1; j < worldXBorder; j++){
            
            n_neighbour = 0;

            //controllo le 3 celle sopra della cella di riferimento
            if(startWorld[i-1][j-1] == '|') n_neighbour++;
            if(startWorld[i-1][j] == '|') n_neighbour++;
            if(startWorld[i-1][j+1] == '|') n_neighbour++;

            //controllo 2 celle adiacenti
            if(startWorld[i][j-1] == '|') n_neighbour++;
            if(startWorld[i][j+1] == '|') n_neighbour++;

            //controllo 3 celle sotto la cella di riferimento
            if(startWorld[i+1][j-1] == '|') n_neighbour++;
            if(startWorld[i+1][j] == '|') n_neighbour++;
            if(startWorld[i+1][j+1] == '|') n_neighbour++;

            //cambio lo stato delle celle
            if(n_neighbour < 2 || n_neighbour > 3) endWorld[i][j] = '-';
            if(n_neighbour == 3) endWorld[i][j] = '|';

            //controllo lo stato dei bordi del mondo per espanderlo
            if(i == 1 && startWorld[i][j] == '|'){

                height += 1;
                reallocWorldHeight(startWorld);
            }

            if(i == worldYBorder && startWorld[i][j] == '|'){
                
                height += 1;
                reallocWorldHeight(startWorld);
            }

            //if(j == 1 && startWorld[i][j] == '|') length += 1;
            //if(j == worldXBorder && startWorld[i][j] == '|') length += 1;

            printf("world[%d][%d]: %c\n", i, j, startWorld[i][j]);
        }
    }
}

void reallocWorldHeight(char **world){

    printf("Realloc return value: %p\n", realloc(world, height * sizeof(char **)));

    printf("Pointer position in realloc:  %p\n", world);

    if(world+(height-1) == NULL) printf("NULL pointer");

    //*(world+(height-1)) = (char *)malloc(length * sizeof(char));

    /*for(int i = 0; i <= length - 3; i++){

        world[height-1][i] = '-';
        //printf("Value to row length[%d]: %c\n", i, world[height-1][i]);
    }*/
}