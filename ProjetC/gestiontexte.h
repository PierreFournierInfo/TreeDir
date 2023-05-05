#ifndef GESTIONTEXTE_H
#define GESTIONTEXTE_H

    typedef struct{
    int nbr;
    char** words;
    }w_index;

    extern bool verif(const char* mot);

    extern void free_index(w_index* pa);
    extern void print_index(w_index* pa);
    extern int size_words(w_index* pa);

    extern w_index* cons_index(char* s);
    extern w_index* mot(char* s);
    
#endif