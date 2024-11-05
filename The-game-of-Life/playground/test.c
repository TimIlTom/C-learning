#include <stdio.h>

int main(){

    char parola[200] = "Fabio sei un cojone";

    char *pParola = parola;

    while(*pParola){      
        if(*pParola == ' ') *pParola = '\n';
        pParola++;
    }

    printf("%s", parola);

    return 0;
}