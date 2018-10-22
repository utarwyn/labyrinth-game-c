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
    int cls_score;

    place = cls.nombre;

    /* Recherche de la possible place du joueur */
    for (i = 0; i < cls.nombre && place == cls.nombre; i++) {
        cls_score = cls.meilleurs[i].score;

        if (cls_score == 0 || cls_score > joueur.score) {
            place = i;
        }
    }

    /* Le joueur est trop loin dans le classement pour être enregistré */
    if (place == 10) {
        place = -1;
    }

    return place;
}

void nouveau_joueur_classement (classement * classement, joueur joueur) {
    /* On place d'abord le joueur en dernier du classement */
    classement->meilleurs[CLASSEMENT_NOMBRE - 1] = joueur;

    /* Et on trie le classement grâce à la méthode qsort */
    qsort(classement->meilleurs, CLASSEMENT_NOMBRE, sizeof(joueur), comparer_joueur_classement);

    if (classement->nombre < CLASSEMENT_NOMBRE) {
        classement->nombre++;
    }
}

int comparer_joueur_classement(void const *a, void const *b) {
    joueur const *ja = a;
    joueur const *jb = b;

    return ja->score == 0 ? 1 : (jb->score == 0 ? -1 : ja->score - jb->score);
}

void initialiser_classement (classement * cls) {
    int i;
    
    cls->nombre = 0;

    for (i = 0; i < CLASSEMENT_NOMBRE; i++) {
        strcpy(cls->meilleurs[i].nom, "");
        cls->meilleurs[i].score = 0;
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
        initialiser_classement(&cls);
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