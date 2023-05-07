#include "fonctionauxiliaire.h"
#ifndef FONCTIONPRINCIPALE_H
#define FONCTIONAUXILIAIRE_H
    extern void ls(noeud* n);
    extern noeud* cd(noeud* n,char* name);
    extern void pwd(noeud* n);
    extern void mkdir(noeud* no,char* nom);
    extern void touch(noeud* no,char* nom);
    extern void print(noeud* n);
    extern void rm(noeud* n,char* chem);
    extern void cp(noeud* n,char* chem1,char* chem2);
    extern void mv(noeud* n,char* chem1,char* chem2);
#endif