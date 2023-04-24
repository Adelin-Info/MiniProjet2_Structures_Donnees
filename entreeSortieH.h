#ifndef _ENTREESORTIE_H_
#define _ENTREESORTIE_H_

#include "biblioH.h"

//Lit dans un fichier les n premieres lignes et les stocke dans une bibliothèque
BiblioH* chargerH(char* nomfic, int n);

//Ecrit dans un fichier une bibliothèqu
void enregistrerH(BiblioH* b, char* nomfic);

#endif