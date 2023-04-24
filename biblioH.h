#ifndef _BIBLIO_H_
#define _BIBLIO_H_

//taille max de la table de hachage
#define TAILLE_MAX 100 

// Definition du type LivreH
typedef struct livreh{
	int clef;
	int num;
	char* titre;
	char* auteur;
	struct livreh *suivant;
} LivreH;

// Definition du type BiblioH
typedef struct table{
	int nE;
	int m;
	LivreH** T;
}BiblioH;


// Somme de chaque lettre d'une chaine de caractère 
int fonctionClef(char* auteur);

// Allocation et initialisation d'une variable de type LivreH
LivreH* creer_livreH(int num, char* titre, char* auteur);

// Desallocation d'une variable de type LivreH
void liberer_livreH(LivreH* l);

// Allocation et initialisation d'une variable de type BiblioH
BiblioH* creer_biblioH(int m);

// Desallocation d'une variable de type BiblioH
void liberer_biblioH(BiblioH* b);

// Creation d'un cle hachée
int fonctionHachage(int cle, int m);

// Insertion d'un livre dans une table de hachage
void inserer(BiblioH* b, int num, char* titre, char* auteur);

// Afficher un livre
void affichage_livreH(LivreH* l);

// Afficher une bibliotheque
void affichage_biblioH(BiblioH* b);

//Rechercher un livre par rapport a son numero dans une table de hachage
void recherche_numeroH(BiblioH* b, int n);

//Rechercher un livre par rapport a son titre dans une table de hachage
void recherche_titreH(BiblioH* b, char* t);

//Renvoi tout les livres d'un même auteur
BiblioH* recherche_auteurH(BiblioH* b, char* a);

//Supprime un livre de la bibliothèque 
BiblioH* suppressionH(BiblioH* b, int n, char* t, char* a);

//Ajoute la deuxieme bibliothèque à la première
BiblioH* fusionH(BiblioH* b1, BiblioH* b2);

//Renvoi les livres en plusieurs exemplaires dans la bibliothèque
BiblioH* recherche_plusieurs_exemplairesH(BiblioH* b,int n);

#endif