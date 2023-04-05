#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "gestiontexte.h"
#include "fonctionauxiliaire.h"
#include "fonctionprincipale.h"

void ls(noeud* n){
    assert(n!=NULL);
    printf("\n");
    // Parcours de la liste des fils 
    if(n->est_dossier){
        //printf("Parcour Debut Dans LS \n");
        if(n->fils==NULL){
            printf("-- Vide LS\n");
        }
        else{
            liste_noeud* li=n->fils;
            // Si il n'y a pas de fils 
            if(li==NULL){
                printf(" FILS NULL\n"); 
            }
            else{
            printf("\n LS FILS\n");
                while(li->succ != NULL && validiteNoeud(li->no)==true){

                    printf("%s\n",li->no->nom);
                    li=li->succ;
                }
                printf("%s\n",li->no->nom);
            }
        }
    }
    printf("\n");
}

//Deplacement de chem normalement seulement dans un dossier
noeud* cd(noeud* n,char* name){
   assert(n!=NULL);
   assert(name!=NULL);
   //TRAITER LE CAS DU RETOUR A LA RACINE
   if(strcmp(name,"")==0){
    //printf("\n---Retour à la racine avec CD \n ");
    n=n->racine;
     return n;
   }
   else if(verif(name)==1){
    //Traiter le cas du RETOUR
    if(strcmp(name,"..")==0){
        //printf("\nRetour Direct \n");
        assert(n->pere!=NULL);
        assert(n->pere->nom!=NULL);
        if(strcmp(n->pere->nom,"")!=0){
            printf("=> Retour pere possible");
            n=n->pere;
        }
        return n;
    }
    else{
           return depCD(n,name);
        }
   }
   else{
    printf("=> cd : Il y a une erreur dans le chemin qui est donné !! ");
    exit(1);
   }
}

// Affichage du chemin du noeud sur le temrinal 
void pwd(noeud* n){ // Probleme de sens inverse à régler
    assert(n!=NULL);
    if(!validiteNoeud(n)){ 
        printf(" pwd : Il y a des problèmes de liaisons ");
        exit(EXIT_FAILURE);
    }
   if(strcmp(n->racine->nom,n->nom)==0){
    return ;
   }
    pwd(n->pere); // Appel récursif pour le noeud père
    printf("/%s", n->nom); // Affichage du nom du noeud courant avec un "/"
}

//Creation de Dossier
void mkdir(noeud* no,char* nom){
    assert(no!=NULL);
    assert(nom!=NULL);
    if(strlen(nom)>99 || strcmp(nom,"")==0){
        printf("l4 26 mkdir: Trop de caracterre dans le nom ou trop peu \n");
        exit(1);
    }
    if(no->est_dossier==false){
        printf(" mkdir : Il y a une erreur \n");
        exit(1);
    }
    
    if(no->fils==NULL){
        liste_noeud* list=malloc(sizeof(liste_noeud));
        noeud* li=malloc(sizeof(noeud));
        li->est_dossier=true;
        strcpy(li->nom,nom);
        li->racine=no->racine;
        li->pere=no;
        li->fils=NULL;
        list->no=li;
        list->succ=NULL;
        no->fils=list;
    }
    else{
        //Parcour des fils puis ajout 
        liste_noeud* parc=no->fils;
            while(parc->succ!=NULL){
                if(strcmp(parc->no->nom,nom)==0){
                    printf("l 451 - mkdir : Il y a déjà ce nom de fichier dans la liste\n");
                    return ;
                }
                parc=parc->succ;
            }
            assert(parc!=NULL);
            if(strcmp(parc->no->nom,nom)==0){
                printf("l 457 - Il y a déjà ce nom de fichier dans la liste\n");
                return ;
            }

            // Gestion des affectations
            liste_noeud* suiv=malloc(sizeof(liste_noeud));
            assert(suiv!=NULL);
            suiv->succ=NULL;
            noeud* li=malloc(sizeof(noeud));
            assert(li!=NULL);
            li->est_dossier=true;
            strcpy(li->nom,nom);
            li->racine=no->racine;
            assert(li->racine!=NULL);
            li->pere=no;
            assert(li->pere!=NULL);
            li->fils=NULL;
            suiv->no=li;
            
            parc->succ=suiv;
            printf("\n"); // Debug
    }
}

//Creation de fichier
void touch(noeud* no,char* nom){
    assert(nom !=NULL);
    assert(no!=NULL);
    if(strlen(nom)>99 || strcmp(nom,"")==0){
        printf("l 483 touch : Trop de caracterre dans le nom ou trop peu \n");
        return ;
    }
    if(no->est_dossier){
        // Ajouter directement au debut 
        if(no->fils==NULL){
            //printf(" Parcour de TOUCH direct \n");
            liste_noeud* list=malloc(sizeof(liste_noeud));
            list->succ=NULL;
            noeud* li=malloc(sizeof(noeud));
            li->est_dossier=false;
            strcpy(li->nom,nom);
            li->racine=no->racine;
            li->pere=no;
            li->fils=NULL;
            list->no=li;
            no->fils=list;
        }
        else{
            //Parcour des fils puis ajout 
            liste_noeud* parc=no->fils;
            while(parc->succ!=NULL){
                if(strcmp(parc->no->nom,nom)==0){
                    printf("l 505 - touch : Il y a déjà ce nom de fichier dans la liste\n");
                    return ;
                }
                parc=parc->succ;
            }
            if(strcmp(parc->no->nom,nom)==0){
                    printf("l 505 - Il y a déjà ce nom de fichier dans la liste\n");
                    return ;
            }

            // Gestion des affectations
            liste_noeud* suiv=malloc(sizeof(liste_noeud));
            suiv->succ=NULL;
            noeud* li=malloc(sizeof(noeud));
            li->est_dossier=false;
            strcpy(li->nom,nom);
            li->racine=no->racine;
            li->pere=no;
            li->fils=NULL;
            suiv->no=li;
            parc->succ=suiv;
        }
    }
}

//Print
void print(noeud* n){ // IL y a un probleme quand on ne part pas de la racine
    if(n==NULL){
        printf(" Le noeud à décrire est NULL \n");
        return ;
    }
    noeud* parc=n;
    assert(parc!=NULL);
    liste_noeud* save = n->fils;
    if(save!=NULL && save->no != NULL && strcmp(save->no->nom,"")!=0 &&
     save->no->pere != NULL && save->no->racine != NULL){
        if(strcmp(parc->nom,parc->pere->nom)==0){
            printf("Noeud %s , %d fils: ",parc->nom,nbFils(parc));
            liste_noeud* pFils=parc->fils;
            while(pFils!=NULL){
                    printf(" %s",pFils->no->nom);
                    if(pFils->no->est_dossier){
                        printf("(D)| ");
                    }
                    else{
                        printf("(F)| ");
                    }
            pFils=pFils->succ;
            }
        printf("\n");
        }
        else{
            printf("Noeud %s,  pere: %s , %d fils: ",parc->nom,parc->pere->nom,nbFils(parc));
            liste_noeud* pFils=parc->fils;
            
            while(pFils!=NULL){
                printf(" %s ",pFils->no->nom);
                if(pFils->no !=NULL){
                    if(pFils->no->est_dossier==true){
                        printf("(D)| ");
                    }
                    else{
                        printf("(F)| ");
                    }
                }
            pFils=pFils->succ;
            }
            
        printf("\n");
        }
        
        // Parcour recursif de nos éléments
        while(save!=NULL){
            print(save->no);
            save=save->succ;
        }
    }
    else{
        //printf("fils null \n");
        if(strcmp(n->nom,n->pere->nom)==0){
            printf("Noeud: %s ", n->nom);
            if(n->est_dossier==true){
                printf("(D)| 0 fils\n");
            }
            else{
                printf(" (F)| 0 fils\n");
            }
        }
        else{
            printf("Noeud : %s ", n->nom);
            if(n->est_dossier==true){
                printf("(D)| père : %s , 0 fils \n", n->pere->nom);
            } 
            else{
                printf("(F)| père: %s , 0 fils \n",n->pere->nom);
            }
        }
    }
}


void rm(noeud* n,char* chem){
    // La manière dont j'ai imaginé est de verifier en premier la cohérence du chemin 
    // Ensuite on va vérifier que c'est un chemin ou notre noeud n'est pas situé 

    if(chemin_existe(n,chem)==1){
        printf("\n \033[34m l 302 - rm: Le chemin que l'on a donné est correct \033[0m \n");
        //On va maintenant se déplacer vers ce chemin via un cd 
        noeud* dep=deplacementCalculer(n,chem);
        assert(dep!=NULL);

        //On va maintenant vérifier si le noeud courant n'est pas dans ce chemin
        if(verification_PresenceFils(n,dep->fils)==0){
            printf("\n \033[34m l 312 - rm: Ce chemin n'est pas sur le noeud courant où on est situé \033[0m \n");
            
            //Utiliser une fonction auxiliaire de libération de la mémoire
            // On pourra alors libérer la profondeur si on n'est pas situé sur le noeud courant
            printf("\n \033[34m l 316 - rm : liberation des noeuds \033[0m \n");
            liberation_noeud(n,chem);
        }
        else{
            printf("\n \033[33m l 320 - rm: Ce chemin est sur le noeud courant on ne peut pas le supprimer \033[0m\n");
            exit(1);
        }
    }
    else{
        printf(" \n \033[33m l 325 - rm: Ce chemin est incorrect \033[0m \n");
        exit(1);
    }
}

//Copie de chemin dans un dossier
void cp(noeud* n,char* chem1,char* chem2){

    //Faire les vérifications nécessaire pour éviter de copier dans le noeud ou on est situé
    if(chemin_existe(n,chem1)==1){
        printf("\033[34m l 335 - cp : Le chemin que l'on a donné est correct \033[0m \n");
        noeud* dep = cpVerif1(n,chem1);
        assert(dep!=NULL);
        printf(" Voici le nom de la copie à faire : %s \n",dep->nom );
        
        cpVerif2(dep,n,chem2);
    }
    else{
        printf("\033[31m l 343 : Erreur de chemin dans cp \033[0m\n");
        exit(1);
    }
}


//Faire des déplacements pour des suppressions
void mv(noeud* n,char* chem1,char* chem2){
    // Pour bien faire mv il faut etre sur que cp et rm fonctionne bien
}
