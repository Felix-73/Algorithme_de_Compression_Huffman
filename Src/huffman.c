#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h"

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

// Fonction pour regrouper les feuilles dans un arbre de Huffman
struct noeud* construireArbreHuffman(struct noeud* arbre[256], int n) {
    while (n > 1) {
        // Trouver les deux nœuds avec les occurrences les plus faibles
        int min1 = 0, min2 = 1;
        if (arbre[min1]->occurence > arbre[min2]->occurence) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < n; i++) {
            if (arbre[i]->occurence < arbre[min1]->occurence) {
                min2 = min1;
                min1 = i;
            } else if (arbre[i]->occurence < arbre[min2]->occurence) {
                min2 = i;
            }
        }

        // Créer un nouveau nœud avec les deux nœuds trouvés comme fils
        struct noeud* nouveauNoeud = (struct noeud*)malloc(sizeof(struct noeud));
        if (NULL != nouveauNoeud) {
            nouveauNoeud->occurence = arbre[min1]->occurence + arbre[min2]->occurence;
            nouveauNoeud->gauche = arbre[min1];
            nouveauNoeud->droite = arbre[min2];

            // Mettre à jour le tableau en éliminant les deux nœuds regroupés et en ajoutant le nouveau
            arbre[min1] = nouveauNoeud;
            arbre[min2] = arbre[n - 1];
            n--;
        }
    }

    // Le dernier élément restant est la racine de l'arbre
    return arbre[0];
}

// Fonction pour afficher l'arbre de Huffman (parcours préfixe)
void afficherArbreHuffman(struct noeud* racine) {
    if (racine != NULL) {
        printf("Caractère: %c, Occurrence: %u\r\n", racine->c, racine->occurence);
        afficherArbreHuffman(racine->gauche);
        afficherArbreHuffman(racine->droite);
    }
}
