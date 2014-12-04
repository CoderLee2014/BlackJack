/* BJ_AFFICHAGE.H
 * 
 * contient les foncions relatives a la gestion de l'affichache
 *
 */

#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "bj_jeu.h"

/* Fonction: affiche_main
 *  Entrees: - un joueur
 *  Sorties:  aucune
 *
 *  Affiche la main du joueur passe en parametre
 */
void affiche_main(struct s_joueur joueur);


/*  Fonction affiche_jeu
 *  Entrees: - la table de jeu
 *  Sorties: aucune
 *
 * Affiche la main de tous les joueurs de la table
 *  y compris la banque.
 */
void affiche_jeu(struct s_table table);


/*  Fonction: convert_card_name
 *  Entrees: - indice de la carte dans le tableau de cartes
 *           - chaine de caractÃ¨re pour la couleur de la carte
 *           - chaine de caractÃ¨re pour le numero de la carte
 *  Sorties: aucune
 * 
 *  Traduit l'indice de la carte du tableau en un format
 *   comprehensible (ex: couleur = "coeur", number = "As")
 *  La memoire est supposee allouee pour les chaines de caracteres.
 */
void convert_card_name(int carte, char *couleur, char *number);


#endif
