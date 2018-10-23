#include "main.h"

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
    printf("  difficulté (%d: facile, %d: difficile) : ", FACILE, DIFFICILE);
    scanf("%d", &laby.difficulte);

    if (laby.largeur > 3 && laby.largeur % 2 == 1) {
        if (laby.hauteur > 3 && laby.hauteur % 2 == 1) {
            if (laby.difficulte == FACILE || laby.difficulte == DIFFICILE) {
                laby.tableau = creer_tableau_2d(laby.largeur, laby.hauteur);
    
                creer_structure_labyrinthe(laby);
                generer_labyrinthe_aleatoire(laby);
                generer_bonus_malus(laby);

                if (laby.difficulte == DIFFICILE) {
                    rendre_difficile(laby);
                }

                sauvegarder_labyrinthe(laby);

                printf("\n  > Labyrinthe généré avec succès dans %s.cfg\n", laby.nom);
                
                return laby;
            } else {
                laby.hauteur = 0;
                printf("  > Vous devez choisir un niveau de difficulté valide.\n");
            }
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
    char nom[50];

    DIR *d;
    struct dirent *dir;
    d = opendir(CHEMIN_LABYS);

    if (d) {
        printf("  Labyinthes disponibles :\n");
        
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".cfg") != NULL) {
                printf("    - %s\n", dir->d_name);
            }
        }

        closedir(d);

        printf("\n  labyrinthe à ouvrir :\n    ");
        scanf("%s", nom);
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
        classement classement;
        monstre * monstres;

        preparer_joueur(&joueur, laby);
        monstres = initialiser_monstres(&laby);

        do {

            afficher_labyrinthe(laby);
            printf("score: %d\n", joueur.score);

            char dir;
            scanf(" %c", &dir);

            deplacer_joueur(&joueur, laby, dir);
            deplacer_monstres(monstres, laby);

            joueur.score += tester_penalites(monstres, laby, &joueur);

        } while (joueur_est_arrive(joueur, laby) != 1);

        afficher_labyrinthe(laby);

        /* Gestion des scores après la partie. */
        classement = charger_classement(laby);
        int place_joueur = recuperer_place_joueur(classement, joueur);

        if (place_joueur > -1) {
            char nom_joueur[50];
            printf("Bravo, vous êtes à la place %d avec %dpts !\n", place_joueur + 1, joueur.score);
            printf("Nom pour sauvegarder le score : ");
            
            /* On nettoie l'entrée de l'utilisateur pour éviter tout bug. */
            int c;
            while ( (c = getchar()) != '\n' && c != EOF ) { }

            scanf("%s", nom_joueur);
            strcpy(joueur.nom, nom_joueur);

            nouveau_joueur_classement(&classement, joueur);
            afficher_classement(classement);
            sauvegarder_classement(classement);
        } else {
            afficher_classement(classement);
            printf("Votre score: %d\n", joueur.score);
        }

        /* Rechargement du labyrinthe en cours */
        laby = charger_labyrinthe(laby.nom);

    } else {
        printf("   > Aucun labyrinthe n'a été chargé. Annulation.\n");
    }
}