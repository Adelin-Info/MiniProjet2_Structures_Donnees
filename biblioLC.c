#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioLC.h"


Livre* creer_livre( int num, char* titre, char* auteur){
	Livre* L=(Livre*)malloc(sizeof(Livre));
	if (L == NULL) {
		printf("Erreur d'allocation");
		return NULL;
    }
	//initialisation des données et du pointeur
	L->num = num;
	L->titre = strdup(titre);    //strdup commande permettant d'allouer une chaine de caracteres
	L->auteur = strdup(auteur);
	L->suiv = NULL;
	return L;
}

void liberer_livre(Livre* l){
	// desalloue les données puis le livre
	free(l->titre);
	free(l->auteur);
	free(l);
}

Biblio* creer_biblio(){
	Biblio* B = (Biblio*)malloc(sizeof(Biblio));
	if (B == NULL){
		printf("Erreur allocation");
		return NULL;
	}
	// initialisation du pointeur
	B->L = NULL;
	return B;
}

void liberer_biblio(Biblio* b){
	// desalloue chaque livre puis la bibliotheque
	while (b->L != NULL){
		Livre* l = b->L;
		b->L = b->L->suiv;
		liberer_livre(l);
	}
	free(b);
}

void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
	Livre* livre = creer_livre(num,titre,auteur);
	livre->suiv = b->L;
	b->L = livre;
}

void affichage_livre(Livre* l){
	printf("%d %s %s \n", l->num, l->titre, l->auteur);
}

void affichage_biblio(Biblio* b){
	Livre* l = b->L;
	while (l != NULL){
		affichage_livre(l);
		l = l->suiv;
	}
	printf("\n");
}

void recherche_numero(Biblio* b, int n){
	Livre* l = b->L;
	while (l != NULL){
		if (l->num == n){
			affichage_livre(l);
			return;
		}
		l = l->suiv;
	}
	printf("L'ouvrage n'est pas dans la bibliothèque\n");
}

void recherche_titre(Biblio* b, char* t){
	Livre* l = b->L;
	while (l != NULL){
		if (strcmp(l->titre, t) == 0){   // strcmp compare deux chaines de caractères et renvoi 0 si elles sont identiques
			affichage_livre(l);
			return;
		}
		l = l->suiv;
	}
	printf("L'ouvrage n'est pas dans la bibliothèque\n");
}

Biblio* recherche_auteur(Biblio* b, char* a){
	Biblio* res = creer_biblio();
	Livre* l = b->L;
	while (l != NULL){
		if (strcmp(l->auteur, a)==0){
			inserer_en_tete(res, l->num, l->titre, l->auteur);
		}
		l = l->suiv;
	}
	if(res->L == NULL){
		printf("Aucun ouvrage de cette auteur est présent dans la bibliothèque\n");
		return res;
	}
	else{
		return res;
	}
}

Biblio* suppression_ouvrage(Biblio* b, int n, char* t, char* a){
	Livre* prec;
	Livre* s;
	if ( b->L != NULL){
		s = b->L;
		
		// supprimer en tete de liste 
		if ((s->num == n) && (strcmp(s->titre, t) == 0) && (strcmp(s->auteur, a) == 0)){
			b->L = s->suiv;
			free(s);
			return b;
		}
		
		// supprimer en fin ou au milieu de liste
		else{
			prec = b->L;
			s = s->suiv;
			while (s != NULL){
				if ((s->num == n) && (strcmp(s->titre, t) == 0) && (strcmp(s->auteur, a) == 0)){
					prec->suiv = s->suiv;
					liberer_livre(s);
					return b;
				}
				prec = prec->suiv;
				s = s->suiv;
			}
			printf("L'ouvrage n'est pas dans la bibliothèque");
		}
	}
	return b;
}

Biblio* fusion_biblio(Biblio* b1, Biblio* b2){
	Livre* l1 = b1->L;
	while (l1->suiv != NULL){
		l1 = l1->suiv;
	}
	l1->suiv = b2->L; //le dernier livre de b1 pointe sur le premier livre de b2 
	b2->L = NULL;     
	free(b2);
	return b1;
}

Biblio* recherche_plusieurs_exemplaires(Biblio* b, int n){
	Biblio* res = creer_biblio();
	Livre* l1 = b->L;
	Livre* l2;
	
	//allocation et initialisation d'un tableau dont chaque case contient 0
	int* t = (int*)calloc(n, sizeof(int));
	
	//teste si l'allocation à marcher
	if (t==NULL){
		printf("Erreur d'allocation");
		exit(-1);
	}
	
	while (l1->suiv != NULL){
		l2 = l1->suiv;
		while (l2->suiv != NULL){
			if ((strcmp(l1->titre,l2->titre)==0) && (strcmp(l1->auteur,l2->auteur)==0)){
				if (t[l2->num]==0){
					inserer_en_tete(res,l2->num,l2->titre,l2->auteur);
					t[l2->num]=1;
				}
				if (t[l1->num]==0){
					inserer_en_tete(res,l1->num,l1->titre,l1->auteur);
					t[l1->num]=1;
				}
			}
			l2 = l2->suiv;
		}
		l1 = l1->suiv;
	}
	free(t);
	
	if (res->L == NULL){
		printf("Il n'y a pas plusieurs exemplaires d'ouvrages dans la bibliothèque\n");
		return res;
	}
	else {
		return res;
	}
}