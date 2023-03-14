#include "player.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Player create(void){
    Player p;
    strcpy(p.name, "Unknown");
    p.level = 1;
    return p;
}
 void say(Player p, char *message ){
    printf("%s , %s " , p.name, message);
 }