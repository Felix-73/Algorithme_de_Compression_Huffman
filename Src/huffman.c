#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "huffman.h" // Inclure le fichier d'en-tête

// Fonction pour créer une feuille de l'arbre de Huffman
void creerFeuille(struct noeud* arbre[256], uint32_t tab[256]) {
    for (int i = 0; i < 256; i++) {
        if (tab[i] > 0) {
            // Allouer de la mémoire pour une nouvelle structure noeud (sizeof met sur 4 octets)
            arbre[i] = (struct noeud*)malloc(sizeof(struct noeud));

            // Initialiser les champs de la structure
            arbre[i]->c = (uint8_t)i;
            arbre[i]->occurence = tab[i];
            arbre[i]->code = 0;
            arbre[i]->tailleCode = 0;
            arbre[i]->gauche = NULL;
            arbre[i]->droite = NULL;

            // Affichage dans la liaison serie
			printf("struct noeud\r\ncaractere='%c'\r\noccurrence=%u\r\ncode=%u\r\ntailleCode=%u\r\n"
				   "gauche=%p\r\ndroite=%p\r\n\n",
				   arbre[i]->c, arbre[i]->occurence, arbre[i]->code, arbre[i]->tailleCode,
				   (void*)arbre[i]->gauche, (void*)arbre[i]->droite);
		} else {
			// Si l'occurrence est nulle, initialiser le pointeur à NULL
			arbre[i] = NULL;
		}
	}
}
