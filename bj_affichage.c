#include "bj_affichage.h"
#include "bj_jeu.h"
#include <stdio.h>
#include <string.h>

void affiche_main(struct s_joueur joueur)
{
    int i;
    printf("les cartes de %s:\n",joueur.nom);

    for(i=0;i<joueur.nb_cartes;i++)
    {
        char couleur[100];
        char number[100];
        convert_card_name(joueur.jeu_en_main[i], couleur, number);
        printf("No%d:%s %s\n",i+1,couleur,number);
    }
}

void affiche_jeu(struct s_table table)
{
    int i;
    affiche_main(table.banque);
    printf("<----------------->\n");

    for(i=0;i<table.nb_joueurs;i++)
    {
        affiche_main(*(table.joueurs+i));
        printf("<----------------->\n");
    }                                                                                  /*Tous les joueurs*//*¶ÔËùÓÐÈË*/
}

void convert_card_name(int carte, char *couleur, char *number)
{
    if(carte<(ROI_PIQUE-2)&&carte>AS_PIQUE)
    {
        sprintf(number,"%d",carte+1);
        strcpy(couleur,"PIQUE");
    }
    else if(carte<(ROI_COEUR -2)&&carte>AS_COEUR )
    {
        sprintf(number,"%d",carte-ROI_PIQUE);
        strcpy(couleur,"COEUR");
    }
    else if(carte<(ROI_CARREAU -2)&&carte>AS_CARREAU )
    {
        sprintf(number,"%d",carte-ROI_COEUR);
        strcpy(couleur,"CARREAU");
    }
    else if(carte<(ROI_TREFLE-2)&&carte>AS_TREFLE )
    {
        sprintf(number,"%d",carte-ROI_CARREAU);
        strcpy(couleur,"TREFLE");
    }                                                                                /*donne les informations des cartes 2-10*//*¸ø³ö2-10µÄÅÆµÄÐÅÏ¢*/
    else
    {
        switch(carte)
        {
            case AS_PIQUE:
                strcpy(number,"As");
                strcpy(couleur,"PIQUE");
                break;
            case AS_COEUR:
                strcpy(number,"As");
                strcpy(couleur,"COEUR");
                break;
            case AS_CARREAU:
                strcpy(number,"As");
                strcpy(couleur,"CARREAU");
                break;
            case AS_TREFLE:
                strcpy(number,"As");
                strcpy(couleur,"TREFLE");
                break;
            case ROI_PIQUE:
                strcpy(number,"Roi");
                strcpy(couleur,"PIQUE");
                break;
            case ROI_COEUR:
                strcpy(number,"Roi");
                strcpy(couleur,"COEUR");
                break;
            case ROI_CARREAU:
                strcpy(number,"Roi");
                strcpy(couleur,"CARREAU");
                break;
            case ROI_TREFLE:
                strcpy(number,"Roi");
                strcpy(couleur,"TREFLE");
                break;
            case ROI_PIQUE-1:
                strcpy(number,"Daome");
                strcpy(couleur,"PIQUE");
                break;
            case ROI_COEUR-1:
                strcpy(number,"Daome");
                strcpy(couleur,"COEUR");
                break;
            case ROI_CARREAU-1:
                strcpy(number,"Daome");
                strcpy(couleur,"CARREAU");
                break;
            case ROI_TREFLE-1:
                strcpy(number,"Daome");
                strcpy(couleur,"TREFLE");
                break;
            case ROI_PIQUE-2:
                strcpy(number,"Valet");
                strcpy(couleur,"PIQUE");
                break;
            case ROI_COEUR-2:
                strcpy(number,"Valet");
                strcpy(couleur,"COEUR");
                break;
            case ROI_CARREAU-2:
                strcpy(number,"Valet");
                strcpy(couleur,"CARREAU");
                break;
            case ROI_TREFLE-2:
                strcpy(number,"Valet");
                strcpy(couleur,"TREFLE");
                break;
        }
    }                                                                                   /*donne les informations des cartes As ou >10 *//*¸ø³öA£¬J£¬Q£¬K*/
}
