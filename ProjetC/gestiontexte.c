#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include "gestiontexte.h"
#include "debug.h"


//------------------ Des methodes auxiliaires pour gérer des taches repetitives ---------------------------------------------------
//Verifier la coherence du mot donné
bool verif(const char* mot){
    //Cas d'un chemin vide
    if(strcmp(mot,"")==0){
        //printf("Verif : Chemin vide dans la vérification \n");
        return false;
    }

    // Cas retour au noeud Racine
    if(strlen(mot)==2){
        if(strcmp(mot,"..")==0){
            return true;
        }
    }
    for(const char* i=mot; *i!='\0'; ++i){
        //Verifier tous les cas d'erreurs d'une chaine de caractere
        if(isspace(*i) || 
           (*(i+1)=='\0' && (*i)=='/') ||
           (!isdigit(*i)&&!isalpha(*i)&&(*i)!='/') ||
           (*(i+1)!='\0' &&*i=='/'&& *(i+1)=='/')){
            return false;
        }
    }
    return true;
}

void free_index(w_index* pa){
    assert(pa!=NULL);
    for(int i=0; i<pa->nbr;++i){
        free(*(pa->words+i));
    }
    free(pa);
}

void print_index(w_index* pa){
    assert(pa!=NULL);
    printf("\n-Les Elements dans notre w_index: \n");
    for(int i=0;i<pa->nbr;++i){
        printf("  %d : %s \n ",i,pa->words[i]);
    }   
}

int size_words(w_index* pa){
    assert(pa!=NULL);
    int x=0;
    for(int i=0;i<pa->nbr;++i){
        x+=strlen(pa->words[i]);
    }
    return x;
}

w_index* cons_index(char* str){
    if(verif(str)==true){
    w_index* index=malloc(sizeof(w_index));
    int i = 0;
    
    // Calculer le nombre de mots
    index->nbr = 1;
    
    for (i = 1; str[i]!='\0'; ++i) {
        if (str[i] == '/') {
            index->nbr++;
        }
    }
    
    //Allouer de la mémoire pour les mots
    index->words = malloc(index->nbr * sizeof(char*));

    // Extraire les mots
    i = 0;
    // copie de la chaine pour ne pas modifier str
    char *temp=malloc((strlen(str)+1)*sizeof(char));
    assert(temp!=NULL);
    strcpy(temp,str);
    char* token = strtok(temp, "/");
    assert(token!=NULL);
    while (token != NULL) {
        index->words[i] = malloc(strlen(token) + 1);
        strcpy(index->words[i], token);
        if(DEBUG)printf("res :  %s \n",index->words[i]);
        token = strtok(NULL, "/");
        ++i;
    }
    free(temp);
    return index;
    }
    else{
        printf(" Erreur dans le chemin \n");
        exit(EXIT_FAILURE);
    }
}


w_index* mot(char* str){
    w_index* index=malloc(sizeof(w_index));
    int i = 0;
    
    // Calculer le nombre de mots
    index->nbr = 1;
    
    for (i = 1; str[i]!='\0'; ++i) {
        if (str[i] == '/') {
            index->nbr++;
        }
    }
    
    //Allouer de la mémoire pour les mots
    index->words = malloc(index->nbr * sizeof(char*));

    // Extraire les mots
    i = 0;
    // copie de la chaine pour ne pas modifier str
    char *temp=malloc((strlen(str)+1)*sizeof(char));
    assert(temp!=NULL);
    strcpy(temp,str);
    char* token = strtok(temp," ");
    assert(token!=NULL);
    while (token != NULL) {
        index->words[i] = malloc(strlen(token) + 1);
        strcpy(index->words[i], token);
        if(DEBUG)printf("res :  %s \n",index->words[i]);
        token = strtok(NULL, " ");
        ++i;
    }
    return index;
}