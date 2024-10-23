#include <stdio.h>
#include <stdlib.h>

const int height = 20;
const int length = 20;

void printWorld(char **world);

void die(char *cell);
void live(char *cell);

void copyWorld(char startWorld[height][length], char endWorld[height][length]);

void evolve(char startWorld[height][length], char endWorld[height][length]);

int main(){

    // creation of the empty world
    char **world = (char **)malloc(height * sizeof(char *));

    for(int i = 0; i < height; i++){

        *(world+i) = (char *)malloc(length * sizeof(char));
    }

    for(int i = 0; i < height; i++){

        for(int j = 0; j < length; j++){

            world[i][j] = '-';
        }
    }

    printWorld(world);

    /*int n_generations = 10;

    char middleWorld[20][20];*/

    /*
    for(int i = 0; i < n_generations; i++){

        printWorld(startWorld);

        copyWorld(startWorld, middleWorld);

        evolve(startWorld, middleWorld);

        copyWorld(middleWorld, startWorld);
    }
    */

    return 0;
}

void printWorld(char **world){

    printf("\n");
    for(int i = 0; i < height; i++){

        for (int j = 0; j < length; j++){

            printf("%c ", world[i][j]);
        }
        printf("\n");
    }
}

void copyWorld(char startWorld[height][length], char endWorld[height][length]){

    for(int i = 0; i < height; i++){

        for (int j = 0; j < length; j++){

            endWorld[i][j] = startWorld[i][j];
        }
    }
}

void evolve(char startWorld[height][length], char endWorld[height][length]){

    int n_neighbour = 0;

    for(int i = 1; i < height-1; i++){
        for(int j = 1; j < length-1; j++){
            
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