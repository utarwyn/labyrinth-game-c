#include "classement.h"

void afficher_classement (classement cls) {
    int i;
    joueur joueur;

    if (cls.nombre > 0) {
        printf("+------------+-------+\n");
        printf("| Joueur     | Score |\n");
        printf("+------------+-------+\n");

        for (i = 0; i < cls.nombre; i++) {
            joueur = cls.meilleurs[i];

            printf("| %-10s | %5d |\n", joueur.nom, joueur.score);
        }

        printf("+------------+-------+\n");
    }
}

int recuperer_place_joueur (classement cls, joueur joueur) {
    int place;
    int i;

    place = cls.nombre;

    for (i = 0; i < cls.nombre && place == cls.nombre; i++) {
        if (cls.meilleurs[i].score >= joueur.score) {
            place = i;
        }
    }

    /* Le joueur est trop loin dans le classement pour être enregistré */
    if (place == 10) {
        place = -1;
    }

    return place;
}

void definir_place_joueur (classement * classement, joueur joueur_, int place) {
    int i;

    for (i = classement->nombre - 1; i > place; i--) {
        classement->meilleurs[i] = classement->meilleurs[i - 1];
    }

    classement->meilleurs[place] = joueur_;

    if (classement->nombre < 10) {
        classement->nombre++;
    }
}

classement charger_classement (labyrinthe laby) {
    classement cls;
    cls.laby = laby;

    FILE *fichier;
    fichier = fopen(concatener(CHEMIN_LABYS, concatener(laby.nom, ".score")), "rb");

    if (fichier != NULL) {
        fread(&cls.nombre, sizeof(cls.nombre), 1, fichier);
        fread(&cls.meilleurs, sizeof(joueur), 10, fichier);
        fclose(fichier);
    } else {
        cls.nombre = 0;
    }

    return cls; 
}

void sauvegarder_classement (classement cls) {
    FILE *fichier;
    fichier = fopen(concatener(CHEMIN_LABYS, concatener(cls.laby.nom, ".score")), "wb");

    fwrite(&cls.nombre, sizeof(cls.nombre), 1, fichier);
    fwrite(&cls.meilleurs, sizeof(joueur), 10, fichier);

    fclose(fichier);
}