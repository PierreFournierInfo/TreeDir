#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include "gestiontexte.h"
#include "fonctionauxiliaire.h"
#include "debug.h"

// Creation de la racine
noeud* creationDebut(){
    noeud* n = malloc(sizeof(noeud));
    strcpy(n->nom,"~");
    n->est_dossier=true;
    n->fils=NULL;
    n->pere=n;
    n->racine=n;
    return n;
}

// Fonction auxiliaire de verification de la validité d'un noeud
bool validiteNoeud(noeud* n){
    return n != NULL && n->racine != NULL && n->pere != NULL;
}

// Fonction auxiliaire de description simple
void descriptionNoeud(noeud* d){
    assert(d!=NULL);
    printf("\n-- DESCRIPTION DU NOEUD -- \n");
    if(d->est_dossier){
        printf("Ce noeud est un dossier, ");
    }
    printf("Son nom est : %s et le nom de son pere est : %s\n",d->nom,d->pere->nom);
    printf("Le nom de sa racine est : %s \n",d->racine->nom);
    if(d->fils!=NULL){
        printf(" Il possède des fils\n");
        printf("\n");
    }
    printf("\n");
}

//Fonction auxiliaire ajout dans une liste
noeud* ajoutL(noeud* courant, noeud* n){
    assert(courant!=NULL);
    assert(n!=NULL);
    if(courant != NULL && courant->fils !=NULL && n != NULL ){
        if(DEBUG)printf("\033[33mAjout Liste \033[0m\n");
        if(courant->fils->succ==NULL){
            // Si le suivant est directement NULL
            liste_noeud* aj=malloc(sizeof(liste_noeud));
            assert(aj!=NULL);
            aj->no=n;
            aj->succ=NULL;
            courant->fils->succ=aj;
            return courant;
        }
        else{
            // Si on doit faire un parcour des fils
            liste_noeud* tmp = courant->fils;
            while(tmp->succ != NULL){
                tmp=tmp->succ;
            }
            liste_noeud* aj=malloc(sizeof(liste_noeud));
            assert(aj!=NULL);
            aj->no=n; 
            aj->succ=NULL;
            tmp->succ=aj;    
            return courant;
        }
    }
    else{ 
        // Creation des fils de la liste
        if(DEBUG)printf("\n \033[33mAjout Liste 2 \033[0m\n");
        if(n != NULL){
            if(courant->fils==NULL){
                //printf(" ==>Reussi l'ajout \n");
                courant->fils=malloc(sizeof(liste_noeud));
                courant->fils->no = n;
                courant->fils->succ=NULL;
            }
            return courant;
        }
        else{
            printf("\033[31m Le noeud à ajouter dans la liste courante est null !! \033[0m");
            exit(EXIT_FAILURE);
        }
    }
}

// CD
//!Faire une fonction auxiliaire pour le deplacement dans un fichier
noeud* depCD(noeud* n, char* name){
    if(DEBUG) printf(" NOM du chem de deplacement  : %s\n",name);
    if(*name == '/'){
            assert(n->racine->fils!=NULL);
            
            // Sauvegarde du pere
            //noeud* tmpPere = malloc(sizeof(noeud));
            //assert(tmpPere!=NULL);
            if(DEBUG)printf("\033[33m Chemin racine direct \033[0m\n");
            noeud* tmp=n->racine;
            liste_noeud* list=n->racine->fils;
            bool testList=false;
            w_index* chem=cons_index(name);
            assert(chem!=NULL);
            if(DEBUG)print_index(chem);
            for(int i=0;i<chem->nbr;++i){ // Boucle pour parcourir tous le chemin
                //Recherche du Deplacement 
                while(list != NULL && list->succ != NULL){
                    //Verifier que c'est bien un dossier
                    if(list->no->est_dossier==true && strcmp(list->no->nom,chem->words[i])==0){
                            tmp=list->no;
                            testList=true;
                            list=tmp->fils;
                            break;
                    }
                    list = list->succ;
                }
                //Verifier la derniere adresse si on n'a toujours pas trouve le chemin parmi les fils
                if(!testList){
                    if(list != NULL && strcmp(list->no->nom,chem->words[i])==0
                    && list->no->est_dossier==true){
                        tmp=list->no;
                        list=tmp->fils;
                    }
                    else{
                        printf("\033[31mdepCd 122: Il y a un problème dans le déplacement \033[0m\n");
                        exit(EXIT_FAILURE);
                    }
                }
                testList=false;
            }
            free_index(chem);

            //AFFECTATIONS DES ADRESSES n'a pas marché
            assert(tmp!=NULL);
            if(!validiteNoeud(tmp)){
                printf("\033[31m(depCD if 133 ) Il y a un problème dans la liaison des noeuds \033[0m\n");
                exit(EXIT_FAILURE);
            }
            return tmp;
    }
    else{
            assert(n->fils!=NULL);
            noeud* tmp=n;

            // Sauvegarde du pere
            //noeud* tmpPere = malloc(sizeof(noeud));
            //assert(tmpPere!=NULL);

            liste_noeud* list=n->fils;
            bool testList=false;
            w_index* chem=cons_index(name);
            assert(chem!=NULL);
            if(DEBUG)print_index(chem);
            for(int i=0; i<chem->nbr ;++i){ // Boucle pour parcourir tous le chemin
                //Recherche du Deplacement 
                while(list->succ != NULL){
                    //Verifier que c'est bien un dossier
                    if(DEBUG)printf(" %s , %s \n", list->no->nom,name);
                    if(list->no->est_dossier==true){
                        if(list->no->est_dossier==true && strcmp(list->no->nom,chem->words[i])==0){
                            tmp=list->no;
                            testList=true;
                            //if(list->no->pere != NULL){
                            //    tmpPere=list->no->pere;
                            //}
                            //else{
                            //    printf("\033[33m (depCD else 170) Erreur dans les deplacement internes \033[0m\n");
                            //    exit(EXIT_FAILURE);
                            //}
                            list=tmp->fils;
                            break;
                        }
                    }
                    list = list->succ;
                    if(!validiteNoeud(list->no)){
                        assert(list->no != NULL);
                        if(list->no->pere == NULL){
                            printf("\033[33m Ce noeud : %s n'a pas de pere \033[0m\n", list->no->nom);
                            //list->no->pere=tmpPere;
                            exit(EXIT_FAILURE);
                        }
                    }
                    // Sauvegarde dup pere au cas ou il y a une erreur à corriger plus tard
                    //if(list->no->pere!=NULL){
                    //    tmpPere=list->no->pere;
                    //}
                }
                //Verifier la derniere adresse si on n'a toujours pas trouve le chemin parmi les fils
                if(!testList){
                    if(strcmp(list->no->nom,chem->words[i])==0
                    && list->no->est_dossier==true){
                        tmp=list->no;
                        list=tmp->fils;
                    }
                    else{
                        printf("\033[31mdepCd 199: Il y a un problème dans le déplacement %s , %s \033[0m\n",list->no->nom, chem->words[i]);
                        exit(EXIT_FAILURE);
                    }
                }
                testList=false;
            }
            free_index(chem);
            assert(tmp!=NULL);
            if(!validiteNoeud(tmp)){
                printf("\033[31m(else depCD 208 ) Il y a un problème dans la liaison des noeuds \033[0m\n");
                exit(EXIT_FAILURE);
            }
            //printf("\033[34mcd : %s (Réussi) \033[0m\n", tmp->nom);
            return tmp;
    }
}

//Print
//Fonction auxiliaire pour print afin d'afficher le nombre de fils
int nbFils(noeud* n){
    int x=0;
    liste_noeud* parc=n->fils;
    if(n!=NULL){
        while(parc!=NULL){
            x++;
            parc=parc->succ;
        }
    }
    return x;
}

//Fonction auxliaire pour voir si un fils est situé dans ce chemin
bool verification_PresenceFils(noeud* n, liste_noeud* list){
    assert(n!=NULL);
    if(list==NULL || !validiteNoeud(n)){
        return false;
    }

    bool res=false;
    liste_noeud* parc=list;
    while(parc->succ != NULL){
        if(validiteNoeud(parc->no)){
            if(strcmp(parc->no->nom,n->nom)==0){
            if(DEBUG)printf(" VerificationPresenceFils : Verification par le fils présent directement \n");
            if(DEBUG)printf("%s , %s \n", parc->no->nom, n->nom);
            return true;
            }
            if(parc->no->est_dossier){
                if(parc->no->fils!=NULL){
                    // Verifier les sous dossiers ...
                    res=verification_PresenceFils(n,parc->no->fils);
                    if(res==true){
                        if(DEBUG)printf(" verificationPresenceFils : Vérification par les fils des élements dans la liste \n");
                        return true;
                    }
                }
            }
            parc=parc->succ;
        }
        else{
            printf("\033[31mIl y a un noeud invalide \033[0m\n");
            exit(EXIT_FAILURE);
        }
    }
    if(!validiteNoeud(parc->no) && strcmp(parc->no->nom,n->nom)==0){
        return true;
    }
    return res;
}

// Fonction auxliaire pour faire la deliaison des liste et libérer la mémoire
void suppression(noeud* pere,noeud* noeud_a_supprimer){
   
   if (pere == NULL || noeud_a_supprimer == NULL) {
        return;
    }
    // Rechercher le noeud à supprimer dans la liste de fils du père
    liste_noeud* liste_courante = pere->fils;
    liste_noeud* liste_precedente = NULL;
    while (liste_courante != NULL && liste_courante->no != noeud_a_supprimer) {
        liste_precedente = liste_courante;
        liste_courante = liste_courante->succ;
    }

    if (liste_courante == NULL) {
        // Le noeud à supprimer n'a pas été trouvé dans la liste de fils du père
        return;
    }

    // Délier le noeud à supprimer de la liste de fils du père
    if (liste_precedente == NULL) {
        pere->fils = liste_courante->succ;
    } else {
        liste_precedente->succ = liste_courante->succ;
    }

    // Supprimer les fils du noeud à supprimer récursivement
    while (noeud_a_supprimer->fils != NULL) {
        suppression(noeud_a_supprimer, noeud_a_supprimer->fils->no);
    }

    // Libérer la mémoire allouée pour la liste de fils du noeud à supprimer
    while (noeud_a_supprimer->fils != NULL) {
        liste_noeud* liste_a_supprimer = noeud_a_supprimer->fils;
        noeud_a_supprimer->fils = liste_a_supprimer->succ;
        //free(liste_a_supprimer);
    }

    // Délier le noeud à supprimer de son père et libérer la mémoire allouée pour le noeud
    free(noeud_a_supprimer); 
}

// CP
// Fonction auxiliaire de verification pour le chemin de cp
// Faire un deplacement afin de sauvegarder la copie à faire
noeud* cpVerif1(noeud* n,char*chem){
    //printf("l 595 cp Verif1 %s \n ",chem);
    if(verif(chem)==true){
        if(strcmp(chem,"")==0 || strcmp(chem,"..")==0){
            printf("l 598 - cpVerif1 : Le premier chemin de copie est incorrect");
            exit(EXIT_FAILURE);
        }
        else{
            noeud* dep=depCD(n,chem);
            if(DEBUG)printf(" ==> l 607 - Description du Noeud dans cpVeriff1 \n");
            assert(dep!=NULL);
            return dep;
        }
    }
    else{
        printf(" ==> l 614 - cpVerif1: il y a une erreur dans laformation du chemin \n");
        exit(EXIT_FAILURE);
    }
}

//! Fonction auxliaire pour s'arreter avant le dernier mot
noeud* deplacementAuxiliaireCp2(noeud* n,char* chem){
    assert(n!=NULL);
    assert(chem!=NULL);
    if(verif(chem)==false || strcmp(chem,"")==0 || strcmp(chem,"..")==0){
        printf("l 646 - deplacementCalculer : le chemin est faux \n");
        exit(EXIT_FAILURE);
    }
    if(*chem =='/'){
        bool testList=false;
        w_index* constructionChemin=cons_index(chem);
        assert(constructionChemin!=NULL);
        noeud* tmp=n->racine;
        liste_noeud* list=n->racine->fils;
        if(DEBUG)print_index(constructionChemin);
        // A voir si on verifie le cas de deplacement avec nom à la racine
        for(int i=0;i<constructionChemin->nbr-1;++i){ 
            while(list->succ!=NULL){
                if(strcmp(list->no->nom,constructionChemin->words[i])==0){
                    tmp=list->no;
                    testList=true;
                    list=tmp->fils;
                    break;
                }
                list=list->succ;
            }

            if(!testList){
                    if( strcmp(list->no->nom,constructionChemin->words[i])==0
                    && tmp->est_dossier==true){
                        tmp=list->no;
                        if(list->no->pere != list->no->racine){
                            tmp->pere=list->no->pere;
                        }
                    }
                    else{
                        printf("l 676 - deplacementCalculer : Il y a un problème dans le déplacement \n");
                        exit(EXIT_FAILURE);
                    }
            }
            testList=false;
        }
        assert(tmp!=NULL);
        free_index(constructionChemin);
        if(!validiteNoeud(tmp)){
            printf("(if deplacementAuxiliaire2) IL y a un problème dans les liaisons \n");
            exit(EXIT_FAILURE);
        }
        return tmp;        
    }
    else{
        bool testList=false;
        w_index* constructionChemin=cons_index(chem);
        assert(constructionChemin!=NULL);
        noeud* tmp=n;
        liste_noeud* list=n->fils;
        for(int i=0;i<constructionChemin->nbr-1;++i){ 
            while(list->succ!=NULL){
                if(strcmp(list->no->nom,constructionChemin->words[i])==0){
                    tmp=list->no;
                    testList=true;
                    list=tmp->fils;
                    break;
                }
                list=list->succ;
            }
            if(!testList){
                    if(strcmp(list->no->nom,constructionChemin->words[i])==0
                    && tmp->est_dossier==true){
                        tmp=list->no;
                        if(list->no->pere != list->no->racine){
                            tmp->pere=list->no->pere;
                        }
                    }
                    else{
                        printf("deplacementCalculer : Il y a un problème dans le déplacement \n");
                        exit(EXIT_FAILURE);
                    }
            }
            testList=false;
        }
        assert(tmp!=NULL);
        free_index(constructionChemin);
        if(!validiteNoeud(tmp)){
            printf("(else deplacementAuxiliaire2) IL y a un problème dans les liaisons \n");
            exit(EXIT_FAILURE);
        }
        return tmp;
    }
}

// Fonction pour copier un pointeur de la structure noeud et ses enfants
noeud* copy_noeud(noeud *src,char* chem,noeud* pere) {
    // Vérification de la validité du pointeur
    if (src == NULL) {
        return NULL;
    }
    
    // Création d'un nouveau noeud
    noeud *dest = malloc(sizeof(noeud));
    dest->est_dossier = src->est_dossier;
        // Gestion du nom à changer pour le noeud courant
        if(chem != NULL) strcpy(dest->nom, chem); 
        else strcpy(dest->nom, src->nom);

        // Gestion du pere
        if(pere==NULL) dest->pere = src->pere;
        else dest->pere = pere;
    dest->racine = src->racine;
    dest->fils = NULL;
    if(DEBUG){printf("Copie\n");
    descriptionNoeud(dest);}
    
    // Copie des enfants
    liste_noeud *src_child = src->fils;
    liste_noeud *dest_child = NULL;
    liste_noeud *prev_child = NULL;

    while (src_child != NULL) {
        // Création d'une nouvelle structure liste_noeud
        liste_noeud *new_child = malloc(sizeof(liste_noeud));
        new_child->no = copy_noeud(src_child->no,NULL,dest);
        new_child->succ = NULL;
        
        // Si c'est le premier enfant, on l'ajoute directement à la liste
        if (dest_child == NULL) {
            dest->fils = new_child;
            dest_child = dest->fils;
        }
        // Sinon, on l'ajoute à la fin de la liste
        else {
            dest_child->succ = new_child;
            dest_child = dest_child->succ;
        }
        
        // Passage à l'enfant suivant
        prev_child = src_child;
        if(DEBUG)printf(" prev_child : %s",prev_child->no->nom);
        src_child = src_child->succ;
    }
    return dest;
}

// Fonction auxiliaire pour faire un deplacement avec la creation pour la copie
void cpVerif2(noeud* copie,noeud* courant,char* chem){
    w_index* cheminParcour=cons_index(chem);
    if(DEBUG)printf("cpVerif2 nombre d'indew à copier : %d\n",cheminParcour->nbr);
    //! Soit on va directement faire la copie, soit on va faire le depalcement puis la copie
    if(cheminParcour->nbr==1){
        liste_noeud* li = courant->fils;
        // Si la ou on est n'a pas de fils
        if(li==NULL){
            ajoutL(courant,copie);
            return ;
        }
        
        // Vérifier que les fichiers n'ont pas les memes noms
        while(li->succ != NULL){
            if(strcmp(li->no->nom,courant->nom)==0){
                printf(" On ne pas faire une copie d'un noeud déjà existant \n");
                exit(EXIT_FAILURE);
            }
            li=li->succ;
        }
        noeud* save=copy_noeud(copie,cheminParcour->words[cheminParcour->nbr-1],NULL);
        if(DEBUG)printf(" NOM de la copie : %s \n", save->nom);
            
        ajoutL(courant,save);
        free_index(cheminParcour);
    }
    else{
        //Faire le deplacement vers l'avant dernier élément
        noeud* creation = deplacementAuxiliaireCp2(courant,chem);
        if(DEBUG)printf(" \033[35m nom : %s \033[0m \nn", creation->nom);
        assert(creation != NULL);

        if(creation->est_dossier==true && 
           verification_PresenceFils(copie,creation->fils)==0 && 
           verification_PresenceFils(creation,copie->fils)==0){
            
            noeud* save=copy_noeud(copie,cheminParcour->words[cheminParcour->nbr-1],NULL);
            if(DEBUG)printf(" NOM de la copie : %s \n", save->nom);
            
            ajoutL(creation,save);
            free_index(cheminParcour);   
        }
        else{
            printf(" l 794 - cpVerif2 : On ne peut pas faire une copie dans un fichier \n");
            free_index(cheminParcour);
            exit(EXIT_FAILURE);
        }    
    }
}

