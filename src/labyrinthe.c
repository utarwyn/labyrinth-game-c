#include "labyrinthe.h"

void creer_structure_labyrinthe (labyrinthe laby) {
    int lig;
    int col;
    int nombre_case;

    nombre_case = 1;

    for (lig = 0; lig < laby.hauteur; lig++) {
        for (col = 0; col < laby.largeur; col++) {
            if (col == 0 || lig == 0 || lig == laby.hauteur - 1 || col == laby.largeur - 1 || lig % 2 == 0 || col % 2 == 0) {
                laby.tableau[lig][col] = MUR;
            } else {
                laby.tableau[lig][col] = nombre_case++;
            }
        }
    }
}

void generer_labyrinthe_aleatoire (labyrinthe laby) {
    int iteration;
    int ligne;
    int colonne;
    int case1;
    int case2;
    int vertical;
    int ** tableau;

    iteration = 0;
    tableau = laby.tableau;

    while (iteration < ((laby.largeur / 2) * (laby.hauteur / 2)) - 1) {
        ligne = nombre_aleatoire(1, laby.hauteur - 2);
        colonne = nombre_aleatoire(1, laby.largeur - 2);
        vertical = colonne % 2;

        if (tableau[ligne][colonne] == MUR) {
            /* Dans le cas où le mur pointé est dans une colonne impaire,
               on considère qu'il doit opérer en vertical.
               Cela signifie que l'on doit séléctionner les cases en haut
               et en bas de ce dernier. */
            if (vertical) {
                case1 = tableau[ligne - 1][colonne];
                case2 = tableau[ligne + 1][colonne];
            } else {
                case1 = tableau[ligne][colonne - 1];
                case2 = tableau[ligne][colonne + 1];
            }

            // Les deux cases doivent être libres, mais dans des sections différentes.
            if (case1 != MUR && case2 != MUR && case1 != case2) {
                if (vertical) {
                    tableau[ligne][colonne] = tableau[ligne + 1][colonne];
                    remplacer_valeur_recursif(tableau, ligne - 1, colonne, tableau[ligne - 1][colonne], tableau[ligne + 1][colonne]);
                } else {
                    tableau[ligne][colonne] = tableau[ligne][colonne + 1];
                    remplacer_valeur_recursif(tableau, ligne, colonne - 1, tableau[ligne][colonne - 1], tableau[ligne][colonne + 1]);
                }

                iteration++;
            }
        }
    }

    // Création de l'entrée et de la sortie du labyrinthe
    tableau[1][0] = JOUEUR;
    tableau[laby.hauteur - 2][laby.largeur - 1] = 0;
}

void remplacer_valeur_recursif (int ** tableau, int ligne, int colonne, int valeur, int valeur_a_remplacer) {
    tableau[ligne][colonne] = valeur_a_remplacer;

    if (tableau[ligne - 1][colonne] == valeur) {
        remplacer_valeur_recursif(tableau, ligne - 1, colonne, valeur, valeur_a_remplacer);
    }
    if (tableau[ligne + 1][colonne] == valeur) {
        remplacer_valeur_recursif(tableau, ligne + 1, colonne, valeur, valeur_a_remplacer);
    }
    if (tableau[ligne][colonne - 1] == valeur) {
        remplacer_valeur_recursif(tableau, ligne, colonne - 1, valeur, valeur_a_remplacer);
    }
    if (tableau[ligne][colonne + 1] == valeur) {
        remplacer_valeur_recursif(tableau, ligne, colonne + 1, valeur, valeur_a_remplacer);
    }
}

void sauvegarder_labyrinthe (labyrinthe laby) {
    // Si le dossier qui doit contenir les labyrinthes n'existe pas, on le créé.
    if (opendir(CHEMIN_LABYS) == NULL) {
        assert(mkdir(CHEMIN_LABYS, 0700) == 0);
    }

    FILE *fichier;
    fichier = fopen(concatener(CHEMIN_LABYS, concatener(laby.nom, ".cfg")), "wb");

    // Ecriture de la largeur et de la hauteur du labyrinthe
    fwrite(&laby.largeur, sizeof(int), 1, fichier);
    fwrite(&laby.hauteur, sizeof(int), 1, fichier);

    // Ecriture des cases du labyrinthe dans le fichier
    int lig, col;
    char element;

    for (lig = 0; lig < laby.hauteur; lig++) {
        for (col = 0; col < laby.largeur; col++) {
            element = laby.tableau[lig][col];

            /* Si l'élément est une case vide avec une valeur, on la met à zéro
               pour éviter les dépassements de type (ici char).                */
            if (element != MUR && element != JOUEUR) {
                element = 0;
            }

            fwrite(&element, sizeof(char), 1, fichier);
        }
    }


    fclose(fichier);
}

labyrinthe charger_labyrinthe (char * nom) {
    labyrinthe laby;

    FILE *fichier;
    fichier = fopen(concatener(CHEMIN_LABYS, concatener(nom, ".cfg")), "rb");

    if (fichier == NULL) {
        laby.largeur = 0;
        laby.hauteur = 0;

        return laby;
    }

    fread(&laby.largeur, sizeof(int), 1, fichier);
    fread(&laby.hauteur, sizeof(int), 1, fichier);

    int lig, col;
    char element;

    laby.tableau = creer_tableau_2d(laby.largeur, laby.hauteur);

    for (lig = 0; lig < laby.hauteur; lig++) {
        for (col = 0; col < laby.largeur; col++) {
            fread(&element, sizeof(char), 1, fichier);
            laby.tableau[lig][col] = element;
        }
    }

    fclose(fichier);
    return laby;
}

void afficher_labyrinthe (labyrinthe laby) {
    int lig;
    int col;
    char c;

    printf("\n");

    for (lig = 0; lig < laby.hauteur; lig++) {
        for (col = 0; col < laby.largeur; col++) {
            switch (laby.tableau[lig][col]) {
                case MUR:
                    c = '#';
                    break;
                case JOUEUR:
                    c = 'o';
                    break;
                default:
                    if (!DEBUG_CASES) {
                        c = ' ';
                    } else {
                        c = (laby.tableau[lig][col] - 1 + 'A');                        
                    }
                    break;
            }

            printf("%c ", c);
        }

        printf("\n");
    }

    printf("\n");
}
