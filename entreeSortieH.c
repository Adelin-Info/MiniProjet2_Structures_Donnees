#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entreeSortieH.h"

BiblioH* chargerH(char* nomfic, int n){
	int i=0;
	int num;
	char ligne[50];
	char titre[50];
	char auteur[50];
	BiblioH* B = creer_biblioH(TAILLE_MAX);
	FILE* fic = fopen(nomfic, "r");
	if (fic == NULL){
		printf("Probleme d'ouverture du fichier");
		exit(-1);
	}
	while ((i<n) && (fgets(ligne, 50, fic)!=NULL)){
		if (sscanf(ligne, "%d %s %s", &num, titre, auteur) == 3){
				inserer(B,num,titre,auteur);
		}
		else {
			printf("Format de ligne incorrect");
			free(B);
			exit(-1);
		}
		i=i+1;
	}
	fclose(fic);
	return B;
}


void enregistrerH(BiblioH* b, char* nomfic){
	int i;
	LivreH** t = b->T;
	FILE* fic = fopen(nomfic, "w");
	if (fic == NULL){
		printf("Probleme d'ouverture du fichier");
		exit(-1);
	}
	for (i=0; i<b->m; i++){
		while (t[i] != NULL){
		fprintf(fic,"%d %s %s", t[i]->num, t[i]->titre, t[i]->auteur);
		fputc('\n',fic);
		t[i] = t[i]->suivant;
		}
	}
	fclose(fic);
}