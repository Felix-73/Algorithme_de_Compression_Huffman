#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h" // Inclure le fichier d'en-tête

// Fonction pour créer une feuille de l'arbre de Huffman
void creerFeuille(struct noeud* arbre[256], uint32_t tab[256],_Bool debug) {
	uint32_t j=0;
    for (int i = 0; i < 256; i++) {
        if (tab[i] > 0) {
            // Allouer de la mémoire pour une nouvelle structure noeud (sizeof met sur 4 octets)
            arbre[j] = (struct noeud*)malloc(sizeof(struct noeud));
            if(NULL !=arbre[j]){
				// Initialiser les champs de la structure
				arbre[j]->c =i;
				arbre[j]->occurence = tab[i];
				arbre[j]->code = 0;
				arbre[j]->tailleCode = 0;
				arbre[j]->gauche = NULL;
				arbre[j]->droite = NULL;
            }
           j++;
        }
	}
}

void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille) {
    printf("Affichage du tableau de l'arbre de Huffman :\r\n");
    for (uint32_t i = 0; i < taille; i++) {
            printf("struct noeud\r\n"
                   "caractere='%c'\r\n"
                   "occurrence=%u\r\n"
                   "code=%u\r\n"
                   "tailleCode=%u\r\n"
                   "gauche=%p\r\n"
                   "droite=%p\r\n\n",
                   arbre[i]->c, arbre[i]->occurence, arbre[i]->code, arbre[i]->tailleCode,
                   (void*)arbre[i]->gauche, (void*)arbre[i]->droite);
    }
}

// Fonction pour trier l'arbre de Huffman par ordre croissant d'occurrences
void triArbre(struct noeud* arbre[256], uint32_t taille) {
	struct noeud* tampon;
    for (uint32_t i = 0; i < taille; i++) {
    	for (uint32_t j = i+1; j < taille; j++) {
    		if(arbre[j] ->occurence<arbre[i] ->occurence){
    			tampon= arbre[i];
    			arbre[i]=arbre[j];
    			arbre[j]=tampon;
    		}
    	}
    }
}
