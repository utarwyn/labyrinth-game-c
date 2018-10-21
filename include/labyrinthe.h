#include <stdio.h>
#include <dirent.h>
#include <assert.h>
#include <sys/stat.h>

#include "utils.h"

#define MUR -1
#define JOUEUR -2
#define TRESOR -3
#define PIEGE -4

#define DEPART_LIG 1
#define DEPART_COL 0
#define ARRIVEE_LIG -2
#define ARRIVEE_COL -1

#define CHANCE_PIEGE .03
#define CHANCE_TRESOR .04

#define SCORE_TRESOR -5
#define SCORE_PIEGE +4
#define SCORE_DEPLACEMENT +1

#define CHEMIN_LABYS "labys/"

/**
 * Structure représentant un labyrinthe.
 * Elle permet donc des les manipuler plus simplement à travers
 * toute l'application.
 **/
typedef struct {

    char nom[50];
    int largeur;
    int hauteur;
    int ** tableau;

} labyrinthe;

/**
 * Génère la structure du labyrinthe, avec des murs pour l'entourer,
 * et des cases libres en colonne paire.
 * (C'est pourquoi il est important de fournir un nombre de
 *  colonnes et de lignes impairs pour garder ce comportement.)
 * 
 * @param laby Labyrinthe déjà initialisé en mémoire pour être rempli.
 **/
void creer_structure_labyrinthe (labyrinthe laby);

/**
 * Génère les chemins et l'entrée/sortie du labyrinthe
 * pour qu'il puisse être résolu.
 * Le labyrinthe possède après cette méthode au moins un
 * chemin permettant de rejoindre la sortie depuis l'entrée.
 * 
 * @param laby Labyrinthe déjà préparé et structuré
 **/
void generer_labyrinthe_aleatoire (labyrinthe laby);

void generer_bonus_malus (labyrinthe laby);

/**
 * Remplace la valeur d'une section (plusieurs cases)
 * grâce à la récursivité.
 * 
 * @param tableau Tableau contenant le labyrinthe.
 * @param ligne Ligne à utiliser pour récupérer la case à remplacer.
 * @param colonne Colonne à utiliser pour récupérer la case à remplacer.
 * @param valeur Valeur initiale pour effectuer le remplacement.
 * @param valeur_a_remplacer Valeur qui va remplacer l'ancienne.
 **/
void remplacer_valeur_recursif (int ** tableau, int ligne, int colonne, int valeur, int valeur_a_remplacer);

/**
 * Charger un labyrinthe depuis un fichier (avec son nom).
 * 
 * @param nom Nom du fichier à charger en tant que labyrinthe.
 **/
labyrinthe charger_labyrinthe (char * nom);

/**
 * Sauvegarde un labyrinthe dans un fichier externe.
 * (La méthode enregistre les données sous forme binaire de telle sorte
 *  à utiliser le moins d'espace disque possible, surtout pour les grands labyrinthes)
 * 
 * @param laby Le labyrinthe à sauvegarder dans un fichier.
 **/
void sauvegarder_labyrinthe (labyrinthe laby);

/**
 * Affiche le labyrinthe dans la console.
 * 
 * @param laby Labyrinthe à afficher
 **/
void afficher_labyrinthe (labyrinthe laby);
