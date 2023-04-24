#include <stdio.h>
#include <stdlib.h>
#include "entreeSortieLC.h"

Biblio* charger_n_entrees(char* nomfic, int n){
	int i=0;
	int num;
	char ligne[50];
	char titre[50];
	char auteur[50];
	Biblio* B = creer_biblio();
	//ouverture du fichier en mode lecture
	FILE* fic = fopen(nomfic, "r");
	//teste si l'ouverture à fonctionner
	if (fic == NULL){
		printf("Probleme d'ouverture du fichier");
		free(B);
		exit(-1);
	}
	while ((i<n) && (fgets(ligne, 50, fic)!= NULL)){
		// teste si chaque ligne du buffer correspond au format souhaité
		if (sscanf(ligne, "%d %s %s", &num, titre, auteur) == 3){
			inserer_en_tete(B,num,titre,auteur);
		}
		else {
			printf("Format de la ligne incorrect");
			free(B);
			exit(-1);
		}
		i=i+1;
	}
	//fermeture du fichier
	fclose(fic);
	return B;
}

void enregistrer_biblio(Biblio* b, char* nomfic){
	//ouverture du fichier en mode ecriture
	FILE* fic = fopen(nomfic, "w");
	//teste si l'ouverture à fonctionner
	if (fic == NULL){
		printf("Probleme d'ouverture du fichier");
		exit(-1);
	}
	while (b->L){
		//ecrit dans le fichier dont chaque ligne correspond au format indiquer
		fprintf(fic,"%d %s %s", b->L->num, b->L->titre, b->L->auteur);
		fputc('\n',fic);
		b->L = b->L->suiv;
	}
	//fermeture du fichier
	fclose(fic);
}
		