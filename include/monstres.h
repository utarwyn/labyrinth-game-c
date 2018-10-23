#include "classement.h"

typedef struct {

    int ligne;
    int colonne;
    char type;

    void (* deplacer)();
    void (* zone_deplacement)();

} monstre ;

monstre * initialiser_monstres (labyrinthe * laby);

void deplacer_monstres (monstre * monstres, labyrinthe laby);

void deplacer_archer (monstre * monstre, labyrinthe laby);

void deplacer_fantome (monstre * monstre, labyrinthe laby);

void zone_deplacement_archer (monstre monstre, labyrinthe laby);

void zone_deplacement_fantome (monstre monstre, labyrinthe laby);
