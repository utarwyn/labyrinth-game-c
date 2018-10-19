
#include "labyrinthe.h"

typedef struct {

    int ligne;
    int colonne;
    char nom[50];

} joueur ;

void preparer_joueur (joueur * joueur, labyrinthe laby);

void deplacer_joueur (joueur * joueur, labyrinthe laby, char direction);

int joueur_est_arrive (joueur joueur, labyrinthe laby);
