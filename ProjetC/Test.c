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
   courant=creationDebut();
   
    char input[200];
    char name[30], arg[100];

    while (1) {
        printf("\033[34m");
        printf("~");
        pwd(courant);
        printf("\033[0m\n");
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
        } else if (strcmp(name, "copy") == 0) {
            cp(courant,"Cours","/Td");
        }else {
            printf("La fonction '%s' n'existe pas\n", name);
        }
    }
    
    mkdir(courant,"Cours");
    courant=cd(courant,"Cours");
    mkdir(courant,"ProjetC");
    mkdir(courant,"Anglais");
    courant=cd(courant,"..");
    cp(courant,"Cours","/Td");
    print(courant);
     
    rm(courant,"Td/Anglais");
    w_index* test=cons_index("/Td");
    print_index(test);
    print(courant);
    courant=cd(courant,"Td");
    mkdir(courant,"td1");
    mkdir(courant,"td2");
    print(courant);

    return 0;
}


