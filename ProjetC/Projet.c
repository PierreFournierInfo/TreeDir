#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

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


//Fonction auxiliaire ajout dans une liste
void ajoutL(liste_noeud* l, noeud* n){
    assert(l!=NULL);assert(n!=NULL);
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

//Fonction de description auxiliaire 
void descriptionNoeud(noeud* d){
    printf("-- DESCRIPTION DU NOEUD --\n");
    if(d->est_dossier){
        printf("Ce noeud est un dossier, ");
    }
    printf("Son nom est : %s et le nom de son pere est : %s\n",d->nom,d->pere->nom);
    printf("Le nom de sa racine est : %s \n",d->racine->nom);
    if(d->fils!=NULL){
        printf(" Il possède des fils\n");
    }

}

//ls
void ls(noeud* n){
    assert(n!=NULL);
    // Parcours de la liste des fils 
    if(n->est_dossier){
        //printf("Parcour Debut Dans LS \n");
        if(n->fils==NULL){
            printf("--Vide LS\n");
        }
        else{
            liste_noeud* li=n->fils;
            // Si il n'y a pas de fils 
            if(li==NULL){
                printf("FILS NULL\n"); 
            }
            else{
            printf("\nLS FILS\n");
                while(li->succ != NULL){
                    printf("%s\n",li->no->nom);
                    li=li->succ;
                }
            printf("%s\n",li->no->nom);
            }
        }
    }
}

//------------------ Des methodes auxiliaires pour gérer des taches repetitives ---------------------------------------------------
//Verifier la coherence du mot donné
bool verif(const char* mot){
    //Cas d'un chemin vide
    if(strcmp(mot,"")==0){
        //printf("Verif : Chemin vide dans la vérification \n");
        return false;
    }

    // Cas retour au noeud Racine
    if(strlen(mot)==2){
        if(strcmp(mot,"..")==0){
            return true;
        }
    }
    for(const char* i=mot; *i!='\0'; ++i){
        //Verifier tous les cas d'erreurs d'une chaine de caractere
        if(isspace(*i) || 
           (*(i+1)=='\0' && (*i)=='/') ||
           (!isdigit(*i)&&!isalpha(*i)&&(*i)!='/') ||
           (*(i+1)!='\0' &&*i=='/'&& *(i+1)=='/')){
                //Juste une cond pour tester un cas de racine
                if(*i=='~'){
                    //printf("Verif : Verification racine\n");
                }
                else{
                    //printf("verif : Il y a une erreur dans la formation du mot !!\n");
                    return false;
                }
        }
    }
    //printf("\n MOT CORRECT \n");
    return true;
}

int nbr_words(const char* a){
    if(verif(a)){
        int res=0;
        assert(a!=NULL);
            if(*a=='/'){
                for(const char* ind=a+1; *(ind) !='\0'; ++ind){
                    if((*(ind)!='/'&&*(ind+1)=='/') || (*(ind)!='/' && *(ind+1)=='\0')){
                        res++;
                    }
                }
            }
            else{
                for(const char* ind=a; *(ind) !='\0'; ++ind){
                     if((*(ind)!='/'&&*(ind+1)=='/') || (*(ind)!='/' && *(ind+1)=='\0')){
                        res++;
                    }
                }
            }
            return res;
    }
    else{return -1000;}
}

//Longuer d'un mot avant le prochain /
int word_len(const char* w){
    assert(w!=NULL);
    int res=0;
    if(*w=='/'){
        for(const char* parc=w+1;*(parc)!='/';++parc){
                res++;
                if(*(parc+1)=='\0')break;
        }
    }
    else{
        for(const char* parc=w;*(parc)!='/';++parc){
                res++;
                if(*(parc+1)=='\0')break;
        }
    }
    return res;
}

//Extraire un mot à partir d'une position
char* extract_word(const char* str,int n){
    //assert(str != NULL);
    if(str==NULL){
        printf("Invalid dans extract word ligne 143");
        exit(1);
    }
    //printf("--> %s \n",str);
    if(verif(str)){
        if(*str!='/'){
            //printf("Extract word / \n");
            int x=word_len(str);
            char* res=malloc(sizeof(char)*x+1);
            assert(res!=NULL);
            memmove(res,str,sizeof(char)*x);
            *(res+x)='\0';
            return res;
        }
        else{
            //printf("Extract Normal \n");
            int x=word_len(str+1);
            char* res=malloc(sizeof(char)*x+1);
            assert(res!=NULL);
            memmove(res,str+1,sizeof(char)*x);
            *(res+x)='\0';
            return res;
        }
    }
    else{
        printf("Erreur dans le mot depuis extract Word");
        exit(1);
        return NULL;
    }   
}

//Chercher le prochain mot en fonnction de critère 
char* next_word(char* w){
    assert(w!=NULL);
    if(*w=='/'){
        //printf("Indirect Next Word \n");
        return w+1;
    }
    else{
        //printf("Direct Next Word \n");
        for(char* x=w;*x!='\0';++x){
            if(*x=='/'){
                return x+1;
            } 
        }
    }
    return NULL;
}

typedef struct{
    int nbr;
    char** words;
}w_index;

void free_index(w_index* pa){
    assert(pa!=NULL);
    for(int i=0; i<pa->nbr;++i){
        free(*(pa->words+i));
    }
    free(pa);
}
void print_index(w_index* pa){
    assert(pa!=NULL);
    printf("\n-Les Elements dans notre w_index: \n");
    for(int i=0;i<pa->nbr;++i){
        printf("  %d : %s \n ",i,pa->words[i]);
    }   
}
int size_words(w_index* pa){
    assert(pa!=NULL);
    int x=0;
    for(int i=0;i<pa->nbr;++i){
        x+=strlen(pa->words[i]);
    }
    return x;
}

w_index* cons_index(char* s){
    int valLen=nbr_words(s), x=0 , cons=0;
    w_index* res=malloc(sizeof(w_index));
    res->nbr=valLen;
    res->words=malloc(sizeof(char*)*valLen); 
    
    //printf("Debut de la creation \n");
    char* save=s;
    
    for(int i=0; i<valLen; ++i){
        save=extract_word(save,cons);
        //printf("Extract (Boucle) : %s \n",save);
        
        // Ne pas oublier le caractere \0
        x+=strlen(save);
        //printf("longueur de x : %d\n",x);
    
        int y=x;
        res->words[i]=malloc(sizeof(char)*strlen(save)+1);
        //Compléter chaque case
        for(int j=0; j<y; ++j){
            res->words[i][j]=save[j];
        }
        res->words[i][strlen(save)]='\0';
        //Voir le prochain mot
        save=next_word((s+x));
        //printf("Next Word (EndB) : %s \n",save);
    }
    return res;
}

//-------------------------------------------------------------------------------------------------

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
   else if(verif(name)){
    //Traiter le cas du RETOUR
    if(strcmp(name,"..")==0){
        //printf("\nRetour Direct \n");
        if(strcmp(n->pere->nom,"")!=0){
            //printf("Retour pere possible");
            n=n->pere;
        }
        return n;
    }
    else{
            //printf("-CD\n");
            // Verifier qu'il y a des fils à voir
            assert(n->fils!=NULL);
            noeud* tmp=n;
            noeud* tmp2=tmp;
            liste_noeud* list=n->fils;
            bool testList=false;
            w_index* chem=cons_index(name);
            //print_index(chem);
            for(int i=0;i<chem->nbr;++i){ // Boucle pour parcourir tous le chemin
                //Recherche du Deplacement 
                while(list->succ != NULL){
                    //Verifier que c'est bien un dossier
                    if(list->no->est_dossier==true){
                        if(strcmp(list->no->nom,chem->words[i])==0){
                            //printf("Dep dans cd %s && %s\n",list->no->nom,chem->words[i]);
                            tmp=list->no;
                            testList=true;
                            list=tmp->fils;
                            break;
                        }
                    }
                    list = list->succ;
                }
                //Verifier la derniere adresse si on n'a toujours pas trouve le chemin parmi les fils
                if(!testList){
                    if(tmp==tmp2 && strcmp(list->no->nom,chem->words[i])==0
                    && tmp->est_dossier==true){
                        //printf("Fin fini dans cd\n");
                        tmp=list->no;
                        tmp2=tmp;
                    }
                    else{
                        //printf("else de cd %s\n",list->no->nom);
                        //printf(" verif suivante %s \n",chem->words[i]);
                        //printf("Indice d'erreur dans cd %d\n ",i);
                        //printf("Il manque des fils dans le chemin !!!\n");
                        printf("cd : Il y a un problème dans le déplacement \n");
                        exit(1);
                    }
                }
                testList=false;
            }

            free_index(chem);

            //AFFECTATIONS DES ADRESSES n'a pas marché
            assert(tmp!=NULL);
            return tmp;
        }
   }
   else{
    printf("cd : Il y a une erreur dans le chemin qui est donné !! ");
    exit(1);
   }
}

//Faire une fonction auxiliaire pour le deplacement dans un fichier

// Affichage du chemin du noeud sur le temrinal 
char* pwd(noeud* n){ // Probleme de sens inverse à régler
    assert(n!=NULL);
    char* tmp=malloc(sizeof(char)*strlen(n->nom)+1);
    memmove(tmp,n->nom,sizeof(char)*strlen(n->nom));
    // Si on est directement placé au debut 
    
    if(strcmp(n->nom,n->racine->nom)==0){
        //printf("Retour direct pwd \n");
        return tmp;
    }
    //Sinon remonter jusqu'à la racine
    else{
        char* save=n->racine->nom;
        noeud* parc=n;
        
        while(strcmp(save,parc->nom)!=0){
            int x=strlen(parc->pere->nom);
            int y=strlen(tmp);

            tmp=realloc(tmp,y+x+1);
            strncat(tmp,"/",sizeof(char)*1);
            strncat(tmp,parc->pere->nom,sizeof(char)*x+sizeof(char));
            
            parc=parc->pere;
        }
        return tmp;
    }
    
    return tmp;
}

//Creation de Dossier
void mkdir(noeud* no,char* nom){
    assert(no!=NULL);
    assert(nom!=NULL);
    if(strlen(nom)>99 || strcmp(nom,"")==0){
        printf("Trop de caracterre dans le nom ou trop peu \n");
        return ;
    }
    if(no->est_dossier){
        if(no->fils==NULL){
            liste_noeud* list=malloc(sizeof(liste_noeud));
            noeud* li=malloc(sizeof(noeud));
            li->est_dossier=true;
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
                    printf("Il y a déjà ce nom de fichier dans la liste\n");
                    return ;
                }
                parc=parc->succ;
            }
            if(strcmp(parc->no->nom,nom)==0){
                    printf(" Il y a déjà ce nom de fichier dans la liste\n");
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
            li->pere=no;
            li->fils=NULL;
            suiv->no=li;
            
            //descriptionNoeud(li);
            parc->succ=suiv;
        }
    }
}

//Creation de fichier
void touch(noeud* no,char* nom){
    assert(nom !=NULL);
    if(strlen(nom)>99 || strcmp(nom,"")==0){
        printf("Trop de caracterre dans le nom ou trop peu \n");
        return ;
    }
    if(no->est_dossier){
        // Ajouter directement au debut 
        if(no->fils==NULL){
            //printf(" Parcour de TOUCH direct \n");
            liste_noeud* list=malloc(sizeof(liste_noeud));
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
                    printf("Il y a déjà ce nom de fichier dans la liste\n");
                    return ;
                }
                parc=parc->succ;
            }
            if(strcmp(parc->no->nom,nom)==0){
                    printf(" Il y a déjà ce nom de fichier dans la liste\n");
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
//Fonction auxiliaire pour print afin d'afficher le nombre de fils
int nbFils(noeud* n){
    int x=0;
    liste_noeud* parc=n->fils;
    while(parc!=NULL){
        x++;
        parc=parc->succ;
    }
    return x;
}

void print(noeud* n){ // IL y a un probleme quand on ne part pas de la racine
    if(n==NULL){
        return ;
    }
    noeud* parc=n;
    liste_noeud* save=n->fils;
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

// Suppression de dossier en fonction de chemin

//Fonction auxiliaire pour faire un deplacement 
noeud* deplacementCalculer(noeud* n, char* chem){
    assert(n!=NULL);
    assert(chem!=NULL);
    if(verif(chem)==false){
        printf(" deplacementCalculer : le chemin est faux \n");
        exit(1);
    }
    if(*chem =='/'){
        bool testList=false;
        w_index* constructionChemin=cons_index(chem);
        noeud* tmp=n;
        noeud* tmp2=tmp;
        liste_noeud* list=n->fils;
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
                    if(tmp==tmp2 && strcmp(list->no->nom,constructionChemin->words[i])==0
                    && tmp->est_dossier==true){
                        tmp=list->no;
                        tmp2=tmp;
                    }
                    else{
                        printf("deplacementCalculer : Il y a un problème dans le déplacement \n");
                        exit(1);
                    }
            }
            testList=false;
        }

        //AFFECTATIONS DES ADRESSES n'a pas marché
        assert(tmp!=NULL);
        return tmp;

        free_index(constructionChemin);
    }
    else{
        bool testList=false;
        w_index* constructionChemin=cons_index(chem);
        noeud* tmp=n;
        noeud* tmp2=tmp;
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
                    if(tmp==tmp2 && strcmp(list->no->nom,constructionChemin->words[i])==0
                    && tmp->est_dossier==true){
                        tmp=list->no;
                        tmp2=tmp;
                    }
                    else{
                        printf("deplacementCalculer : Il y a un problème dans le déplacement \n");
                        exit(1);
                    }
            }
            testList=false;
        }

        //AFFECTATIONS DES ADRESSES n'a pas marché
        assert(tmp!=NULL);
        return tmp;
        free_index(constructionChemin);
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
            printf("verificationPresenceFils : Verification par le fils présent directement\n");
            printf("%s , %s \n", parc->no->nom, n->nom);
            return true;
        }
        if(parc->no->est_dossier){
            if(parc->no->fils!=NULL){
                res=verification_PresenceFils(n,parc->no->fils);
                if(res){
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
        printf("Chemin_existe :  Le chemin est vide \n");
        return false;
    }

    if(strcmp(chem,"..")!=0 || strcmp(chem,"")!=0){
            printf("Chemin_existe : Le chemin de suppression respecte les normes \n");
    }
    else{
            printf("Chemin_existe : Le chemin de suppression est incohérant \n");
            return false;
    }

    // Parcour d'un chemin absolu
    if(*chem=='/'){ // verifier tous les fils que notre noeud courant n'est pas dans le chemin
        w_index* index=cons_index(chem);
        //printf("Creation Index réussi\n");
        liste_noeud* parc=n->racine->fils;
        print_index(index);
        for(int i=1;i<index->nbr;++i){
            assert(parc!=NULL);
            //verifier le dossier
            while(parc->succ!=NULL){
                //printf("/ chem_existe parcour : %s\n",parc->no->nom);
                if(parc->no->est_dossier==true){
                    //printf("Dossier\n");
                    if(strcmp(parc->no->nom,index->words[i])==0){
                        if((i+1)>=index->nbr){
                            //printf("Fin de parcour\n");
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
                printf("Chemin_existe / : Il y a un problème dans le déplacement du chemin \n");
                printf(" %s : parc->no->nom \n",parc->no->nom);
                printf("%s : index->words[i] \n",index->words[i]);
                return false;
            }
        }
        free_index(index);
        //Verifier tous les fils qu'on ne se trouve pas sur ce chemin
    }
    else{
        w_index* index=cons_index(chem);
        //printf("Creation Index réussi\n");
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
                printf("Chemin_existe : Il y a un problème dans le déplacement du chemin \n");
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
            printf("suppression : un seul élément \n");
            free(n);
        } 
        else{
            printf("suppression: plusieurs élément \n");
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
    printf("liberation_noeud: racine \n");
    
    noeud* pred=NULL;
    noeud* parc=n->racine;
    
    liste_noeud* list=parc->fils;
    liste_noeud* li_Pred=NULL;

    for(int i=1;i<index_Chem->nbr;++i){
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
            printf("Liberation noeud (if->else): il y a une erreur \n");
            exit(1);
        }
    }

    printf("\nLibération noeud : description du noeud à supprimer \n");
    printf("->courant: %s \n",parc->nom);
    if(pred!=NULL )printf("->pred : %s \n",pred->nom);
    if(list!=NULL ) printf("Liste courante : %s \n", list->no->nom);
    if(li_Pred!=NULL) printf("LIste pred : %s \n" ,li_Pred->no->nom);


    // Maintenant on peut supprimer tous les fils
    suppression(pred,parc);
   
   }
   else{
    printf("Libération noeud : courant \n");
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
            printf("Liberation noeud (else->else): il y a une erreur \n");
            exit(1);
        }
    }

    printf("Libération noeud : description du noeud à supprimer \n");
    printf("%s\n",parc->nom);
    if(pred!=NULL )printf("->pred : %s \n",pred->nom);
    if(list!=NULL ) printf("Liste courante : %s \n", list->no->nom);
    if(li_Pred!=NULL) printf("LIste pred : %s \n" ,li_Pred->no->nom);

    // Maintenant on peut supprimer tous les fils
    suppression(pred,parc);
   }
}

void rm(noeud* n,char* chem){
    // La manière dont j'ai imaginé est de verifier en premier la cohérence du chemin 
    // Ensuite on va vérifier que c'est un chemin ou notre noeud n'est pas situé 

    if(chemin_existe(n,chem)==1){
        printf("rm: Le chemin que l'on a donné est correct ");
        //On va maintenant se déplacer vers ce chemin via un cd 
        noeud* dep=deplacementCalculer(n,chem);
        assert(dep!=NULL);

        printf(" rm : Description du noeud à supprimer \n");
        print(dep);

        //On va maintenant vérifier si le noeud courant est dans ce chemin
        if(verification_PresenceFils(n,dep->fils)==0){
            printf("rm: Ce chemin n'est pas sur le noeud courant où on est situé \n");
            
            //Utiliser une fonction auxiliaire de libération de la mémoire
            // On pourra alors libérer la profondeur si on n'est pas situé sur le noeud courant
            printf("rm : liberation des noeuds\n");
            liberation_noeud(n,chem);
        }
        else{
            printf("rm: Ce chemin est sur le noeud courant on ne peut pas le supprimer \n");
        }
    }
    else{
        printf("rm: Ce chemin est incorrect \n");
    }
}

//Copie de chemin dans un dossier
void cp(noeud* n,char* chem1,char* chem2){
    //Faire les vérifications nécessaire pour éviter de copier dans le noeud ou on est situé
    if(chemin_existe(n,chem1)){
        printf("Le chemin que l'on a donné est correct \n");
        noeud* dep=cd(n,chem1);
        noeud* cop=cd(n,chem2);
        
        // Vérifier la présence des fils dans le chemin
        if(verification_PresenceFils(dep,cop->fils)){
            printf("Ce chemin est cohérant \n");
            // On peut alors utiliser notre fonction auxiliaire d'ajout
            // on va donc prendre les fils ou on doit copier et ensuite ajouter le noeud à copier
            ajoutL(dep->fils,cop);
        }
    }
}

//Faire des déplacements pour des suppressions

void mv(noeud* n,char* chem1,char* chem2){
    // Pour bien faire mv il faut etre sur que cp et rm fonctionne bien
}

int main(){
    //Test Formation correct ou non
    /*
    char* test1="/t/ QJSQKLH/QSKH/JHSK"; // Faux
    char* test2="/kjh//d"; //Faux
    char* test3=".."; //Vrai
    char* test7="sdlkfj/lsdkh/zei/qoei";//Vrai
    char* test8="/qsjd/jkfh/zoiey/jdk/d";//Vrai
    char* test4="/d/lkdh/sdj/";//Faux
    char* test5="lskh/lksjd/iory/;/ksl";//Faux
    char* test6=".";//Faux  
    printf("-- Test1 %d\n",verif(test1));
    printf("-- Test2 %d\n",verif(test2));
    printf("-- Test3 %d\n",verif(test3));
    printf("-- Test4 %d\n",verif(test4));
    printf("-- Test5 %d\n",verif(test5));
    printf("-- Test6 %d\n",verif(test6));
    printf("-- Test7 %d\n",verif(test7));
    printf("-- Test8 %d\n",verif(test8));
    */

    //Test du nombre de mot
    /*
    char* testVrai="/ldkf/ki/mldjf/kjdh/oeir";
    char* testVrai2="ldkghtf/ki/mldjf/kji";
    printf("Nombre de mot test1 : %d \n",nbr_words(testVrai));
    printf("Nombre de mot test2 : %d \n",nbr_words(testVrai2));

    //Test longuer d'un mot dans notre cas
    printf("Nombre de mot à la premiere adresse testVrai: %d\n",word_len(testVrai));
    printf("Nombre de mot à la  première adresse testVrai2: %d\n",word_len(testVrai2));
    
    //Test de la creation d'un index pour des caractères donné
    //w_index* resultat=cons_index("td/tp/anglais/bien");
    w_index* resultat2=cons_index("/td/tp/anglais/bien");
    //print_index(resultat);
    print_index(resultat2);
    */
    
    
    //On peut définir un noeud de type global pour verifier la position courante
    noeud* positionCourante=malloc(sizeof(noeud));

    printf("Creation noeud a1\n");
    noeud a1;
    
    //Creation Noeud a2
    printf("Creation Noeud a2\n");
    noeud a2;
    a2.est_dossier=true;
    char* a21="Cours";
    memmove(a2.nom,a21,sizeof(char)*6);
    a2.pere=&a1;
    a2.racine=&a1;
    
    //Creation du noeud a5
    printf("Creation Noeud a5\n");
    noeud a5;
    a5.est_dossier=true;
    char* a51="ProjetC";
    memmove(a5.nom,a51,sizeof(char)*8);
    a5.pere=&a2;
    a5.racine=&a1;
    a5.fils=NULL;
    
    //Creation du noeud a6
    printf("Creation Noeud a6\n");
    noeud a6;
    a6.est_dossier=true;
    char* c="Anglais";
    memmove(a6.nom,c,sizeof(char)*8);
    a6.pere=&a2;
    a6.racine=&a1;
    a6.fils=NULL;

    printf("Creation liste A2 \n");
    liste_noeud filsA2;
    filsA2.no=&a5;
    filsA2.succ=NULL;
    printf("Ajout des fils de A2\n");
    a2.fils=&filsA2;

    //Ajout dans notre liste  avec la fonction auxiliaire
    ajoutL(&filsA2,&a6);
    
    //----Premier test de ls
    liste_noeud filsA1;
    filsA1.no=&a2;
    filsA1.succ=NULL;
    a1.est_dossier=true;
    char* a="~";
    memmove(a1.nom,a,sizeof(char)*2);
    a1.pere=&a1;
    a1.racine=&a1;
    a1.fils=&filsA1;

    positionCourante=&a1;
    //ls(positionCourante);

    printf("\n");
    descriptionNoeud(positionCourante);
    //descriptionNoeud(&a2);
    //descriptionNoeud(&a5);
    //descriptionNoeud(&a6);
        
    positionCourante=cd(positionCourante,"Cours");
    assert(positionCourante!=NULL);
    ls(positionCourante);
    descriptionNoeud(positionCourante);

    positionCourante=cd(positionCourante,"ProjetC");
    assert(positionCourante!=NULL);
    ls(positionCourante);
    
    
    positionCourante=cd(positionCourante,"");
    assert(positionCourante!=NULL);
    descriptionNoeud(positionCourante);
    ls(positionCourante);
    //descriptionNoeud(positionCourante);
    
    printf("\nCreation de fichier avec TOUCH\n");
    touch(positionCourante,"edt");
    
    printf("\nCreation de dossier avec MKDIR\n");
    mkdir(positionCourante,"Dossier");
    
    assert(positionCourante!=NULL);
    ls(positionCourante);
    
    positionCourante=cd(positionCourante,"Dossier");
    ls(positionCourante);

    positionCourante=cd(positionCourante,"..");
    descriptionNoeud(positionCourante);
    
    positionCourante=cd(positionCourante,"Cours/ProjetC");
    descriptionNoeud(positionCourante); 

    //IL faut faire une fonction qui inverse les trucs    
    char* testPWD = pwd(positionCourante);
    //assert(testPWD!=NULL);
    
    printf("\n pwd : %s ",testPWD);

    positionCourante=cd(positionCourante,"");
    printf(" retour :  %s ",pwd(positionCourante));
    
    touch(positionCourante,"FichierA");
    ls(positionCourante);

    //Test de la fonction de recherche des trucs
    print(positionCourante);

    //Test de notre fonction auxiliaire
    noeud* positionTest=positionCourante->fils->no;
    if(verification_PresenceFils(positionTest, positionCourante->fils)){
        printf("Verification true \n\n");
    }
    else{
        printf("Verification false \n\n");
    }

    //------Fonction auxiliaire pour vérifier que le chemin que l'on donne est correct
    
    //bool test1=chemin_existe(positionTest,"");//false
    //bool test2= chemin_existe(positionTest,"..");//false
    //bool test3= chemin_existe(positionTest,"/~/Cours");//true
    //bool test4= chemin_existe(positionTest,"/~/Dossier");//true
    //bool test5= chemin_existe(positionTest,"Cours/Chemin");//false
    
    //if(test1==0){ printf("Test1 réussi\n");}else{printf("Test1 echoué\n");}
    //if(test2==0){printf("Test2 réussi\n");}else{printf("Test2 echoué\n");}
    //if(test3==1){printf("Test3 réussi\n");}else{printf("Test3 echoué\n");}
    //if(test4==1){printf("Test4 réussi\n");}else{printf("Test4 echoué\n");}
    //if(test5==0){printf("Test5 réussi\n");}else{printf("Test5 echoué\n");}
    
    //Test de notre fonction rm
    rm(positionCourante,"FichierA");
    rm(positionCourante,"/~/Dossier");
    print(positionCourante);

    mkdir(positionCourante,"Dossier2");
    touch(positionCourante,"Fichier2");

    print(positionCourante);

    positionCourante=cd(positionCourante,"Dossier2");
    mkdir(positionCourante,"Dossier3");
    printf("-----------------------------------------------\n");
    mkdir(positionCourante,"FichierCopi");
    mkdir(positionCourante,"Dossier4");

    cp(positionCourante,"FichierCopi","Dossier4");
    print(positionCourante);

}

