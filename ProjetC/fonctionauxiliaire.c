#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include "gestiontexte.h"
#include "fonctionauxiliaire.h"

noeud* creationDebut(){
    noeud* n = malloc(sizeof(noeud));
    n->nom="";
    n->fils=NULL;
    n->pere=n;
    n->racine=n;
}

// Fonction auxiliaire de verification de la validité d'un noeud
bool validiteNoeud(noeud* n){
    return n != NULL && n->racine != NULL && n->pere != NULL;
}

//Fonction auxiliaire ajout dans une liste
void ajoutL(noeud* courant,liste_noeud* l, noeud* n){
    assert(courant!=NULL);
    assert(n!=NULL);
    //assert(l!=NULL);
    if(courant != NULL && l!=NULL && n != NULL ){
        printf("1 Ajout Liste \n");
        if(l->succ==NULL){
            // Si le suivant est directement NULL
            liste_noeud* aj=malloc(sizeof(liste_noeud));
            assert(aj!=NULL);
            aj->no=n;
            aj->succ=NULL;
            l->succ=aj;
        }
        else{
            // Si on doit faire un parcour des fils
            liste_noeud* tmp=l->succ;
            while(tmp->succ != NULL){
                tmp->succ=tmp->succ;
            }
            liste_noeud* aj=malloc(sizeof(liste_noeud));
            assert(aj!=NULL);
            aj->no=n; aj->succ=NULL;
            tmp->succ=aj;    
        }
    }
    else{ 
        // Creation des fils de la liste
        printf("Ajout Liste 2 \n");
        if(n != NULL){
            if(courant->fils==l){
                printf("==>Reussi l'ajout \n");
                l=malloc(sizeof(liste_noeud*));
                l->no=n;
                l->succ=NULL;
            }
        }
        else{
            printf(" Le noeud à ajouter dans la liste courante est null !! ");
        }
    }
}

// CD
//Faire une fonction auxiliaire pour le deplacement dans un fichier
noeud* depCD(noeud* n, char* name){
    if(*name == '/'){
            assert(n->racine->fils!=NULL);
            
            // Sauvegarde du pere
            noeud* tmpPere = malloc(sizeof(noeud*));
            assert(tmpPere!=NULL);
            
            noeud* tmp=n->racine;
            liste_noeud* list=n->racine->fils;
            bool testList=false;
            w_index* chem=cons_index(name);
            assert(chem!=NULL);

            for(int i=0;i<chem->nbr;++i){ // Boucle pour parcourir tous le chemin
                //Recherche du Deplacement 
                while(list->succ != NULL){
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
                    if(strcmp(list->no->nom,chem->words[i])==0
                    && tmp->est_dossier==true){
                        tmp=list->no;
                    }
                    else{
                        printf("cd 299: Il y a un problème dans le déplacement \n");
                        exit(1);
                    }
                }
                testList=false;
            }
            free_index(chem);

            //AFFECTATIONS DES ADRESSES n'a pas marché
            assert(tmp!=NULL);
            if(!validiteNoeud(tmp)){
                printf("(depCD if) Il y a un problème dans la liaison des noeuds \n");
                exit(1);
            }
            return tmp;
    }
    else{
            assert(n->fils!=NULL);
            noeud* tmp=n;

            // Sauvegarde du pere
            noeud* tmpPere = malloc(sizeof(noeud*));
            assert(tmpPere!=NULL);

            liste_noeud* list=n->fils;
            bool testList=false;
            w_index* chem=cons_index(name);
            assert(chem!=NULL);

            print_index(chem);
            for(int i=0; i<chem->nbr ;++i){ // Boucle pour parcourir tous le chemin
                //Recherche du Deplacement 
                while(list->succ != NULL){
                    //Verifier que c'est bien un dossier
                    if(list->no->est_dossier==true){
                        if(list->no->est_dossier==true && strcmp(list->no->nom,chem->words[i])==0){
                            tmp=list->no;
                            testList=true;
                            if(list->no->pere != NULL){
                                tmpPere=list->no->pere;
                            }
                            else{
                                printf("(depCD else) Erreur dans les deplacement internes \n");
                                exit(1);
                            }
                            list=tmp->fils;
                            break;
                        }
                    }
                    list = list->succ;
                    if(!validiteNoeud(list->no)){
                        assert(list->no != NULL);
                        if(list->no->pere == NULL){
                            printf(" Ce noeud : %s n'a pas de pere \n", list->no->nom);
                            list->no->pere=tmpPere;
                            //exit(1);
                        }
                    }
                    // Sauvegarde dup pere au cas ou il y a une erreur à corriger plus tard
                    if(list->no->pere!=NULL){
                        tmpPere=list->no->pere;
                    }
                }
                //Verifier la derniere adresse si on n'a toujours pas trouve le chemin parmi les fils
                if(!testList){
                    if(strcmp(list->no->nom,chem->words[i])==0
                    && tmp->est_dossier==true){
                        tmp=list->no;
                    }
                    else{
                        printf("cd 345: Il y a un problème dans le déplacement \n");
                        exit(1);
                    }
                }
                testList=false;
            }
            free_index(chem);
            assert(tmp!=NULL);
            if(!validiteNoeud(tmp)){
                printf("(else depCD) Il y a un problème dans la liaison des noeuds \n");
                exit(1);
            }
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


// RM 
//Fonction auxiliaire pour faire un deplacement même dans un noeud
noeud* deplacementCalculer(noeud* n, char* chem){
    assert(n!=NULL);
    assert(chem!=NULL);
    if(verif(chem)==false || strcmp(chem,"")==0 || strcmp(chem,"..")==0){
        printf("l 622 - deplacementCalculer : le chemin est faux \n");
        exit(1);
    }
    if(*chem =='/'){
        bool testList=false;
        w_index* constructionChemin=cons_index(chem);
        assert(constructionChemin!=NULL);
        noeud* tmp=n->racine;
        liste_noeud* list=n->racine->fils;
        // A voir si on verifie le cas de deplacement avec nom à la racine
        for(int i=1;i<constructionChemin->nbr;++i){ 
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
                        printf("l 649 - deplacementCalculer : Il y a un problème dans le déplacement \n");
                        exit(1);
                    }
            }
            testList=false;
        }
        assert(tmp!=NULL);
        free_index(constructionChemin);
        if(!validiteNoeud(tmp)){
            printf("(if DeplacementCalculer) IL y a un problème dans les liaisons \n");
            exit(1);
        }
        return tmp;        
    }
    else{
        bool testList=false;
        w_index* constructionChemin=cons_index(chem);
        assert(constructionChemin!=NULL);
        noeud* tmp=n;
        liste_noeud* list=n->fils;
        for(int i=0;i<constructionChemin->nbr;++i){ 
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
                        exit(1);
                    }
            }
            testList=false;
        }
        assert(tmp!=NULL);
        free_index(constructionChemin);
         if(!validiteNoeud(tmp)){
            printf("(else DeplacementCalculer) IL y a un problème dans les liaisons \n");
            exit(1);
        }
        return tmp;
       
    }
}

//Fonction auxliaire pour voir si un fils est situé dans ce chemin
bool verification_PresenceFils(noeud* n, liste_noeud* list){
    assert(n!=NULL);
    if(list==NULL){
        return false;
    }

    bool res=false;
    liste_noeud* parc=list;
    while(parc->succ!=NULL){
        if(strcmp(parc->no->nom,n->nom)==0){
            printf("VerificationPresenceFils : Verification par le fils présent directement \n");
            printf("%s , %s \n", parc->no->nom, n->nom);
            return true;
        }
        if(parc->no->est_dossier){
            if(parc->no->fils!=NULL){
                // Verifier les sous dossiers ...
                res=verification_PresenceFils(n,parc->no->fils);
                if(res==1){
                    printf("verificationPresenceFils : Vérification par les fils des élements dans la liste \n");
                    return true;
                }
            }
        }
        parc=parc->succ;
    }
    if(strcmp(parc->no->nom,n->nom)==0){
        printf("verificationPresenceFils : Vérification par le dernier élément dans la liste \n");
        return true;
    }

    printf("verificationPresenceFils : Pas de présence avec toute la vérification \n");
    return res;
}

//Fonction auxliaire pour verifier la validité du chemin à parcourir
bool chemin_existe(noeud* n,char* chem){
    // NORMALEMENT IL FAUT ENCORE VERIFIER QU IL NE FAUT PAS SUPPRIMER LE NOEUD COURANT
    assert(n!=NULL);
    assert(chem!=NULL);
    
    if(verif(chem)==0){
        printf("l 743 : Chemin_existe :  Le chemin est vide \n");
        return false;
    }

    if(strcmp(chem,"..")!=0 || strcmp(chem,"")!=0){
            printf("l 748 : Chemin_existe : Le chemin  respecte les normes \n");
    }
    else{
            printf("l 751 : Chemin_existe : Le chemin  est incohérant \n");
            return false;
    }

    // Parcour d'un chemin absolu
    if(*chem=='/'){ // verifier tous les fils que notre noeud courant n'est pas dans le chemin
        w_index* index=cons_index(chem);
        assert(index!=NULL);
        liste_noeud* parc=n->racine->fils;
        print_index(index);
        for(int i=1;i<index->nbr;++i){
            assert(parc!=NULL);
            while(parc->succ!=NULL){
                if(parc->no->est_dossier==true){
                    if(strcmp(parc->no->nom,index->words[i])==0){
                        if((i+1)>=index->nbr){
                            break;
                        }
                        else{
                            parc=parc->no->fils;
                            break;
                        }
                    }
                }
                parc=parc->succ;
            }
            if(strcmp(parc->no->nom,index->words[i])==0){
                parc=parc->no->fils;
            }
            else{
                printf("l 781 - Chemin_existe / : Il y a un problème dans le déplacement du chemin \n");
                printf(" %s : parc->no->nom \n",parc->no->nom);
                printf("%s : index->words[i] \n",index->words[i]);
                return false;
            }
        }
        free_index(index);
    }
    else{
        w_index* index=cons_index(chem);
        assert(index!=NULL);
        liste_noeud* parc=n->fils;
        
        for(int i=0;i<index->nbr;++i){
            assert(parc!=NULL);
            while(parc->succ!=NULL){
                if(parc->no->est_dossier==true){
                    if(strcmp(parc->no->nom,index->words[i])==0){
                        parc=parc->no->fils;
                        break;
                    }
                }
                parc=parc->succ;
            }
            if(strcmp(parc->no->nom,index->words[i])==0){
                parc=parc->no->fils;
            }
            else{
                printf("l 809 Chemin_existe : Il y a un problème dans le déplacement du chemin \n");
                printf(" %s \n",parc->no->nom);
                printf(" %s \n",index->words[i]);
                return false;
            }
        }
        free_index(index);
    }
    return true;
}

// Fonction auxliaire pour faire la deliaison des liste
void suppression(noeud* pred,noeud* n){
    if(pred != NULL ){
        liste_noeud* precedent=NULL;
        liste_noeud* courant=pred->fils;
        liste_noeud* suivant=pred->fils->succ;
        while(courant->no!=n && suivant!=NULL){
            precedent=courant;
            courant=suivant;
            suivant=suivant->succ;
        }
        if(courant->no==n){
            precedent->succ=suivant;
            // free(courant);
        }
    }

    if(n!=NULL){
        if(n->fils == NULL){
            printf("l 839 : suppression : un seul élément \n");
            free(n);
        } 
        else{
            printf("l 843 : suppression: plusieurs élément \n");
            liste_noeud* list=n->fils;
            while(list != NULL){
                liste_noeud* tmp1 = list->succ;
                suppression(NULL,list->no);
                list=tmp1;
            }
            free(n);
        }
    }
}

//Fonction auxiliaire pour supprimer tous les fils du noeud et le noeud lui meme
void liberation_noeud(noeud* n,char* chem){
   assert(n!=NULL);
   assert(chem!=NULL);
   
   w_index* index_Chem=cons_index(chem);
   //print_index(index_Chem);
   if(*chem=='/'){
    printf("l 863 : liberation_noeud: racine \n");
    
    noeud* pred=NULL;
    noeud* parc=n->racine;
    
    liste_noeud* list=parc->fils;
    liste_noeud* li_Pred=NULL;

    // ---------------------- REMARQUE -------------------------------------------
    //Commencer à l'indice 0 si on prend pas en compte le nom de ra racine
    for(int i=0;i<index_Chem->nbr;++i){
        while(list->succ != NULL){
            if(strcmp(index_Chem->words[i],list->no->nom)==0){
                pred=parc;
                parc=list->no;
                li_Pred=list;
                list=parc->fils;
                break; 
            }
            li_Pred=list;
            list=list->succ;
        }
        //Le dernier élément non null
        if(strcmp(list->no->nom,index_Chem->words[i])==0){
            pred=parc;
            parc=list->no;

            li_Pred=list;
            list=parc->fils;
        }
        else{
            printf("l 894 : Liberation noeud (if->else): il y a une erreur \n");
            exit(1);
        }
    }

    printf("\n l 899 : Libération noeud : description du noeud à supprimer \n");
    printf("->courant: %s \n",parc->nom);
    if(pred!=NULL )printf("->pred : %s \n",pred->nom);
    if(list!=NULL ) printf("Liste courante : %s \n", list->no->nom);
    if(li_Pred!=NULL) printf("Liste pred : %s \n" ,li_Pred->no->nom);

    // Maintenant on peut supprimer tous les fils
    suppression(pred,parc);   
   }
   else{
    printf("l 909 : Libération noeud : courant \n");
    noeud* pred=NULL;
    noeud* parc=n;
    
    liste_noeud* li_Pred=NULL;
    liste_noeud* list=parc->fils;
     for(int i=0;i<index_Chem->nbr;++i){
        while(list->succ != NULL){
            if(strcmp(index_Chem->words[i],list->no->nom)==0){
                pred=parc;
                parc=list->no;
                li_Pred=list;
                list=parc->fils;
                break; 
            }
             li_Pred=list;
            list=list->succ;
        }
        //Le dernier élément non null
        if(strcmp(list->no->nom,index_Chem->words[i])==0){
            pred=parc;
            parc=list->no;

            li_Pred=list;
            list=parc->fils;
        }
        else{
            printf("l 936 : Liberation noeud (else->else): il y a une erreur \n");
            exit(1);
        }
    }

    printf("l 941 : Libération noeud : description du noeud à supprimer \n");
    printf("%s\n",parc->nom);
    if(pred!=NULL )printf("->pred : %s \n",pred->nom);
    if(list!=NULL ) printf("Liste courante : %s \n", list->no->nom);
    if(li_Pred!=NULL) printf("LIste pred : %s \n" ,li_Pred->no->nom);

    // Maintenant on peut supprimer tous les fils
    suppression(pred,parc);
   }
}

// CP
//Fonction auxiliaire de verification pour le chemin de cp
// Faire un deplacement afin de sauvegarder la copie à faire
noeud* cpVerif1(noeud* n,char*chem){
    printf("l 995 cp Verif1 %s \n ",chem);
    if(verif(chem)==true){
        if(strcmp(chem,"")==0 || strcmp(chem,"..")==0){
            printf("l 998 - cpVerif1 : Le premier chemin de copie est incorrect");
            exit(1);
        }
        else{
            noeud* dep=deplacementCalculer(n,chem);
            printf(" ==> l 1003 - Description du Noeud dans cpVeriff1 \n");
            assert(dep!=NULL);
            //print(dep);
            return dep;
        }
    }
    else{
        printf(" ==> l 1010 - cpVerif1: il y a une erreur dans laformation du chemin \n");
        exit(1);
    }
}

//Fonction auxliaire pour s'arreter avant le dernier mot
noeud* deplacementAuxiliaireCp2(noeud* n,char* chem){
    assert(n!=NULL);
    assert(chem!=NULL);
    if(verif(chem)==false || strcmp(chem,"")==0 || strcmp(chem,"..")==0){
        printf("l 622 - deplacementCalculer : le chemin est faux \n");
        exit(1);
    }
    if(*chem =='/'){
        bool testList=false;
        w_index* constructionChemin=cons_index(chem);
        assert(constructionChemin!=NULL);
        noeud* tmp=n->racine;
        liste_noeud* list=n->racine->fils;
        // A voir si on verifie le cas de deplacement avec nom à la racine
        for(int i=1;i<constructionChemin->nbr-1;++i){ 
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
                        printf("l 649 - deplacementCalculer : Il y a un problème dans le déplacement \n");
                        exit(1);
                    }
            }
            testList=false;
        }
        assert(tmp!=NULL);
        free_index(constructionChemin);
        if(!validiteNoeud(tmp)){
            printf("(if deplacementAuxiliaire2) IL y a un problème dans les liaisons \n");
            exit(1);
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
                        exit(1);
                    }
            }
            testList=false;
        }
        assert(tmp!=NULL);
        free_index(constructionChemin);
        if(!validiteNoeud(tmp)){
            printf("(else deplacementAuxiliaire2) IL y a un problème dans les liaisons \n");
            exit(1);
        }
        return tmp;
    }
}

//Fonction auxiliaire pour faire un deplacement avec la creation pour la copie
void cpVerif2(noeud* copie,noeud* courant,char* chem){
    w_index* cheminParcour=cons_index(chem);
    if(cheminParcour->nbr==1){
        liste_noeud* li = courant->fils;
        while(li != NULL){
            if(strcmp(li->no->nom,courant->nom)==0){
                printf(" On ne pas faire une copie d'un noeud déjà existant \n");
                exit(1);
            }
            li=li->succ;
        }

        printf("-------------- 1 Affichage avant la copie -----------------\n");
        noeud* save = copie;
        printf(" Le noeud à copier : \n");
        memmove(save->nom,cheminParcour->words[cheminParcour->nbr-1],sizeof(char)*strlen(cheminParcour->words[cheminParcour->nbr-1]));
        //print(save);
        printf(" Le noeud ou on va faire la copie \n");
        //print(courant);
        
        assert(save!=NULL);
        //ajouter maintenant la copie du fichier ou du dossier
        ajoutL(courant,courant->fils,save);
        printf(" ----------------1 Affichage après la copie ----------------- \n");
        //print(save);
        printf("-----------------------------------------------------------------\n");
        //print(courant);

         free_index(cheminParcour);
    }
    else{
        //Faire le deplacement vers l'avant dernier élément
        noeud* creation=deplacementAuxiliaireCp2(courant,chem);
        printf(" l 1118 - cpVerif2 : Voici une description du noeud ou on va faire la copie : \n");
        
        assert(creation != NULL);
        if(creation->est_dossier==true){
            printf(" l 1107 - cpVerif2 : Ce chemin est bien un dossier \n");
        }
        else{
            printf("l 1110 - cpVerif2 : On ne peut pas faire une copie dans un fichier \n");
            free_index(cheminParcour);
            exit(1);
        }
        if(verification_PresenceFils(copie,creation->fils)==0 && verification_PresenceFils(creation,copie->fils)==0){
            printf(" l 1114 :  cpVerif2 : _Normalement ils ne sont pas liés et on peut faire une copie ... \n");
             assert(cheminParcour != NULL);
            noeud* save=malloc(sizeof(noeud*));
            save=copie;
            memmove(save->nom,cheminParcour->words[cheminParcour->nbr-1],sizeof(char)*strlen(cheminParcour->words[cheminParcour->nbr-1]));

             printf("--------------2 Affichage avant la copie -----------------\n");
             //print(courant);
             ajoutL(courant,courant->fils,save);
             printf(" ----------------2 Affichage après la copie ----------------- \n");
             //print(courant);

             free_index(cheminParcour);
        }
        else{
            printf("l:1121 Bizarre ... \n");
             free_index(cheminParcour);
            exit(1);
        }
    }
}

