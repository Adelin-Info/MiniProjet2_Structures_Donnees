#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "biblioH.h"


int fonctionClef(char* auteur){
	int i;
	int cle=0;
	for (i=0; auteur[i]!='\0'; i++){
		cle+=(int) auteur[i];
	}
	return cle;
}

LivreH* creer_livreH(int num, char* titre, char* auteur){
	LivreH* L = (LivreH*)malloc(sizeof(LivreH));
	if (L == NULL) {
		return NULL;
    }
	L->clef = fonctionClef(auteur);
	L->num = num;
	L->titre = strdup(titre);
	L->auteur = strdup(auteur);
	L->suivant = NULL;
	return L;
}

void liberer_livreH(LivreH* l){
	free(l->titre);
	free(l->auteur);
	free(l);
}

BiblioH* creer_biblioH(int m){
	BiblioH* B = (BiblioH*)malloc(sizeof(BiblioH));
	if (B == NULL){
		printf("Erreur allocation");
		return NULL;
	}
	B->nE = 0;
	B->m = m;
	B->T = (LivreH**)malloc(m*sizeof(LivreH*));
	if (B->T == NULL){
		printf("Erreur allocation");
		free(B);
		return NULL;
	}
	for (int i=0; i<m; i++){
		B->T[i] = NULL;
	}
	return B;
}

void liberer_biblioH(BiblioH* b){
	LivreH** t = b->T;
	LivreH* temp;
	int i;
	for(i=0; i<b->m; i++){
		while( t[i] != NULL){
			temp = t[i]->suivant;
			liberer_livreH(t[i]);
			t[i] = temp;
		}
	}
	free(t);
	free(b);
}

int fonctionHachage(int cle, int m){
	double A = (sqrt(5)-1)/2;
	int p;
	p = (int) (cle*A);
	return (int) (m*cle*A - m*p); // développement de la formule donnée 
}

void inserer(BiblioH* b, int num, char* titre, char* auteur){
	LivreH* l = creer_livreH(num, titre, auteur);
	int cleH = fonctionHachage(l->clef, b->m);
	int i;
	for (i=0; i<b->m; i++){
		if (i==cleH){
			l->suivant = b->T[i];
			b->T[i] = l;
		}
	}
}

void affichage_livreH(LivreH* l){
	printf("%d %s %s\n",l->num, l->titre, l->auteur);
}

void affichage_biblioH(BiblioH* b){
	LivreH* l;
	int i;
	for (i=0; i<b->m; i++){
		l = b->T[i];
		while(l != NULL){
			affichage_livreH(l);
			l = l->suivant;
		}
	}
}

void recherche_numeroH(BiblioH* b, int n){
	LivreH* l;
	LivreH** t = b->T;
	int i;
	for (i=0; i<b->m; i++){
		if (t[i] != NULL){
			l = t[i];
			while (l != NULL){
				if (l->num == n){
					affichage_livreH(l);
					return;
				}
				l = l->suivant;
			}
		}
	}
	printf("L'ouvrage n'est pas dans la bibliothèque\n");
	return;
}

void recherche_titreH(BiblioH* b, char* t){
	LivreH* l;
	LivreH** tab = b->T;
	int i;
	for (i=0; i<b->m; i++){
		if (tab[i] != NULL){
			l = tab[i];
			while (l != NULL){
				if (strcmp(l->titre,t)==0){
					affichage_livreH(l);
					return;
			    }
				l = l->suivant;
			}
		}
	}
	printf("L'ouvrage n'est pas dans la bibliothèque\n");
	return;
}

BiblioH* recherche_auteurH(BiblioH* b, char* a){
	BiblioH* res = creer_biblioH(b->m);
	int cle = fonctionClef(a);
	int cleH = fonctionHachage(cle,b->m);
	LivreH* l = b->T[cleH]; 
	while (l != NULL){
		if (strcmp(l->auteur,a)==0){
			inserer(res, l->num, l->titre, l->auteur);
		}
		l = l->suivant;
	}
	return res;
}

BiblioH* suppressionH(BiblioH* b, int n, char* t, char* a){
	int cleH = fonctionHachage(fonctionClef(a), b->m);
	LivreH* prec;
	LivreH* s;
	if (b->T[cleH] != NULL){
		s = b->T[cleH];
		
		// supprimer en tete de liste 
		if ((s->num == n) && (strcmp(s->titre, t)==0) && (strcmp(s->auteur,a)==0)){
			b->T[cleH] = s->suivant;
			free(s);
			return b;
		}
		
		// supprimer en fin ou au milieu de liste
		else{
			prec = b->T[cleH];
			s = s->suivant;
			while (s != NULL){
				if ((s->num == n) && (strcmp(s->titre, t)==0) && (strcmp(s->auteur,a)==0)){
					prec->suivant = s->suivant;
					liberer_livreH(s);
					return b;
				}
				prec = prec->suivant;
				s = s->suivant;
			}
			printf("L'ouvrage n'est pas dans la bibliothèque\n");
		}
	}
	return b;
}

BiblioH* fusionH(BiblioH* b1, BiblioH* b2){
	LivreH** t1 = b1->T;
	LivreH** t2 = b2->T;
	LivreH* l;
	int i;
	for (i=0; i<b1->m; i++){
		if (t1[i] == NULL){
			t1[i] = t2[i];
			t2[i] = NULL;
		}
		else{
			l = t1[i];
			while(l->suivant != NULL){
				l = l->suivant;
			}
			l->suivant = t2[i];
			t2[i] = NULL;
		}
	}
	liberer_biblioH(b2);
	return b1;
}

BiblioH* recherche_plusieurs_exemplairesH(BiblioH* b,int n){
	BiblioH* res = creer_biblioH(b->m);
	// allocation et initialisation d'un tableau dont chaque case contient 0
	int* t=(int*)calloc(n, sizeof(int));
	int i;
	LivreH* l1;
	LivreH* l2;
	
	//teste si l'allocation à marcher
	if (t==NULL){
		printf("Erreur allocation");
		exit(-1);
	}
	for(i=0; i<b->m; i++){
		l1 = b->T[i];
		while (l1 != NULL){
			l2 = l1->suivant;
			while (l2 != NULL){
				if ((strcmp(l1->titre,l2->titre)==0) && (strcmp(l1->auteur,l2->auteur)==0)){
					if (t[l2->num]==0){
						inserer(res,l2->num,l2->titre,l2->auteur);
						t[l2->num]=1;
					}
					if (t[l1->num]==0){
						inserer(res,l1->num,l1->titre,l1->auteur);
						t[l1->num]=1;
					}
				}
				l2 = l2->suivant;
			}
			l1 = l1->suivant;
		}
	}
	free(t);
	return res;
}
			
	
		
	