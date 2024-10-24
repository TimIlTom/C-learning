#include <stdio.h>
#include <stdlib.h>

const int height = 5;
const int length = 7; //lenght size = height + 2 -> for the \n character and \0

void printWorld(char **world);
void die(char *cell);
void live(char *cell);
void **copyWorld(char **startWorld);
void evolve(char **startWorld, char **endWorld);

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

    int n_generations = 10;

    
    for(int i = 0; i < n_generations; i++){

        printWorld(world);

        worldCopy = copyWorld(world);

        printf("MONDO COPIATO:\n");
        printWorld(worldCopy);

        evolve(world, worldCopy);

        free(worldCopy);
    }
    

    return 0;
}

void printWorld(char **world){

    printf("\n");
    for(int i = 0; i < height; i++){

        for (int j = 0; j < length-2; j++){

            printf("%c ", world[i][j]);
        }
        printf("\n");
    }
}

void **copyWorld(char **startWorld){

    char **worldCopy = (char **)malloc(height * sizeof(char **));

    for(int i = 0; i < height; i++){

        *(worldCopy+i) = (char *)malloc(length * sizeof(char));
    }

    for(int i = 0; i < height; i++){

        for(int j = 0; j < length -2; j++){

            worldCopy[i][j] = startWorld[i][j];
        }
    }

    return worldCopy;
}

void evolve(char **startWorld, char **endWorld){

    int n_neighbour = 0;

    for(int i = 1; i < height-3; i++){
        for(int j = 1; j < length-3; j++){
            
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

            if(n_neighbour < 2 || n_neighbour > 3) die(&endWorld[i][j]);
            if(n_neighbour == 3) live(&endWorld[i][j]);
        }
    }
}

void die(char *cell){

    *cell = '-';
}

void live(char *cell){

    *cell = '|';
}