#ifndef FONCTIONAUXILIAIRE_H
#define FONCTIONAUXILIAIRE_H
    struct noeud{
    bool est_dossier;
    char nom [100];
    struct noeud *pere;
    struct noeud *racine;
    struct liste_noeud *fils;
    };

    struct liste_noeud{
        struct noeud *no;
        struct liste_noeud *succ;
    };
    typedef struct noeud noeud;
    typedef struct liste_noeud liste_noeud;

    noeud* creationDebut();
    bool validiteNoeud(noeud* n);
    void ajoutL(noeud* courant,liste_noeud* l, noeud* n);
    void descriptionNoeud(noeud* d);

    noeud* depCD(noeud* n, char* name);
    int nbFils(noeud* n);
    noeud* deplacementCalculer(noeud* n, char* chem);
    bool verification_PresenceFils(noeud* n, liste_noeud* list);
    bool chemin_existe(noeud* n,char* chem);
    void suppression(noeud* pred,noeud* n);
    void liberation_noeud(noeud* n,char* chem);

    noeud* cpVerif1(noeud* n,char*chem);
    void cpVerif2(noeud* copie,noeud* courant,char* chem);

#endif