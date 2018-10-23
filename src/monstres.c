#include "monstres.h"

monstre * initialiser_monstres (labyrinthe * laby) {
    monstre * monstres;
    int nb_cases_vides = ((laby->largeur - 1) * (laby->hauteur -1)) / 2 - 1;

    int nb_archers = nb_cases_vides * CHANCE_ARCHER;
    int nb_fantomes = nb_cases_vides * CHANCE_FANTOME;
    int ligne, colonne;
    int i;
    
    laby->nb_monstres = nb_fantomes + nb_archers;
    monstres = calloc(laby->nb_monstres, sizeof(monstre));
    i = 0;

    while (i < laby->nb_monstres) {
        ligne = nombre_aleatoire(1, laby->hauteur - 2);
        colonne = nombre_aleatoire(1, laby->largeur - 2);

        if (laby->tableau[ligne][colonne] >= 0) { /* Est une case libre */
            if (nb_archers > 0) {
                laby->tableau[ligne][colonne] = ARCHER;
                monstres[i] = (monstre) { ligne, colonne, ARCHER, &deplacer_archer, &penalite_archer };
                nb_archers--;
            } else {
                laby->tableau[ligne][colonne] = FANTOME;
                monstres[i] = (monstre) { ligne, colonne, FANTOME, &deplacer_fantome, &penalite_fantome };
                nb_fantomes--;
            }

            i++;
        }
    }

    return monstres;
}

void deplacer_monstres (monstre * monstres, labyrinthe laby) {
    int i;

    for (i = 0; i < laby.nb_monstres; i++) {
        monstres[i].deplacer(&monstres[i], laby);
    }
}

void deplacer_archer (monstre * monstre, labyrinthe laby) {
    int nb_pas = nombre_aleatoire(1, 3);
    int i_pas = 0;
    int directions[4] = {1, 2, 3, 4};
    int i;
    int trouve;
    int * case_arrivee;

    int dest_ligne, dest_colonne;
    int dern_lig, dern_col;

    dern_lig = -1;
    dern_col = -1;

   for (i_pas = 0; i_pas < nb_pas; i_pas++) {
        shuffle(directions, 4);
        trouve = 0;

        for (i = 0; i < 4 && trouve == 0; i++) {
            dest_ligne = monstre->ligne;
            dest_colonne = monstre->colonne;

            switch (directions[i]) {
                case 1: dest_ligne--; break;
                case 2: dest_colonne++; break;
                case 3: dest_ligne++; break;
                case 4: dest_colonne--; break;
            }

            if (dest_ligne != dern_lig && dest_colonne != dern_col) {
                case_arrivee = &laby.tableau[dest_ligne][dest_colonne];

                if (*case_arrivee >= 0) {
                    inverser(&laby.tableau[monstre->ligne][monstre->colonne], case_arrivee);
                    monstre->ligne = dest_ligne;
                    monstre->colonne = dest_colonne;

                    dern_lig = dest_ligne;
                    dern_col = dest_colonne;
                    trouve = 1;
                }
            }
        }
    }
}

void deplacer_fantome (monstre * monstre, labyrinthe laby) {
    int direction = rand() % 4;
    int dep_lig = 0;
    int dep_col = 0;

    switch (direction) {
        case 0: dep_lig = -1; break;
        case 1: dep_col = 1; break;
        case 2: dep_lig = 1; break;
        case 3: dep_col = -1; break;
    }

    int dest_lig = monstre->ligne + dep_lig;
    int dest_col = monstre->colonne + dep_col;
    int stop = 0;

    do {
        if (dest_lig > 0 && dest_col > 0 && dest_lig < laby.hauteur - 1 && dest_col < laby.largeur - 1) {
            if (laby.tableau[dest_lig][dest_col] >= 0) {
                inverser(&laby.tableau[dest_lig][dest_col], &laby.tableau[monstre->ligne][monstre->colonne]);
                monstre->ligne = dest_lig;
                monstre->colonne = dest_col;

                stop = 1;
            } else {
                dest_lig += dep_lig;
                dest_col += dep_col;
            }
        } else {
            stop = 1;
        }
    } while (stop == 0);
}

int tester_penalites (monstre * monstres, labyrinthe laby, joueur * joueur) {
    int penalites = 0;
    int i;

    for (i = 0; i < laby.nb_monstres; i++) {
        penalites += monstres[i].penalite(monstres[i], laby, joueur);
    }

    return penalites;
}

int penalite_archer (monstre monstre, joueur * joueur) {
    /* TODO: compléxifier un peu le système pour que les murs bloquent les flèches de l'archer. */
    return monstre.ligne == joueur->ligne || monstre.colonne == joueur->colonne ? SCORE_ARCHER : 0;
}

int penalite_fantome (monstre monstre, joueur * joueur) {
    /* TODO: si la fantôme se situe juste à côté du joueur, on le pénalise */
    int diff_lig = monstre.ligne - joueur->ligne;
    int diff_col = monstre.colonne - joueur->colonne;

    return diff_lig >= -1 && diff_lig <= 1 && diff_col >= -1 && diff_col <= 1 ? SCORE_FANTOME : 0;
}
