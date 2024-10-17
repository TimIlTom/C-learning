#include <stdio.h>

const int height = 10;
const int length = 10;

void printWorld(char world[height][length]);

void die(char *cell);
void live(char *cell);

void copyWorld(char startWorld[height][length], char endWorld[height][length]);

void isolamento(char startWorld[height][length], char endWorld[height][length]);
void sopravvivenza(char startWorld[height][length], char endWorld[height][length]);
void sovrappopolazione(char startWorld[height][length], char endWorld[height][length]);
void riproduzione(char startWorld[height][length], char endWorld[height][length]);

int main(){

    char startWorld[10][10] = 
    {
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','O','X','X','X','X','X','X','X'},
        {'X','X','O','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'}
    };

    char middleWorld[10][10];

    printWorld(startWorld);

    copyWorld(startWorld, middleWorld);

    isolamento(startWorld, middleWorld);

    copyWorld(middleWorld, startWorld);

    printWorld(startWorld);

    return 0;
}

void printWorld(char world[height][length]){

    printf("\n");
    for(int i = 0; i < length; i++){

        for (int j = 0; j < height; j++){

            printf("%c ", world[i][j]);
        }
        printf("\n");
    }
}

void isolamento(char startWorld[height][length], char endWorld[height][length]){

    int n_neighbour = 0;

    for(int i = 1; i < height-1; i++){
        for(int j = 1; j < length-1; j++){
            
            n_neighbour = 0;

            //controllo le 3 celle sopra della cella di riferimento
            if(startWorld[i-1][j-1] == 'O') n_neighbour++;
            if(startWorld[i-1][j] == 'O') n_neighbour++;
            if(startWorld[i-1][j+1] == 'O') n_neighbour++;

            //controllo 2 celle adiacenti
            if(startWorld[i][j-1] == 'O') n_neighbour++;
            if(startWorld[i][j+1] == 'O') n_neighbour++;

            //controllo 3 celle sotto la cella di riferimento
            if(startWorld[i+1][j-1] == 'O') n_neighbour++;
            if(startWorld[i+1][j] == 'O') n_neighbour++;
            if(startWorld[i+1][j+1] == 'O') n_neighbour++;
            //printf("world[%d][%d] ha %d vicini\n", i, j, n_neighbour);

            if(n_neighbour < 2) die(&endWorld[i][j]);
        }
    }
}

void copyWorld(char startWorld[height][length], char endWorld[height][length]){

    for(int i = 0; i < length; i++){

        for (int j = 0; j < height; j++){

            endWorld[i][j] = startWorld[i][j];
        }
    }
}

//void sopravvivenza(char world[height][length]);

//void sovrappopolazione(char world[height][length]);

//void riproduzione(char world[height][length]);

void die(char *cell){

    *cell = 'X';
}

void live(char *cell){

    *cell = 'O';
}