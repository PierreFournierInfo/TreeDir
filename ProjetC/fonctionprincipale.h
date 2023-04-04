#include "fonctionauxiliaire.h"
#ifndef FONCTIONPRINCIPALE_H
#define FONCTIONAUXILIAIRE_H
    void ls(noeud* n);
    noeud* cd(noeud* n,char* name);
    char* pwd(noeud* n);
    void mkdir(noeud* no,char* nom);
    void touch(noeud* no,char* nom);
    void print(noeud* n);
    void rm(noeud* n,char* chem);
    void cp(noeud* n,char* chem1,char* chem2);
    void mv(noeud* n,char* chem1,char* chem2);
#endif