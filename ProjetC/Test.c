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
void call_function(noeud* n, char *name, char *arg) {
    if (strcmp(name, "ls") == 0) {
        ls(n);
    } else if (strcmp(name, "pwd") == 0) {
        pwd(n);
    } else if (strcmp(name, "mkdir") == 0) {
        mkdir(n,arg);
    } else if (strcmp(name, "touch") == 0) {
        touch(n,arg);
    } else if (strcmp(name, "rm") == 0) {
        rm(n,arg);
    } else if (strcmp(name, "cd") == 0) {
        n = cd(n,arg);
    } else {
        printf("La fonction '%s' n'existe pas\n", name);
    }
}

int main() {
    char input[100];
    char name[20], arg[80];

   courant=creationDebut();

    while (1) {
        printf("=> ");
        fflush(stdout);
        fgets(input, 100, stdin);
        sscanf(input, "%s %s", name, arg);

        if (strcmp(name, "quit") == 0) {
            break;
        }
        else if (strcmp(name, "ls") == 0) {
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
        } else {
            printf("La fonction '%s' n'existe pas\n", name);
        }
    }
    return 0;
}
