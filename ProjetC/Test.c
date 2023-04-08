#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "gestiontexte.h"
#include "fonctionauxiliaire.h"
#include "fonctionprincipale.h"


noeud* courant;

int main() {
    char input[200];
    char name[30], arg[100];

   courant=creationDebut();

    while (1) {
        printf("\033[34m/%s\033[0m\n",courant->nom);
        printf("> ");
        fflush(stdout);
        fgets(input, 100, stdin);
        sscanf(input, "%s %s", name, arg);

        if (strcmp(name, "quit") == 0) {
            break;
        }else if (strcmp(name, "ls") == 0) {
            ls(courant);
        } else if (strcmp(name, "pwd") == 0) {
            pwd(courant);
            printf("\n");
        } else if (strcmp(name, "mkdir") == 0) {
            mkdir(courant,arg);
        } else if (strcmp(name, "touch") == 0) {
            touch(courant,arg);
        } else if (strcmp(name, "rm") == 0) {
            rm(courant,arg);
        } else if (strcmp(name, "cd") == 0) {
            courant = cd(courant,arg);
        } else if (strcmp(name, "print") == 0) {
            print(courant);
        } else if (strcmp(name, "racine") == 0) {
            courant=cd(courant,"");
        } else {
            printf("La fonction '%s' n'existe pas\n", name);
        }
    }

    cp(courant,"Cours","/Td");
    ls(courant);
    rm(courant,"/Td/ProjetC");
    rm(courant,"/Td/Anglais");
    courant=cd(courant,"Td");
    mkdir(courant,"td1");
    mkdir(courant,"td2");
    print(courant);

    return 0;
}
