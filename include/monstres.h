#include "classement.h"

/**
 * Structure représentant un monstre quelconque
 * dans le labyrinthe. Elle permet de connaître
 * sa ligne, sa colonne, son type, et ses méthodes
 * de déplacement et de pénalité.
 **/
typedef struct {

    int ligne;
    int colonne;
    char type;

    void (* deplacer)();
    int (* penalite)();

} monstre ;

/**
 * Initialise des monstres aléatoirement dans un labyrinthe
 * lorsque sa difficulté est en mode difficile.
 * 
 * @param laby Labyrinthe où initialiser les monstres
 * @return Liste des monstres générés
 **/
monstre * initialiser_monstres (labyrinthe * laby);

/**
 * Lance le déplacement de tous les monstres dans le labyrinthe.
 * 
 * @param monstres Liste des monstres générés
 * @param laby Labyrinthe où déplacer les monstres
 **/
void deplacer_monstres (monstre * monstres, labyrinthe laby);

/**
 * Lance le déplacement d'un archer.
 * 
 * @param monstre Archer à déplacer
 * @param laby Labyrinthe où l'archer se situe
 **/
void deplacer_archer (monstre * monstre, labyrinthe laby);

/**
 * Lance le déplacement d'un fantôme.
 * 
 * @param monstre Fantôme à déplacer
 * @param laby Labyrinthe où le fantôme se trouve
 **/
void deplacer_fantome (monstre * monstre, labyrinthe laby);

/**
 * Teste si un joueur doit prendre des pénalités ou non.
 * 
 * @param monstres Liste des monstres à tester
 * @param laby Labyrinthe dans lequel est le joueur
 * @param joueur Joueur à tester
 * @return Nombre de pénalités que le joueur doit avoir
 **/
int tester_penalites (monstre * monstres, labyrinthe laby, joueur * joueur);

/**
 * Renvoie le nombre de pénalités qu'un joueur doit avoir
 * pour un archer spécifique.
 * 
 * @param monstre Archer à tester
 * @param joueur Joueur à tester
 * @return Nombre de pénalités que le joueur doit avoir
 **/
int penalite_archer (monstre monstre, joueur * joueur);

/**
 * Renvoie le nombre de pénalités qu'un joueur doit avoir
 * pour un fantôme spécifique.
 * 
 * @param monstre Fantôme à tester
 * @param joueur Joueur
 * @return Nombre de pénalités que le joueur doit avoir
 **/
int penalite_fantome (monstre monstre, joueur * joueur);

/**
 * Met à jour la position d'un monstre si ce dernier
 * est en relation avec un joueur.
 * 
 * @param monstres Liste des monstres
 * @param laby Labyrinthe où se trouve le monstre
 * @param joueur Joueur qui intéragit avec les monstres
 * @param ligne Ligne de départ du joueur
 * @param colonne Colonne de départ du joueur
 **/
void maj_position_monstre (monstre * monstres, labyrinthe laby,
                           joueur * joueur, int ligne, int colonne);
