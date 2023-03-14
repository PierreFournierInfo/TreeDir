#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int  main(){

    printf(" Exemple Simple \n ");
    Player test = create();
    strcpy(test.name, "Jack");
    say(test," Je suis la creation");
    return 0;
}