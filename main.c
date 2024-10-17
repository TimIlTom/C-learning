#include <stdio.h>

const int height = 20;
const int length = 20;

void printWorld(char world[height][length]);

void die(char *cell);
void live(char *cell);

void copyWorld(char startWorld[height][length], char endWorld[height][length]);

void isolation(char startWorld[height][length], char endWorld[height][length]);
void overpopulation(char startWorld[height][length], char endWorld[height][length]);
void reproduction(char startWorld[height][length], char endWorld[height][length]);

int main(){

    char startWorld[20][20] = 
    {
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','|','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','|','-','|','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','|','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','|','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','|','|','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','|','-','|','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','|','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
        {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
    };

    int n_generations = 10;

    char middleWorld[20][20];

    for(int i = 0; i < n_generations; i++){

        printWorld(startWorld);

        copyWorld(startWorld, middleWorld);

        isolation(startWorld, middleWorld);
        overpopulation(startWorld, middleWorld);
        reproduction(startWorld, middleWorld);

        copyWorld(middleWorld, startWorld);
    }

    return 0;
}

void printWorld(char world[height][length]){

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

void isolation(char startWorld[height][length], char endWorld[height][length]){

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
            //printf("world[%d][%d] ha %d vicini\n", i, j, n_neighbour);

            if(n_neighbour < 2) die(&endWorld[i][j]);
        }
    }
}

void overpopulation(char startWorld[height][length], char endWorld[height][length]){

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
            //printf("world[%d][%d] ha %d vicini\n", i, j, n_neighbour);

            if(n_neighbour > 3) die(&endWorld[i][j]);
        }
    }
}

void reproduction(char startWorld[height][length], char endWorld[height][length]){

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
            //printf("world[%d][%d] ha %d vicini\n", i, j, n_neighbour);

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