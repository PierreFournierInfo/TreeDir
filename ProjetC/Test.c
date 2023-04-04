#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include "gestiontexte.h"
#include "fonctionauxiliaire.h"
#include "fonctionprincipale.h"


int main(){
    printf(" Test \n");
    noeud* positionCourante = creationDebut();
    descriptionNoeud(positionCourante);

    mkdir(positionCourante,"Cours");
    descriptionNoeud(positionCourante);

    positionCourante = cd(positionCourante,"Cours");
    descriptionNoeud(positionCourante);
    
    mkdir(positionCourante,"Anglais");
    mkdir(positionCourante,"Maths");
    mkdir(positionCourante,"Physique");
    touch(positionCourante,"Fichier1");
    ls(positionCourante);

    positionCourante = cd(positionCourante,"");
    //positionCourante = cd(positionCourante,"Fichier1"); Test reussi
    print(positionCourante);

    positionCourante = cd(positionCourante,"Cours/Anglais");
    descriptionNoeud(positionCourante);
    
    touch(positionCourante,"edt");
    ls(positionCourante);
    descriptionNoeud(positionCourante);
    
    positionCourante = cd(positionCourante,"");
    descriptionNoeud(positionCourante);
    
    print(positionCourante);
    
    ls(positionCourante);
    mkdir(positionCourante,"Video");
    mkdir(positionCourante,"Photo");
    ls(positionCourante);
    rm(positionCourante,"Video");
    //ls(positionCourante);

    printf("\n *** FIN *** \n");
}

