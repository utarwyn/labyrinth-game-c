
#include "joueur.h"

#define CLASSEMENT_NOMBRE 10

/**
 * Structure de contrôle d'un classement de labyrinthe.
 * Gère les 10 meilleurs joueurs (en fonction de leur score).
 **/
typedef struct {

    labyrinthe laby;
    int nombre;
    joueur meilleurs[CLASSEMENT_NOMBRE];

} classement ;

/**
 * Affiche un classement dans le terminal.
 * 
 * @param classement Classement à afficher dans la console.
 **/
void afficher_classement (classement classement);

/**
 * Calcule la place théorique qu'aurait un joueur dans un classement
 * avec le score qu'il possède au moment de l'exécution de la fonction.
 * 
 * @param classement Classement où réaliser le calcul de la place
 * @param joueur Joueur concerné par le calcul de la place
 * @return Place du joueur théorique calculée
 **/
int recuperer_place_joueur (classement classement, joueur joueur);

/**
 * Ajoute un joueur spécifique dans le classement. Elle retrie
 * dans un second le classement afin d'avoir les scores des joueurs
 * dans un ordre croissant.
 * 
 * @param classement Pointeur vers le classement où ajouter le joueur
 * @param joueur Joueur à ajouter dans le classement
 **/
void nouveau_joueur_classement (classement * classement, joueur joueur);

/**
 * Compare le score de deux joueurs pour le tri dans le classement
 * grâce à la fonction qsort.
 * 
 * @param a Pointeur vers le premier objet à trier (joueur 1)
 * @param b Pointeur vers le second objet à trier (joueur 2)
 * @return Score du premier joueur par rapport au second.
 **/
int comparer_joueur_classement(void const *a, void const *b);

/**
 * Initialise le classement avec des valeurs par défaut
 * pour s'assurer de son bon fonctionnement tout au long
 * de l'exécution du programme.
 * 
 * @param classement Pointeur vers le classement à initialiser
 **/
void initialiser_classement (classement * classement);

/**
 * Charge un classement depuis un fichier de score (.score).
 * Pour cela, il prend en compte le nom du labyrinthe passé en paramètre.
 * 
 * @param laby Labyrinthe pour lequel il faut charger le fichier des scores
 * @return Le classement chargé depuis le fichier spécifique.
 **/
classement charger_classement (labyrinthe laby);

/**
 * Sauvegarde un classement dans un fichier spécifique.
 * Pour cela, il prend en compte le nom du labyrinthe auquel il est lié.
 * 
 * @param classement Classement à sauvegarder dans un fichier.
 **/
void sauvegarder_classement (classement classement);