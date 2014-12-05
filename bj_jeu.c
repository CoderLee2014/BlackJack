#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "bj_jeu.h"
#include "bj_affichage.h"

int init_jeu(struct s_table *table, int nb_joueurs, int nb_cartes,  char **noms_des_joueurs, const int *affiche_score)
{

    int i,r,t;
    if (nb_carte % 52=!0)
    {
        printf("Le nombre de cartes n'est pas juste.");
        return -1;
    }
    if (nb_joueurs <= 1)
    {
        printf("Le nombre de joueurs n'est pas juste. ");
        return -1;
    }
    if (*affiche_score =! 0 && *affiche_score =! 1)
    {
        printf("Le nombre d'affiche_score n'est pas juste. ");
        return -1;
    }
    table->nb_joueurs=nb_joueurs;                                            /*nombre de joueurs de la partie*//*ÖØÖÃÍæ¼Ò*/
    table->nb_cartes_max=nb_cartes;                                          /*nombre de cartes Max intial dans le talon*//*ÖØÖÃÅÆ*/
    table->nb_cartes_dispo=nb_cartes;
    for(i=0;i<nb_cartes;i++)
        table->cartes[i]=i;                                                  /*nombre de cartes intial dans le talon*//*ÖØÖÃÅÆ*/

    srand((int)time(0));
    for(i=0;i<nb_cartes;i++)
    {
        r=rand()%52;
        t=table->cartes[i];
        table->cartes[i]=table->cartes[r];
        table->cartes[r]=t;                                                  /*melange les cartes*//*Ï´ÅÆ*/
    }
    strcpy(table->banque.nom,"banque");
    table->banque.nb_cartes=0;
    table->banque.jeu_en_main[0]=NULL;
    table->banque.points=0;
    table->banque.affiche_score=*affiche_score;                              /* initialise la banque *//*³õÊ¼»¯×¯¼Ò*/

    for(i=0;i<nb_joueurs;i++)
    {
        strcpy((table->joueurs+i)->nom,noms_des_joueurs[i]);
        (table->joueurs+i)->nb_cartes=0;
        (table->joueurs+i)->jeu_en_main[0]=NULL;
        (table->joueurs+i)->points=0;
        (table->joueurs+i)->affiche_score=*(affiche_score+i);
    }                                                                        /* initialise les joueurs *//*³õÊ¼»¯Íæ¼Ò*/

    for(i=0;i<=nb_joueurs;i++)
    {
        donne_une_carte(table, i);
        donne_une_carte(table, i);
    }                                                                        /*distribue 2 cartes aux joueurs et la banque */ /*¸øËùÓÐÈË·¢Á½ÕÅÅÆ*/

    table->banque.points = calcule_score(table->banque.jeu_en_main,table->banque.nb_cartes);
                                                                             /*calcule le score de la banque *//*¼ÆËã×¯¼Ò·ÖÊý*/

    for(i=0;i<nb_joueurs;i++)
    {
        table->joueurs[i].points = calcule_score(table->joueurs[i].jeu_en_main,table->joueurs[i].nb_cartes);
    }
                                                                             /*calcule les scores des joueurs *//*¼ÆËãÍæ¼Ò·ÖÊý*/
    return 0;
}

int tire_carte(struct s_table *table)
{
    int indice;
    srand((int)time(0));
    indice=rand()%(table->nb_cartes_dispo);                                  /*choisis une carte au hazard *//*Ëæ»ú³éÕÅÅÆ*/
    table->nb_cartes_dispo--;                                                /*ÅÆ¶Ñ¼õÈ¥Ò»ÕÅ*/
    return indice;
}

