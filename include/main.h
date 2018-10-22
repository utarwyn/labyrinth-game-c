
#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <string.h>

#include "classement.h"
#include "utils.h"

/**
 * Vérifie et lance l'action désirée par l'utilisateur,
 * après affichage du menu. Cette méthode lance donc les méthodes
 * annexes pour traiter chacune des actions du jeu.
 * 
 * @param choix Choix de l'utilisateur dans le menu.
 **/
void executer_action_menu (int choix);

/**
 * Crée un labyrinthe avec un nom, une largeur et une hauteur.
 * Sauvegarde les informations de l'utilisateur dans un fichier
 * externe afin de le reharger plus tard. Charge aussi le labyrinthe
 * généré pour y jouer immédiatement.
 * 
 * @return La structure labyrinthe générée.
 **/
labyrinthe creer_labyrinthe ();

/**
 * Charge un labyrinthe en mémoire depuis un fichier externe.
 * L'utilisateur doit choisir le fichier à utiliser grâce à son
 * nom. La méthode affiche aussi la liste des fichiers disponibles
 * dans le dossier de sauvegarde des labyrinthes.
 * 
 * @return La structure labyrinthe chargée depuis le fichier.
 **/
labyrinthe charger_fichier_labyrinthe ();

/**
 * Lance une partie sur le labyrinthe actuellement chargé en mémoire.
 **/
void jouer_labyrinthe ();
