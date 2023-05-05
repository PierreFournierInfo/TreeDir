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

char* remove_newline(char* str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
    return str;
}

void lire_fichier(char* nom_fichier){
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL){
        printf("Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return;
    }

    char ligne[100];
    char* mot1;
    char* mot2;
    while (fgets(ligne, 100, fichier) != NULL){
        // On sépare la ligne en deux mots
        mot1 = strtok(ligne," ");
        mot2 = strtok(NULL, " ");
        // On appelle la fonction correspondante
        // Avec une gestion en plus en fonction du nom que l'on a 
        if (strcmp(remove_newline(mot1), "ls") == 0) {
            ls(courant);
        } else if (strcmp(mot1, "pwd") == 0) {
            pwd(courant);
            printf("\n");
        } else if (strcmp(remove_newline(mot1), "mkdir") == 0) {
            mkdir(courant,remove_newline(mot2));
        } else if (strcmp(remove_newline(mot1), "touch") == 0) {
            touch(courant,remove_newline(mot2));
        } else if (strcmp(remove_newline(mot1), "rm") == 0) {
            rm(courant,remove_newline(mot2));
        } else if (strcmp(remove_newline(mot1), "cd") == 0) {
            courant = cd(courant,remove_newline(mot2));
        } else if (strcmp(remove_newline(mot1), "print") == 0) {
            print(courant);
        } else if (strcmp(remove_newline(mot1), "racine") == 0) {
            courant=cd(courant,"");
        } else if (strcmp(remove_newline(mot1), "cp") == 0) {
            printf("cp %s",mot2);
            char* mot3 = strtok(NULL,"\n");
            printf(" arg2 : %s\n",mot3);
            cp(courant,remove_newline(mot2),remove_newline(mot3));
        }else if (strcmp(remove_newline(mot1), "mv") == 0) {
            printf("mv %s",mot2);
            char* mot3 = strtok(NULL,"\n");
            printf(" arg2 : %s\n",mot3);
            mv(courant,remove_newline(mot2),mot3);
        }
        else {
            printf("La fonction '%s' n'existe pas\n", mot1);
        }
    }
    fclose(fichier);
}

int main(int argC,char* chaine[]){
    courant=creationDebut();
    lire_fichier(chaine[1]);
    
    //w_index* a = cons_index("Creation/omt/n");
    //free_index(a);

    return 0;
}