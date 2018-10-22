
#include "joueur.h"

#define CLASSEMENT_NOMBRE 10

typedef struct {

    labyrinthe laby;
    int nombre;
    joueur meilleurs[CLASSEMENT_NOMBRE];

} classement ;

void afficher_classement (classement classement);

int recuperer_place_joueur (classement classement, joueur joueur);

void nouveau_joueur_classement (classement * classement, joueur joueur);

int comparer_joueur_classement(void const *a, void const *b);

classement charger_classement (labyrinthe laby);

void initialiser_classement (classement * classement);

void sauvegarder_classement (classement classement);