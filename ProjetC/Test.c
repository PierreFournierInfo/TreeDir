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

void appliquerCommande(char* name, char* arg){
        if (strcmp(name, "quit") == 0) {
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

int main(){
  FILE *flux=fopen("fichier_Exemple.txt","r");
  if(flux==NULL){
    perror("Probleme ouverture de fichier");
    exit(EXIT_FAILURE);
  }
  int r=0;
  int cour=0;
  int dec=0;
  int i=0;
  char *st="bonjour";
  while((i=fgetc(flux))!="EOF"){
    if(i!=' '){
      ++dec;
    }else{
      r=fseek(flux,cour,SEEK_SET);
      assert(r==0);
      st=malloc(sizeof(char)*(dec+2));
      char *st2=fgets(st,dec+2,flux);
      assert(st2!=NULL);
      appliquercommande(st);
      free(st);
      cour=cour+dec+1;
      dec=0;
    }
  }
  r=fclose(flux);
  if(r!=0){
    perror("Probleme fermeture de fichier");
  } 
}


