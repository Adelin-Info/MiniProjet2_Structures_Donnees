#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entreeSortieLC.h"
#include "entreeSortieH.h"

// Menu du mode de gestion 
void menu1(){
	printf("\nQuel mode de gestion souhaitez vous pour la bibliothèque ?\n");
	printf("0-Sortir du programme\n");
	printf("1-Liste chainée\n");
	printf("2-Table de hachage\n");
}

// Menu des choix réalisables sur la bibliothèque
void menu2(){
	printf("\nQuel choix souhaitez vous ?\n");
	printf("0-Changez de mode de gestion\n");
	printf("1-Afficher la bibliothèque\n");
	printf("2-Insérer un ouvrage\n");
	printf("3-Supprimer un ouvrage\n");
	printf("4-Recherche d'un ouvrage par son numéro\n");
	printf("5-Recherche d'un ouvrage par son titre\n");
	printf("6-Recherche des ouvrages d'un auteur\n");
	printf("7-Recherche des ouvrages avec plusieurs exemplaires\n");
	printf("8-Fusionner deux bibliothèques\n");
	printf("9-Enregistrer la bibliothèque\n");
}
	
	
int main(int argc, char** argv){
	if (argc != 3){
		printf("Usage: il manque des paramètres\n");
		return -1;
	}
	
	//initialisation de l'ensemble des variables qu'on aura besoin 
	int n = atoi(argv[2]);
	Biblio* B1;
	Biblio* Btmp1;
	BiblioH* B2;
	BiblioH* Btmp2;
	int num;
	int nbLigne;
	char titre[50];
	char auteur[50];
	char tmp[50];
	char rep[50];
	char nomfic[50];
	int mode;
	int choix;
	
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu;
	
	do{
		//appartition du menu demandant le mode
		menu1();
		printf("Entrez votre mode: ");
		fgets(rep,50,stdin);
		mode = atoi(rep); // conversion de la chaine de caractere en int grace a atoi
		switch (mode){
			
		case 1: //mode liste chainee
			B1 = charger_n_entrees(argv[1],n);
			do{
				//apparition du menu demandant les actions sur la bibliothèque
				menu2();
				printf("Entrez votre choix: ");
				fgets(rep,50,stdin);
				choix = atoi(rep);
				switch (choix){
					
				case 1: //affichage de la bibliothèque 
					printf("\nAffichage de la bibliothèque:\n");
					affichage_biblio(B1);
					break;
					
				case 2: //inserer un livre
					printf("\nInsertion d'un ouvrage:\n");
			
					printf("Numéro de l'ouvrage: ");
					fgets(tmp,50,stdin);
					num = atoi(tmp);
			
					printf("\nTitre de l'ouvrage: ");
					fgets(titre,50,stdin);
					titre[strlen(titre)-1] ='\0';     // enlever la saisie entree de la chaine de caractère
			
					printf("\nAuteur de l'ouvrage: ");
					fgets(auteur,50,stdin);
					auteur[strlen(auteur)-1]='\0';
			
					inserer_en_tete(B1,num,titre,auteur);
					break;
					
				case 3: //supprimer un livre 
					printf("\nSuppression d'un ouvrage:\n");
			
					printf("Numéro de l'ouvrage: ");
					fgets(tmp,50,stdin);
					num = atoi(tmp);
			
					printf("Titre de l'ouvrage: ");
					fgets(titre,50,stdin);
					titre[strlen(titre)-1] ='\0';
			
					printf("Auteur de l'ouvrage: ");
					fgets(auteur,50,stdin);
					auteur[strlen(auteur)-1]='\0';
			
					suppression_ouvrage(B1,num,titre,auteur);
					break;
					
				case 4: //Recherche d'un livre par son numero 
					printf("\nRecherche d'un ouvrage par son numéro:\n");
			
					printf("Numéro de l'ouvrage: ");
					fgets(tmp,50,stdin);
					num = atoi(tmp);
					
					temps_initial = clock();
					recherche_numero(B1,num);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps : %f\n",temps_cpu);
					break;
					
				case 5: //Recherche d'un livre par son titre
					printf("\nRecherche d'un ouvrage par son titre:\n");
			
					printf("Titre de l'ouvrage: ");
					fgets(titre,50,stdin);
					titre[strlen(titre)-1] ='\0';
					
					temps_initial = clock();
					recherche_titre(B1,titre);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps : %f\n",temps_cpu);
					break;
					
				case 6: // Recherche de tout les livres d'un auteur 
					printf("\nRecherche des ouvrages d'un auteur:\n");
			
					printf("Auteur des ouvrages: ");
					fgets(auteur,50,stdin);
					auteur[strlen(auteur)-1]='\0';
					
					temps_initial = clock();
					Btmp1=recherche_auteur(B1,auteur);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps : %f\n",temps_cpu);
					
					affichage_biblio(Btmp1);
					liberer_biblio(Btmp1);
					break;
					
				case 7: // Recherche de plusieurs exemplaires dans la biblio
					printf("\nRecherche des ouvrages avec plusieurs exemplaires:\n");
					
					temps_initial = clock();
					Btmp1 = recherche_plusieurs_exemplaires(B1,n);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps : %f\n",temps_cpu);
					
					affichage_biblio(Btmp1);
					liberer_biblio(Btmp1);
					break;
					
				case 8: //Fusionner deux bibliothèque
					printf("\nFusionner deux bibliothèques:\n");
			
					printf("Nom du fichier: ");
					fgets(nomfic,50,stdin);
					nomfic[strlen(nomfic)-1]='\0';
			
					printf("Nombre de lignes du fichier à stocker: ");
					fgets(tmp,50,stdin);
					nbLigne = atoi(tmp);
			
					Btmp1 = charger_n_entrees(nomfic,nbLigne);
					fusion_biblio(B1,Btmp1);
					break;
					
				case 9: // Enregistrer la bibliothèque dans un nouveau fichier
					printf("\nEnregistrer la bibliothèque\n");
					printf("Nom du fichier: ");
					fgets(nomfic,50,stdin);
					nomfic[strlen(nomfic)-1]='\0';
					enregistrer_biblio(B1,nomfic);
					break;
				}
			}while(choix!=0); // retour au menu de mode
			liberer_biblio(B1);
			break;
			
		case 2: // Mode Table de hachage
			B2 = chargerH(argv[1],n);
			do{
				//apparition du menu demandant les actions sur la bibliothèque
				menu2();
				printf("Entrez votre choix: ");
				fgets(rep,50,stdin);
				choix = atoi(rep);
				switch (choix){
					
				case 1: //afficher bibliothèque   
					printf("\nAffichage de la bibliothèque:\n");
					affichage_biblioH(B2);
					break;
					
				case 2: //inserer un livre
					printf("\nInsertion d'un ouvrage:\n");
			
					printf("Numéro de l'ouvrage: ");
					fgets(tmp,50,stdin);
					num = atoi(tmp);
			
					printf("Titre de l'ouvrage: ");
					fgets(titre,50,stdin);
					titre[strlen(titre)-1] ='\0';
			
					printf("Auteur de l'ouvrage: ");
					fgets(auteur,50,stdin);
					auteur[strlen(auteur)-1]='\0';
			
					inserer(B2,num,titre,auteur);
					break;
				case 3:// Supprimer un livre
					printf("\nSuppression d'un ouvrage:\n");
			
					printf("Numéro de l'ouvrage: ");
					fgets(tmp,50,stdin);
					num = atoi(tmp);
			
					printf("Titre de l'ouvrage: ");
					fgets(titre,50,stdin);
					titre[strlen(titre)-1] ='\0';
			
					printf("Auteur de l'ouvrage: ");
					fgets(auteur,50,stdin);
					auteur[strlen(auteur)-1]='\0';
			
					suppressionH(B2,num,titre,auteur);
					break;
				case 4:// Recherche d'un livre par son numero
					printf("\nRecherche d'un ouvrage par son numéro:\n");
			
					printf("Numéro de l'ouvrage: ");
					fgets(tmp,50,stdin);
					num = atoi(tmp);
					
					temps_initial = clock();
					recherche_numeroH(B2,num);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps = %f\n",temps_cpu);
					break;
				case 5: //Recherche d'un livre par son titre
					printf("\nRecherche d'un ouvrage par son titre:\n");
			
					printf("Titre de l'ouvrage: ");
					fgets(titre,50,stdin);
					titre[strlen(titre)-1] ='\0';
					
					temps_initial = clock();
					recherche_titreH(B2,titre);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps = %f\n",temps_cpu);
					break;
				case 6: // Recherche des livres d'un auteur
					printf("\nRecherche des ouvrages d'un auteur:\n");
			
					printf("Auteur des ouvrages: ");
					fgets(auteur,50,stdin);
					auteur[strlen(auteur)-1]='\0';
					
					temps_initial = clock();
					Btmp2 = recherche_auteurH(B2,auteur);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps = %f\n",temps_cpu);
					
					affichage_biblioH(Btmp2);
					liberer_biblioH(Btmp2);
					break;
				case 7: // Recherche plusieurs exemplaires dans la bibliothèque
					printf("\nRecherche des ouvrages avec plusieurs exemplaires:\n");
					temps_initial = clock();
					Btmp2 = recherche_plusieurs_exemplairesH(B2,n);
					temps_final = clock();
					temps_cpu = ((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;
					printf("temps = %f\n",temps_cpu);
					
					affichage_biblioH(Btmp2);
					liberer_biblioH(Btmp2);
					break;
				case 8: //Fusion deux bibliothèques
					printf("\nFusionner deux bibliothèques:\n");
			
					printf("Nom du fichier: ");
					fgets(nomfic,50,stdin);
					nomfic[strlen(nomfic)-1]='\0';
			
					printf("Nombre de lignes du fichier à stocker: ");
					fgets(tmp,50,stdin);
					nbLigne = atoi(tmp);
			
					Btmp2 = chargerH(nomfic,nbLigne);
					fusionH(B2,Btmp2);
					break;
				case 9:// Enregistrer la bibliothèque dans un nouveau fichier
					printf("\nEnregistrer la bibliothèque\n");
					printf("Nom du fichier: ");
					fgets(nomfic,50,stdin);
					nomfic[strlen(nomfic)-1]='\0';
					enregistrerH(B2,nomfic);
					break;
				}
			}while(choix!=0); // retour au menu mode 
			liberer_biblioH(B2);
			break;
		}
	}while (mode!=0); // quitte le programme
	printf("\nMerci et au revoir !\n");
	return 0;
}

	