// Le jeu de BlackJack

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bj_jeu.h"
#include"bj_affichage.h"

static char commence;
static int nb_joueurs,nb_cartes;
static char**noms_des_joueurs=NULL;
static struct s_table table;

void bienvenue();
void main_menu ();
void inscrire();
void renseigner();
void jouer();
int init_noms_joueurs();
void premier_tour(struct s_table*table);
void deuxieme_tour(struct s_table*table);
void rand_tour(struct s_table*table);
void eliminer(struct s_table*table);

//*****************main()***************************
void main()
{
	   
       
	   //utiliser la fonction de faire la figure....
	    bienvenue();
      
	  // entrer le  menu principal 
		main_menu ();
		
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
		while(1)
		{
			printf("*****************************************BlackJack**********************************************\n\n\n\n\n\n");
			printf("                                         Main Menu\n\n\n\n\n\n");
			printf("                                      1.S'inscrire en jeu.\n\n");
			printf("                                    2.Se renseigner sur le jeu.");
			scanf("%d",&choix);
			switch(choix){
			case 1:system("cls");inscrire();break;
			case 2:system("cls");renseigner();break;
			default:printf("\nEntree erreur!\n");
				    system("pause");
					system("cls");
					continue;
			}
		    //commence a jouer.
				do
				{    
					 system("cls");
					 printf("\n\n\n\n                            Demarrez le jeu tout a l'heure? \n\n\n\n");
					 printf("                                          Y/N    ");
					 scanf("%c",&commence);
				}while(commence!='Y'&&commence!='N');
				switch(commence){
					case 'Y':jouer();break;//aller a la derniere break!
					default: system("cls");continue;
					}
				break;//while(1)
			}
		
		
		printf("Au revoir!\n");//sortir du jeu sans s'inscrire
		free(noms_des_joueurs);		
}
void inscrire(){
	
        printf("                       Entrez le nombre de joueurs,s'il vous plait.\n");
		printf("                             Le nombre de joueurs:  ");
		scanf("%d",&nb_joueurs);
		printf("                       Entrez le nombre de cartes,s;il vous plait.\n");
		printf("                             Le nombre de cartes:   ");
		scanf("%d",&nb_cartes);
		printf("nb_cartes=%d",nb_cartes);
		system("pause");
		init_noms_joueurs();
}
void renseigner(){

}

//enregistrer des noms des joueurs
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
			scanf("%c",&sauvegarder);
			switch(sauvegarder)
			{
			case 'Y':system("cls");return 1;
			case 'N':noms_des_joueurs=NULL;system("cls");return 0;
			default:printf("Entree fausse!Entrez encore une fois!\n");
				system("cls");
			}
		}
}

//le jeu commence!
void jouer(){
    
	int*affiche_score=(int*)malloc(sizeof(int)*(nb_joueurs+1));
	printf("commencer a jouer!");

	//initialiser le jeu
	if(init_jeu(&table,nb_joueurs,nb_cartes,noms_des_joueurs,affiche_score)){
		printf("Le jeu ne s'est pas deroule!\n");
		return;
	}
	//donner des cartes au premier tour
    premier_tour(&table);
	deuxieme_tour(&table);
	eliminer(&table);
 /*   rand_tour(&table);
	*/
}
//
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
}
void premier_tour(struct s_table*table){
	int i=0;
	while(i<table->nb_joueurs)
	{	
		donne_une_carte(table,i);
		table->joueurs[i].points=calcule_score(table->joueurs[i].jeu_en_main,table->joueurs[i].nb_cartes);
		i++;
	}

//	affiche_jeu(table);
}
void deuxieme_tour(struct s_table*table){
    int i=0;
	while(i<table->nb_joueurs)
	{	
		donne_une_carte(table,i);
		table->joueurs[i].points=calcule_score(table->joueurs[i].jeu_en_main,table->joueurs[i].nb_cartes);
		i++;
	}
}
void rand_tour(struct s_table*table){

}
void eliminer(struct s_table*table){
	int i=0;
	int choix2;
	while(i<table->nb_joueurs){
		if(table->joueurs[i].points==21)
			printf("numero %d des joueurs %s a BlackJack!\n",i+1,table->joueurs[i].nom);
		else if(table->joueurs[i].points>21){
			printf("%s est elimite.\n",table->joueurs[i].nom);
			table->joueurs[i]=table->joueurs[table->nb_joueurs-1];
			table->nb_joueurs--;
		}
		else{
			while(1){
				printf("Joueur %s,entrez un choix,s'il vous plait.\n",table->joueurs[i].nom);
			    printf("             1.restez \n             2.tirez une carte?\n");
				scanf("%d",&choix2);
				switch(choix2){
				case 1:break;
				case 2:donne_une_carte(table,i);break;
				default:continue;
				}
				break;
			}
		}
		i++;
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
	table->joueurs[id_joueur].jeu_en_main[table->joueurs[id_joueur].nb_cartes]=indice_carte;
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
				if((score+11)>=21)
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
	
		return score;
}
//tire une carte au hasard dans le talon et la donne au joueur
//Le score du joueur est mis à jour.
/*
void donne_une_carte(struct s_table*tables,int id_joueur){
//	int carte=tire_ carte(tables);
}*/
