#ifndef GESTIONTEXTE_H
#define GESTIONTEXTE_H

    typedef struct{
    int nbr;
    char** words;
    }w_index;

    bool verif(const char* mot);

    void free_index(w_index* pa);
    void print_index(w_index* pa);
    int size_words(w_index* pa);

    w_index* cons_index(char* s);
#endif