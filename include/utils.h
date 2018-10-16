
/**
 * Créer un tableau à deux dimensions qui possède
 * une largeur et une hauteur dynamique.
 * Il est important de désallouer la mémoire occupée
 * par ce tableau une fois utilisé ! (avec liberer_tableau_2d).
 * 
 * @param largeur Largeur du tableau à créer
 * @param hauteur Hauteur du tableau à créer
 **/
int ** creer_tableau_2d (int largeur, int hauteur);

/**
 * Désalloue un tableau à deux dimensions créé avec
 * la méthode creer_tableau_2d.
 * 
 * @param tableau Tableau à désallouer de la mémoire
 **/
void liberer_tableau_2d (int ** tableau, int hauteur);

/**
 * Inverse deux valeurs avec leur pointeur.
 * (dans un tableau par exemple)
 * 
 * @param valeur_1 Premier pointeur
 * @param valeur2 Second pointeur
 **/
void inverser (int * valeur_1, int * valeur_2);

/**
 * Génère un nombre aléatoire entre deux
 * valeurs min et max comprises.
 * 
 * @param min Valeur minimum de l'aléatoire (comprise)
 * @param max Valeur maximum de l'aléatoire (comprise)
 **/
int nombre_aleatoire (int min, int max);

/**
 * Concatene deux chaines de caractères en une seule.
 * 
 * @param s1 première chaîne de caractères
 * @param s2 deuxième chaîne de caractères
 * @return chaîne finale concaténée.
 **/
char* concatener(char *s1, char *s2);