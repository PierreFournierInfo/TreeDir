#ifndef GESTIONTEXTE_H
#define GESTIONTEXTE_H

    typedef struct{
    int nbr;
    char** words;
    }w_index;

    //Verifier la coherence du mot donné
    bool verif(const char* mot);
    int nbr_words(const char* a);
    int word_len(const char* w);
    char* extract_word(const char* str,int n);
    char* next_word(char* w);

    void free_index(w_index* pa);
    void print_index(w_index* pa);
    int size_words(w_index* pa);

    w_index* cons_index(char* s);
#endif