/*  BJ_JEU.H
 *
 * Contient les fonctions de gestion de jeu
 * 
 */

#ifndef _JEU_H
#define _JEU_H

#define NB_JOUEURS_MAX 1    /* Nombre de joueursmax, en plus de la banque */
#define NB_CARTES_DEFAUT 52    /* Nombre de cartes dans le jeu */
#define NB_CARTES_MAIN 20   /* Nombre max de cartes en main */
#define TAILLE_NOM 256      /* Taille limite pour le nom d'un joueur */

/* les defines suivant permettent de reperer les cartes 
 * dans le tableau de carte par leur position 
 * les cartes sont supposes rangees par couleur
 * dans l'odre croissant: AS, 2, 3, ..., Dame, Roi 
 */
#define AS_PIQUE 0
#define ROI_PIQUE 12
#define AS_COEUR 13
#define ROI_COEUR 25
#define AS_CARREAU 26
#define ROI_CARREAU 38
#define AS_TREFLE 39
#define ROI_TREFLE 51


/* structure de joueur */
struct s_joueur{
  char nom[TAILLE_NOM];     /* nom du joueur */
  int jeu_en_main[NB_CARTES_MAIN]; /* cartes en main du joueur */
  int nb_cartes;            /* nombre de cartes en main */
  int points;               /* nombre de points du joueur */
  int affiche_score;         /* 1 ou 0 pour afficher ou non le score en meme tems que la main */
};


/* structure pour la table de jeu */
struct s_table{
  struct s_joueur banque;    /* la banque est toujours presente */
  struct s_joueur *joueurs;  /* tableau pour gerer les joueurs */
  int *cartes;               /* jeu de carte utilise pour jouer */
  int nb_cartes_max;         /* nombre de carte maximum dans le talon */
  int nb_cartes_dispo;       /* nombre actuel de carte dans le talon */
  int nb_joueurs;            /* nombre de participants en plus de la banque */
};


/*  Fonction: init_jeu                                       
 *  Entrees: - pointeur sur la table de jeu                  
 *           - nombre de joueurs de la partie    
 *           - nombre de cartes intial dans le talon    
 *           - tableau de chaine de caractere avec les noms des joueurs     
 *           - tableau d'entier (de 0 ou 1) qui indique pour chaque joueur si on doit
 *                 afficher le score ou non.    
 *  Sortie:  - 0 si l'initialisation s'est bien deroulee     
 *           - -1 sinon                                      
 *                                                            
 *  Initialise la partie avec le nombre de joueurs necessaire 
 *  Met tous les scores et les tableaux a 0                  
 *  Distribue 2 cartes a tout le monde                       
 *  Calcule le score correspondant                           
 */
int init_jeu(struct s_table *table, int nb_joueurs, int nb_cartes,  char **noms_des_joueurs, const int *affiche_score);

/*  Fonction: tire_carte                                      
 *  Entrees: - pointeur sur la table de jeu                   
 *  Sorties: - entier representant l'indice de la carte tiree
 *             dans le tableau de carte                      
 *                                                           
 *  Tire une carte au hasard dans le talon                    
 */
int tire_carte(struct s_table *table);


/*  Fonction: donne_une_carte    
 *  Entrees: - pointeur sur la table de jeu 
 *           - indice du joueur a qui donner une carte  
 *  Sorties: aucune 
 *
 *  Tire une carte au hasard dans le talon et la donne au joueur
 *  Le score du joueur est mis a jour.
 */
void donne_une_carte(struct s_table *tables, int id_joueur);


/*  Fonction: calcule_score
 *  Entrees: - un pointeur vers une main
 *           - le nombre de cartes en main
 *  Sorties: - un entier correspondant au score de la main
 *
 *  Calcule le score d'une main donnee. Compte l'as comme 1 ou 11
 *   suivant le meilleur cas possible.
 */
int calcule_score(const int *main, int nb_cartes);

#endif
