// Le jeu de BlackJack

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"bj_jeu.h"
#include"bj_affichage.h"

static char commence;
static int nb_joueurs,nb_cartes;
static char**noms_des_joueurs=NULL;
static struct s_table table;
static int banque=1;

void system_pause();
void bienvenue();
void main_menu ();
void inscrire();
int  demarrer();
void renseigner();
int  sortir();
void jouer();
int  init_noms_joueurs();
void faire_le_tour();
void eliminer(int i);
void demande_carte(int *i,int*si_demande);
//*****************main()***************************
void main()
{
	   
       
	   //utiliser la fonction de faire la figure....
	    bienvenue();
      
	  // entrer le  menu principal 

		main_menu ();

		free(noms_des_joueurs);	
		
		printf("Au revoir!\n");
		
}

//***************fonctions****************

void bienvenue(){

	printf("\n\n\n\n                                   Bienvenue a jouer BlackJack!\n\n\n\n\n");
	printf("                      ");
	system_pause();
	system("clear");
}


void main_menu(){	
       
		int choix;
        
		while(1)
		{
			/*Page 0,c'est la page d'entree*/
			system("clear");
			printf("*****************************************BlackJack**********************************************\n\n\n\n\n\n");
			printf("                                         Main Menu\n\n\n\n\n\n");
			printf("                                      1.S'inscrire en jeu.\n\n");
			printf("                                      2.Se renseigner sur le jeu.\n\n");
			printf("                                      3.Sortir.\n");
			printf("                                      Votre choix:");
			scanf("%d",&choix);
			getchar();

			switch(choix){
				case 1:
					   inscrire(); /*Entrer Page 1*/
					   continue;
				case 2:
					   renseigner();    /*Entrer Page 2*/
					   continue;
				case 3:if(sortir()==1)
					   {
						   return;
					   }
					   else
					   {
						   continue;
					   }
				default:
					   printf("\nEntree erreur!\n");
				           system_pause();
				           continue;
			}
		}//while(1);
}

/*Entrer Page 1*/
void inscrire(){
	    while(1)
		{
			system("clear");
			printf("                       Entrez le nombre de joueurs,s'il vous plait.\n\n");
			printf("                             Le nombre de joueurs:  ");
			scanf("%d",&nb_joueurs);	
			getchar();
			if(nb_joueurs>NB_JOUEURS_MAX)
			{
				printf("            C'est plus que le grand nombre des joueurs!\n");
				printf("               Entrer encore une fois,s'il vous plait.\n");
				system_pause();
				continue;/*Rentrer Page 1.*/
			}
			break;	
		}

		if(init_noms_joueurs()==1)    /*Entrer Page 4*/
		{
			if(demarrer()==0);
		}
}

/*Entrer Page 2*/
void renseigner(){
	system("clear");
	{
	
	}
}

/*Entrer Page 4, Enregistrer des noms des joueurs*/
int init_noms_joueurs(){
	    
		int i=0;
		char sauvegarder;
		noms_des_joueurs=(char**)malloc(sizeof(char*)*(nb_joueurs+1));
		
		system("clear");
		while(i<nb_joueurs){
			noms_des_joueurs[i]=(char*)malloc(sizeof(char)*TAILLE_NOM);
			printf("\n\n\n\n\n			Entrez le nom de %d eme joueur:\n",i+1);
			printf("                                    ");
			scanf("%s",noms_des_joueurs[i]);
			getchar();
			i++;
		}
	
	 	noms_des_joueurs[nb_joueurs]=(char*)malloc(sizeof(char)*TAILLE_NOM);
                printf("\n\n			Entrez le nom de la banque:\n");
		printf("                                    ");
		scanf("%s",noms_des_joueurs[nb_joueurs]);
                getchar();

		while(1)
		{
			printf("\n\n\n\n			Vous voulez les sauvegarder?\n\n\n\n");
			printf("					  Y/N\n");
			printf("				Votre choix:");
			scanf("%c",&sauvegarder);
			getchar();
			switch(sauvegarder)
			{
			case 'Y':return 1;
			case 'N':noms_des_joueurs=NULL;
				     return 0;
			default:printf("\n\n                 Entree fausse!Entrez encore une fois!\n");
				system("clear");
			}
		}
}
/*Entrer Page 5*/
int demarrer(){
			while(1)
			{    
				 system("clear");
				 printf("\n\n\n\n					Demarrez le jeu tout a l'heure? \n\n\n\n");
				 printf("                                                             Y/N\n");
				 printf("                                                                  ");
				 scanf("%c",&commence);
				 getchar();
				
			   	 switch(commence){
					case 'Y':jouer();return 1;
					case 'N':return 0;
					default: printf("					Entrer encore une fois,s'il vous plait.\n");
							 system_pause();
						     continue;
				}
			}
}

void jouer(){
    int blackjack=0;
	int i=0;
	int*affiche_score=(int*)malloc(sizeof(int)*(nb_joueurs+1));
	while(i<nb_joueurs){
		affiche_score[i++]=1;
	}

	affiche_score[nb_joueurs]=0;/*des cartes de la banque ne peuvent pas etre voits.*/

	/*initialiser le jeu*/
	if(init_jeu(&table,nb_joueurs,nb_cartes,noms_des_joueurs,affiche_score)){
		printf("Le jeu ne s'est pas deroule!\n");
		system_pause();
		return;
	}
	else{
		printf("\n					Initialisation succes!\n");
		system_pause();
	}
	 i=0;
	while(i<=nb_joueurs){
		if(table.joueurs[i].points==21)
		{
			affiche_jeu(table);	
			printf("			*************%s a gagne!(Resultat 1.)*************\n",table.joueurs[i].nom);
			blackjack=1;
		}
		i++;
	}
	if(blackjack==1)
		return;/*Rentrer Page 0.*//*Resultat 1*/
	faire_le_tour();
}//jouer()

/*Entrer Page 6.*/	/*faire une boucle pour accomplir tous le jeu*/
void faire_le_tour(){
	int i=0,j=0;
	int max_point;
	int si_demande=0;
//	system("clear");
	while(table.nb_joueurs)
	{ 
		i=0;
		if(si_demande==1)
	          si_demande=0;	
		while( i<(table.nb_joueurs+banque))
		{   
					
			if(table.joueurs[i].points==21)
			{
				affiche_jeu(table);
				printf("			*************%s a gagne!(Resultat 5.)*************\n",table.joueurs[i].nom);
				system_pause();
				return;/*Rentrer Page 0.*//*Resultat 5.*/
			}
			if(table.joueurs[i].points>21)
			{	
				printf("					%s a ete elimine!\n",table.joueurs[i].nom);
				eliminer(i);
				if(banque==0&&table.nb_joueurs==1)
				{
					affiche_jeu(table);	
					printf("		*************%s a gagne!(Resultat 2.)*************\n",table.joueurs[i].nom);
					affiche_main(table.joueurs[i]);
					banque=1;
					system_pause();
					return;/*Rentrer Page 0.*//*resultat 2.*/
				}
				if(banque==1&&table.nb_joueurs==0)
				{
					affiche_jeu(table);	
 					printf("		*************%s a gagne!(Resultat 3.)*************\n",table.joueurs[i].nom);
					system_pause();
					return;/*Rentrer Page 0.*//*resultat 3.*/
				}
				if(banque==0&&nb_joueurs==2)
				{
					affiche_jeu(table);					
					printf("		*************%s a gagne!(Resultat 4.)*************\n",table.joueurs[i].nom);
					system_pause();
					banque=1;
					return;/*Rentrer Page 0.*//*Resultat 4.*/
				}
				continue;//continuer for()
			}
			demande_carte(&i,&si_demande);
			if(table.joueurs[i].points==21)
                        {
	                        printf("		********%s a gagne!*********\n",table.joueurs[i].nom);
				while(j<(table.nb_joueurs+banque))
				{
				       if(table.joueurs[j].points==21)
						printf("		********%s a gagne!*********\n",table.joueurs[j].nom);
                                      j++;			
				}
				return;/*Rentrer Page 0.*//*Resultat 7.*/
		        }
			if(si_demande==0&&i==(table.nb_joueurs+banque))
			{   
				affiche_jeu(table);
				max_point=table.joueurs[0].points;
				j=0;
				while(j<(table.nb_joueurs+banque))
				{
					if(table.joueurs[j].points>max_point)
						max_point=table.joueurs[j].points;
					j++;
				}
				
				j=0;
				while(j<(table.nb_joueurs+banque))
				{

					if(table.joueurs[j].points==max_point)
						printf("		*************%s a gagne!(Resultat 6.)*************\n",table.joueurs[j].nom);
					j++;
				}
				system_pause();
				return;/*Rentrer Page 0*//*Resultat 6.*/
			}
		}//while(i<=nb)
	}//while(table.nb_joueurs)
   
}
/*Page 7.*/
void demande_carte(int *i,int*si_demande){
	char demande;
	int j=0;
//	system("clear");
	while(1)
			{
				printf("\n\n					 %s,Vous voulez demander une carte?\n",table.joueurs[*i].nom);
				printf("							Y/N   ");
				printf("                                   			  ");
				scanf("%c",&demande);
				getchar();
			    if(demande=='Y'){
					*si_demande=1;
					donne_une_carte(&table,*i);
					table.joueurs[*i].points=calcule_score(table.joueurs[*i].jeu_en_main,table.joueurs[*i].nb_cartes);
					if(table.joueurs[*i].points<21)
						continue;
					else 
					{   
						printf("					Le score de %s est superieur a 21!\n",table.joueurs[*i].nom);
						//system_pause();
						return;/*Rentrer Page 6.*/
					}
				}
				if(demande=='N')
				{
					if(table.joueurs[*i].points==21)
					{
						
						return;/*Rentrer Page 6.*/
					}
					(*i)++;
					//system_pause();
					return;/*Rentrer Page 6.*/
				}
				
			}//while(1)
}
/*          fdsfadfa*/
int init_jeu(struct s_table *table, int nb_joueurs, int nb_cartes,  char **noms_des_joueurs, const int *affiche_score)
{

    int i=0,r,t,j=0;
	nb_cartes=NB_CARTES_DEFAUT;
    if (nb_cartes % 52!=0)
    {
        printf("					Le nombre de cartes n'est pas juste.");
        return -1;
    }
    if (nb_joueurs <= 0)
    {
        printf("					Le nombre de joueurs n'est pas juste. ");
        return -1;
    }
	while(i<nb_joueurs){
		if (affiche_score [i]!= 1)
		{
			printf("					Le nombre d'affiche_score n'est pas juste. ");
			return -1;
		}
		i++;
	}
	if(affiche_score[nb_joueurs]!=0)
		printf("					Le nombre d'affiche_score n'est pas juste.");
    table->nb_joueurs=nb_joueurs;                                            /*nombre de joueurs de la partie*/
    table->nb_cartes_max=nb_cartes;                                          /*nombre de cartes Max intial dans le talon*/
    table->nb_cartes_dispo=nb_cartes;
	table->cartes=(int*)malloc(sizeof(int)*nb_cartes);
    for(i=0;i<nb_cartes;i++)
        table->cartes[i]=i;                                                  /*nombre de cartes intial dans le talon*/

    srand((int)time(0));
    for(i=0;i<nb_cartes;i++)
    {
        r=rand()%52;
        t=table->cartes[i];
        table->cartes[i]=table->cartes[r];
        table->cartes[r]=t;                                                  /*melange les cartes*/
    }
    strcpy(table->banque.nom,noms_des_joueurs[nb_joueurs]);
    table->banque.nb_cartes=0;
	i=0;
	table->joueurs=(struct s_joueur*)malloc(sizeof(struct s_joueur)*(nb_joueurs+1));//!!!!tousjours oublier!!!
	while(i<20){
		table->banque.jeu_en_main[i++]=-1;
	}
    table->banque.points=0;
    table->banque.affiche_score=affiche_score[nb_joueurs];                      /* initialise la banque */
    for(i=0;i<nb_joueurs;i++)
    {   
		
        strcpy(table->joueurs[i].nom,noms_des_joueurs[i]);
		table->joueurs[i].nb_cartes=0;
		while(j<20)
		{
			table->joueurs[i].jeu_en_main[j++]=-1;
		}
        table->joueurs[i].points=0;
        table->joueurs[i].affiche_score=affiche_score[i];
    }  
	table->joueurs[nb_joueurs]=table->banque;	                                         /* initialise les joueurs */
    for(i=0;i<=nb_joueurs;i++)
    {
        donne_une_carte(table, i);
        donne_une_carte(table, i);
		table->joueurs[i].points=calcule_score(table->joueurs[i].jeu_en_main,table->joueurs[i].nb_cartes);
    }  
	affiche_jeu(*table);
	/*distribue 2 cartes aux joueurs et la banque */                                                     /*calcule les scores des joueurs */
	i=0;
	while(i<=table->nb_joueurs)
	{
		if(table->joueurs[i].points==21)
			printf("\n			**********************Blackjack!**** %s a gagne!(2premier tour)\n",table->joueurs[i].nom);
		i++;
	}
    return 0;
}

/*
fonction
nom:eliminer()
fonctionalite:supprimer un joueur 
*/
void eliminer(int i){
        int j=i;
        while(j<(table.nb_joueurs-1+banque))
	{
            table.joueurs[j]=table.joueurs[j+1];
            j++;
        }
	if(i!=nb_joueurs)
	    table.nb_joueurs--;
	else{
		banque=0;
	}
}
/*
nom de fonction:joueur_cacul
entree:
sortie:
fonctionalite:
*/
int tire_carte(struct s_table*table){
	int indice=rand()%table->nb_cartes_dispo;
        int carte=table->cartes[indice];
	int temp;
	temp=table->cartes[indice];
	table->cartes[indice]=table->cartes[table->nb_cartes_dispo-1];
	table->cartes[table->nb_cartes_dispo-1]=temp;
	table->nb_cartes_dispo--;	

	return carte;
}

void donne_une_carte(struct s_table*table,int id_joueur){
	int indice_carte=tire_carte(table);
	int a=table->joueurs[id_joueur].nb_cartes;
	table->joueurs[id_joueur].jeu_en_main[a]=indice_carte;
    table->joueurs[id_joueur].nb_cartes++;
}

int calcule_score(const int*main,int nb_cartes){
		int i=0;
		int score=0;

		while(i<nb_cartes)
		{
			if(main[i]%13==0){
				//compte As comme 1 ou 11
				if((score+11)<=21)
					score+=11;
				else{ 
					score+=1;
				}
			}
		   if(main[i]%13>0&&main[i]%13<10){
				score+=main[i]%13+1;
			}
		    if(main[i]%13>=10){
				score+=10;
			}
		
			i++;
		}
	   
		return score;
}

/*Entrer Page 3*/
int sortir(){
	int choix2;
	while(1)
	{
		system("clear");
		printf("\n\n\n\n					 Voulez-vous sortir?\n\n\n");
		printf(" 							1.Oui\n");
		printf("							2.Non\n");
		printf("						 Votre choix:");
		scanf("%d",&choix2);
		getchar();
		switch(choix2){
			case 1:return 1;
			case 2:return 0;
			default:printf("					 Donnez votre choix encore une fois,s'il vous plait.\n");
				system_pause();
		}
	}
}
//tire une carte au hasard dans le talon et la donne au joueur
//Le score du joueur est mis à jour.
/*
void donne_une_carte(struct s_table*tables,int id_joueur){
//	int carte=tire_ carte(tables);
}*/
void affiche_main(struct s_joueur joueur)
{
    int i;
    printf("\n					Le score de %s est: %d\n",joueur.nom,joueur.points);
    printf("					les cartes de %s:\n",joueur.nom);
    printf("					nb_cartes=%d\n",joueur.nb_cartes);
    for(i=0;i<joueur.nb_cartes;i++)
    {
        char couleur[10];
        char number[10];
        convert_card_name(joueur.jeu_en_main[i], couleur, number);
        printf("					No%d:%s %s\n",i+1,couleur,number);
    }
}

void affiche_jeu(struct s_table table)
{
    int i;
    printf("\n<-------------------La banque------------------>\n");
    affiche_main(table.joueurs[nb_joueurs]);
    printf("\n<---------------------------------------------->\n\n\n\n");
    printf("\n<-------------------les Joueurs---------------->\n");
    for(i=0;i<table.nb_joueurs;i++)
    {
	printf("\n					<joueurs %s>\n",table.joueurs[i].nom);
        affiche_main(*(table.joueurs+i));
        
    }  
    printf("\n<--------------------------------------------->\n");                                                            /*Tous les joueurs*//*????*/
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
    }                                                                           
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
    }                                                                          
}
void system_pause(void)
{
 puts("                  Press any key to continue...");
 system("stty raw");
 getchar();
system("stty cooked");
}
