#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "gestiontexte.h"
#include "fonctionauxiliaire.h"
#include "fonctionprincipale.h"
#include "debug.h"

void ls(noeud* n){
    assert(n!=NULL);
    if(n->est_dossier==true){
        if(n->fils==NULL) printf("__");
        else{
            liste_noeud* li=n->fils;
            if(li!=NULL){
                while(li->succ != NULL && validiteNoeud(li->no)==true){
                    if(li->no->est_dossier) printf("\033[35m%s \033[0m",li->no->nom);
                    else printf("%s ",li->no->nom);
                    li=li->succ;
                }
               if(li->no->est_dossier) printf("\033[35m%s \033[0m",li->no->nom);
               else printf("%s",li->no->nom);     
            }
        }
    }
    else{
        printf("\033[31mOn n'est pas dans un dossier il y a eu un deplacement inattendu!\033[0m");
        exit(EXIT_FAILURE);
    }
    printf("\n");
}

//Deplacement de chem normalement seulement dans un dossier
noeud* cd(noeud* n,char* name){
   assert(n!=NULL);
   assert(name!=NULL);
   //TRAITER LE CAS DU RETOUR A LA RACINE
   if(strcmp(name,"")==0){
        if(DEBUG) printf("\n---Retour à la racine avec CD \n ");
        n=n->racine;
        return n;
   }
   else if(verif(name)==1){
        //Traiter le cas du RETOUR
        if(strcmp(name,"..")==0){
            if(DEBUG)printf("\nRetour Direct \n");
            assert(n->pere!=NULL);
            assert(n->pere->nom!=NULL);
            if(strcmp(n->pere->nom,"")!=0){
                if(DEBUG)printf("> Retour pere possible\n");
                n=n->pere;
            }
            return n;
        }
        else{
            //return n;
            return depCD(n,name);
        }
   }
   else{
    printf("\033[31m>cd:Il y a une erreur dans le chemin qui est donné !! \033[0m");
    exit(EXIT_FAILURE);
   }
}

// Affichage du chemin du noeud sur le temrinal 
void pwd(noeud* n){ // Probleme de sens inverse à régler
    assert(n!=NULL);
    if(!validiteNoeud(n)){ 
        printf("\033[31m pwd : Il y a des problèmes de liaisons \033[0m");
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
        printf("\033[31m mkdir: Trop de caractere dans le nom ou trop peu \033[0m\n");
        exit(EXIT_FAILURE);
    }
    if(no->est_dossier==false){
        printf("\033[31m mkdir : Il y a une erreur \033[0m\n");
        exit(EXIT_FAILURE);
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
                    printf("\033[31m mkdir : Il y a déjà ce nom de fichier dans la liste \033[0m\n");
                    return ;
                }
                parc=parc->succ;
            }
            assert(parc!=NULL);
            if(strcmp(parc->no->nom,nom)==0){
                printf("\033[31mmkdir :  - Il y a déjà ce nom de fichier dans la liste \033[0m\n");
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
    }
}

//Creation de fichier
void touch(noeud* no,char* nom){
    assert(nom !=NULL);
    assert(no!=NULL);
    if(strlen(nom)>99 || strcmp(nom,"")==0){
        printf("\033[31m touch : Trop de caracterre dans le nom ou trop peu \033[0m\n");
        return ;
    }
    if(no->est_dossier){
        // Ajouter directement au debut 
        if(no->fils==NULL){
            if(DEBUG)printf(" Parcour de TOUCH direct \n");
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
                    printf("\033[31mtouch : Il y a déjà ce nom de fichier dans la liste \033[0m\n");
                    return ;
                }
                parc=parc->succ;
            }
            if(strcmp(parc->no->nom,nom)==0){
                    printf("\033[31mtouch :  Il y a déjà ce nom de fichier dans la liste \033[0m\n");
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
void print(noeud* n){ 
    if(n==NULL){
        printf("\031[31m Le noeud à décrire est NULL \033[0m\n");
        return ;
    }
    noeud* parc=n;
    assert(parc!=NULL);
    liste_noeud* save = n->fils;
    
    if(save!=NULL && save->no != NULL && strcmp(save->no->nom,"") !=0
       && save->no->pere != NULL && save->no->racine != NULL){
        if(strcmp(parc->nom,parc->pere->nom)==0){
            printf("Noeud %s , %d fils: ",parc->nom,nbFils(parc));
            liste_noeud* pFils=parc->fils;
            while(pFils!=NULL){
                    printf(" %s",pFils->no->nom);
                    if(pFils->no->est_dossier){
                        printf("\033[31m(D)| \033[0m");
                    }
                    else{
                        printf("\033[32m(F)| \033[0m");
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
                        printf("\033[31m(D)| \033[0m");
                    }
                    else{
                        printf("\033[32m(F)| \033[0m");
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
        if(DEBUG)printf("fils null \n");
        if(strcmp(n->nom,n->pere->nom)==0){
            printf("Noeud: %s ", n->nom);
            if(n->est_dossier==true){
                printf("\033[31m(D)|\033[0m 0 fils\n");
            }
            else{
                printf("\033[32m (F)|\033[0m 0 fils\n");
            }
        }
        else{
            printf("Noeud : %s ", n->nom);
            if(n->est_dossier==true){
                printf("\033[31m(D)|\033[0m père : %s , 0 fils \n", n->pere->nom);
            } 
            else{
                printf("\033[31m(F)|\033[0m père: %s , 0 fils \n",n->pere->nom);
            }
        }
    }
}

void rm(noeud* n,char* chem){
    
    if((strlen(chem)==2 && strcmp(chem,"..")==0) || strcmp(chem,"")==0){
        printf("\n\033[31ml 274 - rm: Le chemin que l'on a donné n'est pas correct \n\033[0m ");
        exit(EXIT_FAILURE);
    }
    if(verif(chem)){
        //On va maintenant se déplacer vers ce chemin via un cd 
        noeud* dep=depCD(n,chem);
        assert(dep!=NULL);
        
        //On va maintenant vérifier si le noeud courant n'est pas dans ce chemin
        if(verification_PresenceFils(n,dep->fils)==0 && dep != n){
            // On pourra alors libérer la profondeur si on n'est pas situé sur le noeud courant
            if(DEBUG) printf("rm : pere:%s  , noeud à supprimer %s \n",dep->pere->nom,dep->nom);
            //suppression(dep->pere,dep);
            free(dep);
        }
        else{
            printf("\n \033[31ml 289 - rm: Ce chemin est sur le noeud courant on ne peut pas le supprimer \033[0m\n");
            free(dep);
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf(" \n\033[31ml 294 - rm: Ce chemin est incorrect \033[0m \n");
        exit(EXIT_FAILURE);
    }
}

//Copie de chemin dans un dossier
void cp(noeud* n,char* chem1,char* chem2){
    //Faire les vérifications nécessaire pour éviter de copier dans le noeud ou on est situé
    if(verif(chem1)==true){
        if(DEBUG)printf("\033[34ml 335 - cp : Le chemin que l'on a donné est correct \033[0m \n");
        noeud* dep = cpVerif1(n,chem1);
        assert(dep!=NULL);
        if(DEBUG)printf(" Voici le nom de la copie à faire : %s \n",dep->nom );
        cpVerif2(dep,n,chem2);
    }
    else{
        if(DEBUG)printf("\033[31m l 343 : Erreur de chemin dans cp \033[0m\n");
        exit(1);
    }
}

//Faire des déplacements pour des suppressions
void mv(noeud* n,char* chem1,char* chem2){
    cp(n,chem1,chem2);
    rm(n,chem1);
}
