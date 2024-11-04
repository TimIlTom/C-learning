#include <stdio.h>
#include <stdlib.h>

int height = 7;
int length = 14; //lenght size = height + 2 -> for the \n character and \0

void printWorld(char **world);
char **evolve(char **startWorld);
void reallocWorldHeight(char ***world, int direction);
void reallocWorldLength(char ***world, int direction);

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

    int n_generations = 100;

    for(int i = 0; i < n_generations; i++){

        printf("Generazione: %d\n", i);
        printWorld(world);

        world = evolve(world);
    }
    
    printWorld(world);

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

char **evolve(char **startWorld){

    int n_neighbour = 0;

    int worldYBorder = height - 2;
    int worldXBorder = length - 4;

    for(int i = 1; i <= worldYBorder; i++){

        for(int j = 1; j <= worldXBorder; j++){
            
            n_neighbour = 0;

            //printf("world[%d][%d]: %c\n", i, j, startWorld[i][j]);

            //controllo le 3 celle sopra della cella di riferimento
            if(startWorld[i-1][j-1] == '|' || startWorld[i-1][j-1] == '/') n_neighbour++;
            if(startWorld[i-1][j] == '|' || startWorld[i-1][j] == '/') n_neighbour++;
            if(startWorld[i-1][j+1] == '|' || startWorld[i-1][j+1] == '/') n_neighbour++;

            //controllo 2 celle adiacenti
            if(startWorld[i][j-1] == '|' || startWorld[i][j-1] == '/') n_neighbour++;
            if(startWorld[i][j+1] == '|' || startWorld[i][j+1] == '/') n_neighbour++;

            //controllo 3 celle sotto la cella di riferimento
            if(startWorld[i+1][j-1] == '|' || startWorld[i+1][j-1] == '/') n_neighbour++;
            if(startWorld[i+1][j] == '|' || startWorld[i+1][j] == '/') n_neighbour++;
            if(startWorld[i+1][j+1] == '|' || startWorld[i+1][j+1] == '/') n_neighbour++;

            //cambio lo stato delle celle
            if((n_neighbour < 2 || n_neighbour > 3) && startWorld[i][j] == '|') startWorld[i][j] = '/';
            if(n_neighbour == 3 && startWorld[i][j] == '-' ) startWorld[i][j] = '\\';

            //controllo lo stato dei bordi del mondo per espanderlo
            if(i == 1 && (startWorld[i][j] == '|' || startWorld[i][j] == '/')){
                
                height += 1;
                reallocWorldHeight(&startWorld, 1);
                i++;
                worldYBorder++;
            }

            if(i == worldYBorder && (startWorld[i][j] == '|' || startWorld[i][j] == '/')){                
                height += 1;
                reallocWorldHeight(&startWorld, 0);
            }

            if(j == 1 && (startWorld[i][j] == '|' || startWorld[i][j] == '/')){

                length += 1;
                reallocWorldLength(&startWorld, 1);
                j++;
                worldXBorder++;
            }
            
            if(j == worldXBorder && (startWorld[i][j] == '|' || startWorld[i][j] == '/')){

                length += 1;
                reallocWorldLength(&startWorld, 0);
            }
        }
    }

    for(int i = 1; i <= worldYBorder; i++){

        for(int j = 1; j <= worldXBorder; j++){

            if(startWorld[i][j] == '\\') startWorld[i][j] = '|';
            if(startWorld[i][j] == '/') startWorld[i][j] = '-';
        }
    }

    return startWorld;
}

void reallocWorldHeight(char ***world, int direction){

    //printf("Realloc world height: %d\n", height);

    *world = realloc(*world, height * sizeof(char **));

    if(world+(height-1) == NULL) printf("NULL pointer");

    *(*world+(height-1)) = (char *)malloc(length * sizeof(char));

    for(int i = 0; i <= length - 3; i++){

        (*world)[height-1][i] = '-';
    }

    if(direction == 1){

        char *previousPointer;

        for(int i = 0; i < height; i++)
        {   

            if(i == 0){

                previousPointer = (*world)[i];

                (*world)[i] = (*world)[height-1];
            }else{
                
                char *temp;
                temp = (*world)[i];
                (*world)[i] = previousPointer;
                previousPointer = temp;
            }
        }
    }
}

void reallocWorldLength(char ***world, int direction){

    //printf("Realloc world lenght: %d\n", length);

    for(int i = 0; i < height; i++){

        (*world)[i] = realloc((*world)[i], length * sizeof(char *));
        (*world)[i][length-3] = '-';

        for(int j = 0; j < length - 3; j++){

            if(direction == 1){
                
                char previousChar;

                if(j == 0){
                    
                    previousChar = (*world)[i][length-3];;
                    (*world)[i][j] = (*world)[i][length-3];
                }else{

                    char temp = (*world)[i][j];
                    (*world)[i][j] = previousChar;
                    previousChar = temp;
                }
            }
        }
    }
}