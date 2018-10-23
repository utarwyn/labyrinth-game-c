#include "utils.h"

int ** creer_tableau_2d (int largeur, int hauteur) {
    int ** tableau;
    int ligne;
    int colonne;

    tableau = malloc(hauteur * sizeof(int *));

    for (ligne = 0; ligne < hauteur; ligne++) {
        tableau[ligne] = malloc(largeur * sizeof(int));

        for (colonne = 0; colonne < largeur; colonne++) {
            tableau[ligne][colonne] = -1;
        }
    }

    return tableau;
}

void liberer_tableau_2d (int ** tableau, int hauteur) {
    int ligne;

    for (ligne = 0; ligne < hauteur; ligne++) {
        free(tableau[ligne]);
    }

    free(tableau);
}

void inverser (int * valeur_1, int * valeur_2) {
    int temp;
    
    temp = *valeur_1;
    *valeur_1 = *valeur_2;
    *valeur_2 = temp;
}

int nombre_aleatoire (int min, int max) {
    return rand() % (max - min + 1) + min;
}

char* concatener (char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void shuffle (int *array, size_t n) {
    if (n > 1)  {
        size_t i;
        
        for (i = 0; i < n - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}