#include "classement.h"

typedef struct {

    int ligne;
    int colonne;
    char type;

    void (* deplacer)();
    int (* penalite)();

} monstre ;

monstre * initialiser_monstres (labyrinthe * laby);

void deplacer_monstres (monstre * monstres, labyrinthe laby);

void deplacer_archer (monstre * monstre, labyrinthe laby);

void deplacer_fantome (monstre * monstre, labyrinthe laby);

int tester_penalites (monstre * monstres, labyrinthe laby, joueur * joueur);

int penalite_archer (monstre monstre, joueur * joueur);

int penalite_fantome (monstre monstre, joueur * joueur);
