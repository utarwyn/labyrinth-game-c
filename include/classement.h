
#include "joueur.h"

typedef struct {

    labyrinthe laby;
    int nombre;
    joueur meilleurs[10];

} classement ;

void afficher_classement (classement classement);

int recuperer_place_joueur (classement classement, joueur joueur);

void definir_place_joueur (classement * classement, joueur joueur, int place);

classement charger_classement (labyrinthe laby);

void sauvegarder_classement (classement classement);