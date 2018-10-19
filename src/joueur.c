#include "joueur.h"

void preparer_joueur (joueur * joueur, labyrinthe laby) {
    if (joueur_est_arrive(*joueur, laby)) {
        inverser(&laby.tableau[joueur->ligne][joueur->colonne], &laby.tableau[DEPART_LIG][DEPART_COL]);
    }

    joueur->ligne = DEPART_LIG;
    joueur->colonne = DEPART_COL;
}

void deplacer_joueur (joueur * joueur, labyrinthe laby, char direction) {
    int ligne = joueur->ligne;
    int colonne = joueur->colonne;

    switch (direction) {
        case 'q':
            if (colonne > 0 && laby.tableau[ligne][colonne - 1] != MUR) {
                inverser(&laby.tableau[ligne][colonne], &laby.tableau[ligne][colonne - 1]);
                joueur->colonne--;
            }
            break;
        case 'z':
            if (laby.tableau[ligne - 1][colonne] != MUR) {
                inverser(&laby.tableau[ligne][colonne], &laby.tableau[ligne - 1][colonne]);
                joueur->ligne--;
            }
            break;
        case 'd':
            if (colonne < laby.largeur - 1 && laby.tableau[ligne][colonne + 1] != MUR) {
                inverser(&laby.tableau[ligne][colonne], &laby.tableau[ligne][colonne + 1]);
                joueur->colonne++;
            }
            break;
        case 's':
            if (laby.tableau[ligne + 1][colonne] != MUR) {
                inverser(&laby.tableau[ligne][colonne], &laby.tableau[ligne + 1][colonne]);
                joueur->ligne++;
            }
            break;
    }
}

int joueur_est_arrive (joueur joueur, labyrinthe laby) {
    return joueur.ligne == laby.hauteur + ARRIVEE_LIG && joueur.colonne == laby.largeur + ARRIVEE_COL;
}
