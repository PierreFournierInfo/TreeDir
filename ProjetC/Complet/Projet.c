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

//On peut définir un noeud de type global pour verifier la position courante
noeud* positionCourante2;

// Creation de la racine
noeud* creationDebut(){
    noeud* n = malloc(sizeof(noeud));
    strcpy(n->nom,"");
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

//Fonction de description de noeud auxiliaire 
void descriptionNoeud(noeud* d){
    assert(d!=NULL);
    printf("-- DESCRIPTION DU NOEUD --\n");
    if(d->est_dossier){
        printf("Ce noeud est un dossier, ");
    }
    printf("Son nom est : %s et le nom de son pere est : %s\n",d->nom,d->pere->nom);
    printf("Le nom de sa racine est : %s \n",d->racine->nom);
    if(d->fils!=NULL){
        printf(" Il possède des fils\n");
        liste_noeud* list=d->fils;
        assert(list->no != NULL);
        printf("\n");
    }
}

//ls
void ls(noeud* n){
    assert(n!=NULL);
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
            return false;
        }
    }
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
    if(str==NULL){
        printf("Invalid dans extract word ligne 143");
        exit(1);
    }
    if(verif(str)){
        if(*str!='/'){
            int x=word_len(str);
            char* res=malloc(sizeof(char)*x+1);
            assert(res!=NULL);
            memmove(res,str,sizeof(char)*x);
            *(res+x)='\0';
            return res;
        }
        else{
            int x=word_len(str+1);
            char* res=malloc(sizeof(char)*x+1);
            assert(res!=NULL);
            memmove(res,str+1,sizeof(char)*x);
            *(res+x)='\0';
            return res;
        }
    }
    else{
        printf(" Erreur dans le mot depuis extract Word");
        exit(1);
        return NULL;
    }   
}

//Chercher le prochain mot en fonnction de critère 
char* next_word(char* w){
    assert(w!=NULL);
    if(*w=='/'){
        return w+1;
    }
    else{
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
   
    char* save=s; 
    for(int i=0; i<valLen; ++i){
        save=extract_word(save,cons);
        
        // Ne pas oublier le caractere \0
        x+=strlen(save);
      
        int y=x;
        res->words[i]=malloc(sizeof(char)*strlen(save)+1);
        //Compléter chaque case
        for(int j=0; j<y; ++j){
            res->words[i][j]=save[j];
        }
        res->words[i][strlen(save)]='\0';
      
        //Voir le prochain mot
        save=next_word((s+x));
    }
    return res;
}

//-------------------------------------------------------------------------------------------------
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
            noeud* tmpPere = malloc(sizeof(noeud));
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
            printf("Retour pere possible");
            n=n->pere;
        }
        return n;
    }
    else{
           return depCD(n,name);
        }
   }
   else{
    printf("cd : Il y a une erreur dans le chemin qui est donné !! ");
    exit(1);
   }
}

// Affichage du chemin du noeud sur le temrinal 
char* pwd(noeud* n){ // Probleme de sens inverse à régler
    assert(n!=NULL);
    if(!validiteNoeud(n)){ 
        printf(" pwd : Il y a des problèmes de liaisons ");
        exit(1);
    }
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
void* mkdir(noeud* no,char* nom){
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
            
            //descriptionNoeud(li);
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

void print(noeud* n){ // IL y a un probleme quand on ne part pas de la racine
    if(n==NULL){
        printf(" Le noeud à décrire est NULL \n");
        return ;
    }
    noeud* parc=n;
    assert(parc!=NULL);
    liste_noeud* save = n->fils;
    //assert(save!=NULL);
    /*if(save==NULL){
        printf(" La liste n'a pas d'élément \n");
        return ;
    }*/
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

//----------------------------------------------------------------------------------------------------------------------------------

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

void rm(noeud* n,char* chem){
    // La manière dont j'ai imaginé est de verifier en premier la cohérence du chemin 
    // Ensuite on va vérifier que c'est un chemin ou notre noeud n'est pas situé 

    if(chemin_existe(n,chem)==1){
        printf(" l 957 - rm: Le chemin que l'on a donné est correct ");
        //On va maintenant se déplacer vers ce chemin via un cd 
        noeud* dep=deplacementCalculer(n,chem);
        assert(dep!=NULL);

        printf(" l 962 -  rm : Description du noeud à supprimer \n");
        print(dep);

        //On va maintenant vérifier si le noeud courant n'est pas dans ce chemin
        if(verification_PresenceFils(n,dep->fils)==0){
            printf("l 967 - rm: Ce chemin n'est pas sur le noeud courant où on est situé \n");
            
            //Utiliser une fonction auxiliaire de libération de la mémoire
            // On pourra alors libérer la profondeur si on n'est pas situé sur le noeud courant
            printf("l 971 - rm : liberation des noeuds\n");
            liberation_noeud(n,chem);
        }
        else{
            printf("l 975 - rm: Ce chemin est sur le noeud courant on ne peut pas le supprimer \n");
            exit(1);
        }
    }
    else{
        printf(" l 980 - rm: Ce chemin est incorrect \n");
        exit(1);
    }
}

//------------------------------------------------------------------------------------------------------------------------------
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
            print(dep);
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
        print(save);
        printf(" Le noeud ou on va faire la copie \n");
        print(courant);
        
        assert(save!=NULL);
        //ajouter maintenant la copie du fichier ou du dossier
        ajoutL(courant,courant->fils,save);
        printf(" ----------------1 Affichage après la copie ----------------- \n");
        print(save);
        printf("-----------------------------------------------------------------\n");
        print(courant);

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
             print(courant);
             ajoutL(courant,courant->fils,save);
             printf(" ----------------2 Affichage après la copie ----------------- \n");
             print(courant);

             free_index(cheminParcour);
        }
        else{
            printf("l:1121 Bizarre ... \n");
             free_index(cheminParcour);
            exit(1);
        }
    }
}


//Copie de chemin dans un dossier
void cp(noeud* n,char* chem1,char* chem2){
    //Faire les vérifications nécessaire pour éviter de copier dans le noeud ou on est situé
    if(chemin_existe(n,chem1)==1){
        printf(" l 1139 - cp : Le chemin que l'on a donné est correct \n");
        noeud* dep=cpVerif1(n,chem1);
        assert(dep!=NULL);
        cpVerif2(dep,n,chem2);
    }
    else{
        printf(" l 1150 : Erreur de chemin dans cp \n");
        exit(1);
    }
}

//Faire des déplacements pour des suppressions

void mv(noeud* n,char* chem1,char* chem2){
    // Pour bien faire mv il faut etre sur que cp et rm fonctionne bien
}

int main(){
    printf(" Test \n");
    noeud* positionCourante = creationDebut();
    descriptionNoeud(positionCourante);

     mkdir(positionCourante,"Cours");
    descriptionNoeud(positionCourante);
    ls(positionCourante);

    positionCourante = cd(positionCourante,"Cours");
    descriptionNoeud(positionCourante);
    
    mkdir(positionCourante,"Anglais");
    ls(positionCourante);
    
    positionCourante = cd(positionCourante,"Anglais");
    descriptionNoeud(positionCourante);
    
    /*
    touch(positionCourante,"edt");
    ls(positionCourante);
    descriptionNoeud(positionCourante);
    
    positionCourante = cd(positionCourante,"");
    descriptionNoeud(positionCourante);
    */
    //print(positionCourante);

    printf("\n *** FIN *** \n");
    
}

