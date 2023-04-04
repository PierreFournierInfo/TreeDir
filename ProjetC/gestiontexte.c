#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include "gestiontexte.h"

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

int nbr_words(const char* a){
    if(verif(a)){
        int res=0;
        assert(a!=NULL);
            if(*a=='/'){
                for(const char* ind=a+1; *(ind) !='\0'; ++ind){
                    if((*(ind)!='/'&&*(ind+1)=='/') || (*(ind)!='/' && *(ind+1)=='\0')){
                        res++;
                    }
                }
            }
            else{
                for(const char* ind=a; *(ind) !='\0'; ++ind){
                     if((*(ind)!='/'&&*(ind+1)=='/') || (*(ind)!='/' && *(ind+1)=='\0')){
                        res++;
                    }
                }
            }
            return res;
    }
    else{return -1000;}
}

//Longuer d'un mot avant le prochain /
int word_len(const char* w){
    assert(w!=NULL);
    int res=0;
    if(*w=='/'){
        for(const char* parc=w+1;*(parc)!='/';++parc){
            res++;
            if(*(parc+1)=='\0')break;
        }
    }
    else{
        for(const char* parc=w;*(parc)!='/';++parc){
            res++;
            if(*(parc+1)=='\0')break;
        }
    }
    return res;
}

//Extraire un mot à partir d'une position
char* extract_word(const char* str,int n){
    if(str==NULL){
        printf("\033[1;31m (Gestion de texte) Extract_Word Syntaxe Invalide !! \033[0m \n");
        exit(1);
    }
    if(verif(str)){
        if(*str!='/'){
            int x=word_len(str);
            char* res=malloc(sizeof(char)*x+1);
            assert(res!=NULL);
            memmove(res,str,sizeof(char)*x);
            *(res+x)='\0';
            return res;
        }
        else{
            int x=word_len(str+1);
            char* res=malloc(sizeof(char)*x+1);
            assert(res!=NULL);
            memmove(res,str+1,sizeof(char)*x);
            *(res+x)='\0';
            return res;
        }
    }
    else{
        printf(" Erreur dans le mot depuis extract Word");
        exit(1);
        return NULL;
    }   
}

//Chercher le prochain mot en fonnction de critère 
char* next_word(char* w){
    assert(w!=NULL);
    if(*w=='/'){
        return w+1;
    }
    else{
        for(char* x=w;*x!='\0';++x){
            if(*x=='/'){
                return x+1;
            } 
        }
    }
    return NULL;
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

w_index* cons_index(char* s){
    int valLen=nbr_words(s), x=0 , cons=0;
    w_index* res=malloc(sizeof(w_index));
    res->nbr=valLen;
    res->words=malloc(sizeof(char*)*valLen); 
   
    char* save=s; 
    for(int i=0; i<valLen; ++i){
        save=extract_word(save,cons);
        
        // Ne pas oublier le caractere \0
        x+=strlen(save);
      
        int y=x;
        res->words[i]=malloc(sizeof(char)*strlen(save)+1);
        //Compléter chaque case
        for(int j=0; j<y; ++j){
            res->words[i][j]=save[j];
        }
        res->words[i][strlen(save)]='\0';
      
        //Voir le prochain mot
        save=next_word((s+x));
    }
    return res;
}
