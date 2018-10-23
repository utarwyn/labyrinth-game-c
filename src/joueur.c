#include "joueur.h"

void preparer_joueur (joueur * joueur, labyrinthe laby) {
    if (laby.tableau[laby.hauteur + ARRIVEE_LIG][laby.largeur + ARRIVEE_COL] == JOUEUR) {
        inverser(&laby.tableau[ARRIVEE_LIG][ARRIVEE_COL], &laby.tableau[DEPART_LIG][DEPART_COL]);
    }

    joueur->ligne = DEPART_LIG;
    joueur->colonne = DEPART_COL;
    joueur->score = 0;
}

void deplacer_joueur (joueur * joueur, labyrinthe laby, char direction) {
    char dep_lig;
    char dep_col;

    switch (direction) {
        case 'q': dep_col = -1; break;
        case 'z': dep_lig = -1; break;
        case 'd': dep_col =  1; break;
        case 's': dep_lig =  1; break;
    }

    if ((dep_lig != 0 || dep_col != 0) && joueur->colonne + dep_col >= 0) {
        int * case_courante = &laby.tableau[joueur->ligne][joueur->colonne];
        int * case_dest = &laby.tableau[joueur->ligne + dep_lig][joueur->colonne + dep_col];

        if (*case_dest != MUR) {
            if (*case_dest == TRESOR) {
                joueur->score += SCORE_TRESOR;
                *case_dest = 0;
            } else if (*case_dest == PIEGE) {
                joueur->score += SCORE_PIEGE;
                *case_dest = 0;
            }

            /* TODO: mettre la case courante vide et la case de destination en joueur. */
            inverser(case_courante, case_dest);

            joueur->score += SCORE_DEPLACEMENT;
            joueur->colonne += dep_col;
            joueur->ligne += dep_lig;
        }
    }
}

int joueur_est_arrive (joueur joueur, labyrinthe laby) {
    return joueur.ligne == laby.hauteur + ARRIVEE_LIG && joueur.colonne == laby.largeur + ARRIVEE_COL;
}
