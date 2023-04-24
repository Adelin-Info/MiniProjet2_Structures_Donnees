#ifndef _BIBLIOLC_H_
#define _BIBLIOLC_H_

//Définition du type Livre
typedef struct livre{
	int num;
	char* titre;
	char* auteur;
	struct livre *suiv;
} Livre;

// Définition du type Biblio
typedef struct{
	Livre *L;
} Biblio;

// Allocation et Initialisation d'une variable de type Livre
Livre* creer_livre(int num, char* titre, char* auteur);

// Desallocation d' une variable de type Livre
void liberer_livre(Livre* l);

// Allocation et Initialisation d'une variable de type Biblio
Biblio* creer_biblio();

// Desallocation d'une variable de type Livre
void liberer_biblio(Biblio* b);

// Insertion au début d'une Liste Chainée
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);

// Afficher un livre 
void affichage_livre(Livre* l);

// Afficher une bibliothèque
void affichage_biblio(Biblio* b);

// Rechercher un livre par rapport a son numero dans une liste chainée
void recherche_numero(Biblio* b, int n);

// Rechercher un livre par rapport a son titre dans une liste chainée
void recherche_titre(Biblio* b, char* t);

// Renvoi tout les livres d'un même auteur
Biblio* recherche_auteur(Biblio* b, char* a);

// Supprime un livre de la bibliothèque
Biblio* suppression_ouvrage(Biblio* b, int n, char* t, char* a);

// Ajoute la deuxieme bibliothèque à la première
Biblio* fusion_biblio(Biblio* b1, Biblio* b2);

// Renvoi tout les livres en plusieurs exemplaires dans la bibliothèque
Biblio* recherche_plusieurs_exemplaires(Biblio* b, int n);

#endif	