#ifndef FONCTIONAUXILIAIRE_H
#define FONCTIONAUXILIAIRE_H
    struct noeud{
    bool est_dossier;
    char nom [100];
    struct noeud* pere;
    struct noeud* racine;
    struct liste_noeud* fils;
    };

    struct liste_noeud{
        struct noeud* no;
        struct liste_noeud* succ;
    };
    typedef struct noeud noeud;
    typedef struct liste_noeud liste_noeud;

    extern noeud* creationDebut();
    extern bool validiteNoeud(noeud* n);
    extern noeud* ajoutL(noeud* courant, noeud* n);
    extern void descriptionNoeud(noeud* d);

    extern noeud* depCD(noeud* n, char* name);
    extern int nbFils(noeud* n);
    extern bool verification_PresenceFils(noeud* n, liste_noeud* list);
    extern void suppression(noeud* pred,noeud* n);
    
    extern noeud* cpVerif1(noeud* n,char* chem);
    extern noeud* copy_noeud(noeud* src,char* chem,noeud* nomPere);
    void cpVerif2(noeud* copie,noeud* courant,char* chem);

#endif