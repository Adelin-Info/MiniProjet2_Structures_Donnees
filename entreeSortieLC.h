#ifndef _ENTREESORTIELC_H_
#define _ENTREESORTIELC_H_

#include "biblioLC.h"

//Lit dans un fichier les n premieres lignes et les stocke dans une bibliothèque
Biblio* charger_n_entrees(char* nomfic, int n);

// Ecrit dans un fichier une bibliothèque
void enregistrer_biblio(Biblio* b, char* nomfic);

#endif