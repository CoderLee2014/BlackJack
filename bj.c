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
void bienvenue();
void main_menu ();
void inscrire();
int  demarrer();
void renseigner();
int  sortir();
void jouer();
int  init_noms_joueurs();
void premier_tour();
void deuxieme_tour();
void rand_tour();
void eliminer(int i);
void qui_gagner();
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
	printf("                                        ");
	system("pause");
	system("cls");
}


void main_menu(){	
       
		int choix;
        system("cls");
		while(1)
		{
			/*Page 0,c'est la page d'entree*/
			printf("*****************************************BlackJack**********************************************\n\n\n\n\n\n");
			printf("                                         Main Menu\n\n\n\n\n\n");
			printf("                                      1.S'inscrire en jeu.\n\n");
			printf("                                    2.Se renseigner sur le jeu.\n\n");
			printf("                                       3.Sortir.\n");
			printf("                                            Votre choix:");
			scanf("%d",&choix);
			getchar();

			switch(choix){
				case 1:
					   inscrire(); /*Entrer Page 1*/
					   break;
				case 2:
					   renseigner();    /*Entrer Page 2*/
					   break;
				case 3:if(sortir()==1)
					   {
						   return;
					   }
					   else
					   {
						   break;
					   }
				default:
					   printf("\nEntree erreur!\n");
				       system("pause");
				       break;
			}
				break;//while(1),sortir du jeu.
		}//while(1);
}

/*Entrer Page 1*/
void inscrire(){
	    while(1)
		{
			system("cls");
			printf("                       Entrez le nombre de joueurs,s'il vous plait.\n");
			printf("                             Le nombre de joueurs:  ");
			scanf("%d",&nb_joueurs);	
			getchar();
			if(nb_joueurs>NB_JOUEURS_MAX)
			{
				printf("C'est plus que le grand nombre des joueurs!\n");
				printf("Entrer encore une fois,s'il vous plait.\n");
				system("pause");
				continue;/*Rentrer Page 1.*/
			}
			break;	
		}

		if(init_noms_joueurs()==1)    /*Entrer Page 4*/
		{
			demarrer();
		}
}

/*Entrer Page 2*/
void renseigner(){
	system("cls");
	{
	
	}
}

/*Entrer Page 4, Enregistrer des noms des joueurs*/
int init_noms_joueurs(){
	    
		int i=0;
		char sauvegarder;
		noms_des_joueurs=(char**)malloc(sizeof(char*)*(nb_joueurs+1));
		
		system("cls");
		while(i<nb_joueurs){
			noms_des_joueurs[i]=(char*)malloc(sizeof(char)*TAILLE_NOM);
			printf("		   Entrez le nom de %deme joueur:\n",i+1);
			scanf("%s",noms_des_joueurs[i]);
			getchar();
			i++;
		}
	
		noms_des_joueurs[nb_joueurs]=(char*)malloc(sizeof(char)*TAILLE_NOM);
        printf("               Entrez le nom de la banque:\n");
		scanf("%s",noms_des_joueurs[nb_joueurs]);
        getchar();

		while(1)
		{
			printf("\n\n\n\nVous voulez les sauvegarder?\n\n\n\n");
			printf("              Y/N");
			printf("          Votre choix:");
			scanf("%c",&sauvegarder);
			getchar();
			switch(sauvegarder)
			{
			case 'Y':return 1;
			case 'N':noms_des_joueurs=NULL;
				     return 0;
			default:printf("\n\nEntree fausse!Entrez encore une fois!\n");
				system("cls");
			}
		}
}
int demarrer(){
			while(1)
			{    
				 system("cls");
				 printf("\n\n\n\n                            Demarrez le jeu tout a l'heure? \n\n\n\n");
				 printf("                                          Y/N\n");
				 scanf("%c",&commence);
				 getchar();
				
			   	 switch(commence){
					case 'Y':jouer();return 1;
					case 'N':return 0;
					default: printf("Entrer encore une fois,s'il vous plait.\n");
							 system("pause");
						     continue;
				}
			}
}
//le jeu commence!
void jouer(){
    int blackjack=0;
	char demande;
	int i=0;
	int*affiche_score=(int*)malloc(sizeof(int)*(nb_joueurs+1));
	while(i<nb_joueurs){
		affiche_score[i++]=1;
	}

	affiche_score[nb_joueurs]=0;/*des cartes de la banque ne peuvent pas etre voits.*/

	//initialiser le jeu
	if(init_jeu(&table,nb_joueurs,nb_cartes,noms_des_joueurs,affiche_score)){
		printf("Le jeu ne s'est pas deroule!\n");
		return;
	}
	else{
		printf("\nInitialisation succes!\n");
	}
	//faire une boucle pour accomplir tous le jeu
	while(table.nb_joueurs)
	{
		if(blackjack==1)//game over 1.
		{
			break;
		}
		for( i=0;i<=table.nb_joueurs;i++)
		{
			if(table.joueurs[i].points==21&&table.joueurs[i].nb_cartes==2){
				blackjack=1;
				printf("Joueur  %s a gagne!\n",table.joueurs[i].nom);
				break;
			}
			if(table.joueurs[i].points>21)
			{	
				eliminer(i);
				if(banque==0&&table.nb_joueurs==1)
				{
					printf("%s a gagner!\n",table.joueurs[0].nom);
					return;
				}
				continue;//continuer for()
			}
			while(1)
			{
				printf("Joueur %s,Vous voulez demander une carte?\n",table.joueurs[i].nom);
				printf("Y/N   ");
				scanf("%c",&demande);
				getchar();
			    if(demande=='Y'){
					donne_une_carte(&table,i);
					table.joueurs[i].points=calcule_score(table.joueurs[i].jeu_en_main,table.joueurs[i].nb_cartes);
					if(table.joueurs[i].points<21)
						continue;
					else if(table.joueurs[i].points==21)
					{
						printf("%s a gagne!\n",table.joueurs[i].nom);
					}
					else
					{
						printf("Joueur %s a ete elimine.\n",table.joueurs[i].nom);
						eliminer(i);
						break;
					}
				}
				if(demande=='N')
				{
					
					break;
				}
			}//while(1)
		}//for()
	
	}//while(table.nb_joueurs)
	printf("nb_joueurs=%d\n",table.nb_joueurs);
	if(blackjack==1) return;

	if(table.nb_joueurs==0&&table.joueurs[0].points<=21) 
	{
		printf("La banque %s a gagne!\n",table.banque.nom);
		return;
	}
	printf("nihao\n");
    qui_gagner();
 /*   rand_tour(&table);
	*/
}//jouer()
//
/*
int init_jeu(struct s_table *table, int nb_joueurs, int nb_cartes,char **noms_des_joueurs, const int *affiche_score){
	int i=0;
	table->joueurs=(struct s_joueur*)malloc(sizeof(struct s_joueur)*(nb_joueurs+1));
	table->nb_joueurs=nb_joueurs;
	table->nb_cartes_max=NB_CARTES_DEFAUT;
	table->nb_cartes_dispo=nb_cartes;
	while(i<nb_joueurs){
		strcpy(table->joueurs[i].nom,noms_des_joueurs[i]);
		table->joueurs[i].nb_cartes=0;
		table->joueurs[i].affiche_score=0;
		table->joueurs[i].points=0;
		i++;
	}
	
	strcpy(table->banque.nom,noms_des_joueurs[nb_joueurs]);
	
	//intialiser des cartes
	table->cartes=(int*)malloc(sizeof(int)*nb_cartes);
	i=0;
	while(i<nb_cartes){
		table->cartes[i]=rand()%52;
		printf("%d\t",table->cartes[i]);
		i++;
	}
	return 0;
}*/
int init_jeu(struct s_table *table, int nb_joueurs, int nb_cartes,  char **noms_des_joueurs, const int *affiche_score)
{

    int i=0,r,t,j=0;
    if (nb_cartes % 52!=0)
    {
        printf("Le nombre de cartes n'est pas juste.");
        return -1;
    }
    if (nb_joueurs <= 0)
    {
        printf("Le nombre de joueurs n'est pas juste. ");
        return -1;
    }
	while(i<nb_joueurs){
		if (affiche_score [i]!= 1)
		{
			printf("Le nombre d'affiche_score n'est pas juste. ");
			return -1;
		}
		i++;
	}
	if(affiche_score[nb_joueurs]!=0)
		printf("Le nombre d'affiche_score n'est pas juste.");
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
	/*distribue 2 cartes aux joueurs et la banque */                                                     /*calcule les scores des joueurs */
	i=0;
	while(i<=table->nb_joueurs)
	{
		if(table->joueurs[i].points==21)
			printf("%s a gagne!(2premier tour)\n",table->joueurs[i].nom);
		i++;
	}
    return 0;
}


void rand_tour(){

}
/*
fonction
nom:eliminer()
fonctionalite:supprimer un joueur 
*/
void eliminer(int i){
    table.joueurs[i]=table.joueurs[table.nb_joueurs];
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
	int a=table->joueurs[id_joueur].nb_cartes+1;

	table->joueurs[id_joueur].jeu_en_main[a]=indice_carte;
    table->joueurs[id_joueur].nb_cartes++;

	/*
	if(table->joueurs[id_joueur].points==21){
		table->joueurs[id_joueur].affiche_score=1;//BlackJack!!!
	}
	else if(table->joueurs[id_joueur].points>21){
		table->joueurs[id_joueur].affiche_score=1;
	}*/
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
			else if(main[i]%13>0&&main[i]%13<10){
				score+=main[i]%13;
			}
			else{
				score+=10;
			}
			i++;
		}
	    printf("\nscore=%d\n",score);
		return score;
}
void qui_gagner(){
	int max=table.joueurs[0].points;
	int num_max=0;
	int i=0;
	while(i<=table.nb_joueurs)
	{
		if(table.joueurs[i].points==21)
			printf("%s a gagne!\n",table.joueurs[i].nom);
		if(table.joueurs[i].points>max)
		{
			max=table.joueurs[i].points;
			num_max=num_max+i+1;
		}
		i++;
	}
	printf("Joueur %s a gagne!\n",table.joueurs[0]);
}
/*Entrer Page 3*/
int sortir(){
	int choix2;
	while(1)
	{
		system("cls");
		printf("\n\n\n\n                  Voulez-vous sortir?\n\n\n");
		printf("                        1.Oui\n");
		printf("                        2.Non\n");
		printf("                       Votre choix:");
		scanf("%d",&choix2);
		getchar();
		switch(choix2){
			case 1:return 1;
			case 2:return 0;
			default:printf("Donnez votre choix encore une fois,s'il vous plait.\n");
					system("Pause");
		}
	}
}
//tire une carte au hasard dans le talon et la donne au joueur
//Le score du joueur est mis Ã  jour.
/*
void donne_une_carte(struct s_table*tables,int id_joueur){
//	int carte=tire_ carte(tables);
}*/
