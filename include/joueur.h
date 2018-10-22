
#include "labyrinthe.h"

/**
 * Structure de gestion d'un joueur spécifique.
 * Elle permet de gérer plus facilement sa position dans le labyrinthe,
 * son nom, et son score, pour pouvoir mettre à jour le classement.
 **/
typedef struct {

    int ligne;
    int colonne;
    int score;
    char nom[50];

} joueur ;

/**
 * Prépare un joueur avant sa mise en jeu dans le labyrinthe correspondant.
 * Réinitialise sa position si jamais çela est nécessaire.
 * 
 * @param joueur Pointeur vers le joueur actuel dans le labyrinthe
 * @param laby Labyrinthe où se trouve le joueur
 **/
void preparer_joueur (joueur * joueur, labyrinthe laby);

/**
 * Ordonne au programme de déplacer un joueur dans un labyrinthe dans une
 * diection donnée par un caractère entré par l'utilisateur (z, q, s, d).
 * La méthode fait en sorte de vérifier si celui-ci ne va pas taper un
 * mur et s'il arrive à la destination. Elle compte aussi son nombre de déplacement.
 * 
 * @param joueur Pointeur vers le joueur qui se déplace
 * @param laby Labyrinthe où se trouve le joueur
 * @param direction Direction vers laquelle le joueur veut se déplacer
 **/
void deplacer_joueur (joueur * joueur, labyrinthe laby, char direction);

/**
 * Vérifie si un joueur se trouve sur la position d'arrivée du labyrinthe ou non.
 * 
 * @param joueur Joueur actuel dans le labyrinthe
 * @param laby Labyrinthe où se trouve le joueur
 * @return 1 si le joueur est arrivé, 0 sinon.
 **/
int joueur_est_arrive (joueur joueur, labyrinthe laby);
