#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>

#include "joueur.h"
#include "main.h"
#include "utils.h"

labyrinthe laby;

int main () {
    int choix;

    do {
        printf("\n############### LABY ###############\n");
        printf("#                                  #\n");
        printf("#   [1] Créer un labyrinthe        #\n");
        printf("#   [2] Charger un labyrinthe      #\n");
        printf("#   [3] Jouer                      #\n");
        printf("#   [4] Quitter                    #\n");
        printf("#                                  #\n");
        printf("####################################");

        printf("\n  Action: ");

        choix = 0;
        scanf("%d", &choix);
        getchar();

        printf("\n");

        executer_action_menu(choix);
    } while (choix != 4);

    return 0;
}

void executer_action_menu (int choix) {
    switch (choix) {
        case 1:
            laby = creer_labyrinthe();
            break;
        case 2:
            laby = charger_fichier_labyrinthe();
            break;
        case 3:
            jouer_labyrinthe();
            break;
    }
}

labyrinthe creer_labyrinthe () {
    labyrinthe laby;

    printf("  nom : ");
    scanf("%s", laby.nom);
    printf("  largeur (impair, > 3) : ");
    scanf("%d", &laby.largeur);
    printf("  hauteur (impair, > 3) : ");
    scanf("%d", &laby.hauteur);

    if (laby.largeur > 3 && laby.largeur % 2 == 1) {
        if (laby.hauteur > 3 && laby.hauteur % 2 == 1) {
            laby.tableau = creer_tableau_2d(laby.largeur, laby.hauteur);
    
            creer_structure_labyrinthe(laby);
            generer_labyrinthe_aleatoire(laby);
            sauvegarder_labyrinthe(laby);

            printf("\n  > Labyrinthe généré avec succès dans %s.cfg\n", laby.nom);
            
            return laby;
        } else {
            laby.hauteur = 0;
            printf("  > Vous devez sélectionner une hauteur impaire plus grande que 3.\n");
        }
    } else {
        laby.largeur = 0;
        printf("  > Vous devez sélectionner une largeur impaire plus grande que 3.\n");
    }

    return laby;
}

labyrinthe charger_fichier_labyrinthe () {
    labyrinthe laby;
    char * nom;

    DIR *d;
    struct dirent *dir;
    d = opendir(CHEMIN_LABYS);

    if (d) {
        printf("  Labyinthes disponibles :\n");
        
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                printf("    - %s\n", dir->d_name);
            }
        }

        closedir(d);

        printf("\n  labyrinthe à ouvrir :\n    ");
        scanf("%ms", &nom);
        printf("\n");

        laby = charger_labyrinthe(nom);

        if (laby.largeur > 0) {
            printf("  > Labyrinthe %s.cfg chargé avec succès !\n", nom);
        } else {
            printf("  > Impossible de charger le labyrinthe %s.cfg !\n", nom);
        }
    } else {
        printf("  > Aucun labyrinthe déjà enregistré.\n");
    }

    return laby;
}

void jouer_labyrinthe () {
    if (laby.largeur > 0) {
        
        joueur joueur;

        preparer_joueur(&joueur, laby);

        do {

            afficher_labyrinthe(laby);

            char dir;
            scanf(" %c", &dir);

            deplacer_joueur(&joueur, laby, dir);

        } while (joueur_est_arrive(joueur, laby) != 1);

    } else {
        printf("   > Aucun labyrinthe n'a été chargé. Annulation.\n");
    }
}