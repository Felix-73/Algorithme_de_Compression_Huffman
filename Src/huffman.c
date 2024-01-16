#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h"

// CREATION DE TOUTES LES FEUILLES DE L'ARBRE DE HUFFMAN
void creerFeuille(struct noeud* arbre[256], uint32_t tab[256],_Bool debug) {
	uint32_t j=0;
    for (int i = 0; i < 256; i++) {
        if (tab[i] > 0) {
            // Alloue de la mémoire pour une nouvelle structure noeud (sizeof met sur 4 octets)
            arbre[j] = (struct noeud*)malloc(sizeof(struct noeud));
            if(NULL !=arbre[j]){
				// Initialisation des champs de la structure
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

// FONCTION DE DEBUG POUR VISUALISER TOUTES LES FEUILLES CREES
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

// FONCTION DE TRI DES FEUILLES EN FONCTION DE LEURS OCCURRENCES
void triArbre(struct noeud* arbre[256], uint32_t taille) {
	struct noeud* tampon;									 //declaration d'une structure tampon pour deplacer les feuilles
    for (uint32_t i = 0; i < taille; i++) {					 //On boucle une première fois pour prendre l'intégralité des feuilles
    	for (uint32_t j = i+1; j < taille; j++) {			 //On reboucle une deuxième fois pour faire comparer les feuilles
    		if(arbre[j] ->occurence<arbre[i] ->occurence){	 //Utilisation du tampon pour mettre dans l'ordre
    			tampon= arbre[i];
    			arbre[i]=arbre[j];
    			arbre[j]=tampon;
    		}
    	}
    }
}

// FONCTION QUI REGROUPE LES NOEUX DANS UN ARBRE ET RETOURNE LA RACINE
struct noeud* construireArbreHuffman(struct noeud* arbre[256], int n) {
    while (n > 1) {
        // Trouve les deux nœuds avec les occurrences les plus faibles
        int min1 = 0, min2 = 1;
        if (arbre[min1]->occurence > arbre[min2]->occurence) {  //on s'assure que min1 pointe vers le nœud avec l'occurrence la plus faible
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < n; i++) {							// Cette boucle examine les occurrences de tous les nœuds restants dans le tableau
            if (arbre[i]->occurence < arbre[min1]->occurence) {
                min2 = min1;
                min1 = i;
            } else if (arbre[i]->occurence < arbre[min2]->occurence) {
                min2 = i;
            }
        }
        // Créer un nouveau nœud avec les deux nœuds trouvés comme fils
        struct noeud* nouveauNoeud = (struct noeud*)malloc(sizeof(struct noeud)); //declaration de notre arbre
        if (NULL != nouveauNoeud) {
            nouveauNoeud->occurence = arbre[min1]->occurence + arbre[min2]->occurence;
            nouveauNoeud->gauche = arbre[min1];
            nouveauNoeud->droite = arbre[min2];

            // Mise à jour du tableau en éliminant les deux nœuds regroupés et en ajoutant le nouveau
            arbre[min1] = nouveauNoeud;
            arbre[min2] = arbre[n - 1];
            n--;
        }
    }

    // retourne la racine de l'arbre
    return arbre[0];
}

// FONCTION DE DEBUG POUR AFFICHER L'ARBRE
void afficherArbreHuffman(struct noeud* racine) {
    if (racine != NULL) {
        printf("Caractère: %c, Occurrence: %u\r\n", racine->c, racine->occurence);
        afficherArbreHuffman(racine->gauche);
        afficherArbreHuffman(racine->droite);
    }
}

// FONCTION POUR PARCOURIR L'ARBRE DE HUFFMAN
void parcourirArbre(struct noeud* ptrNoeud) {
    if (ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL) {
        printf("Feuille - Caractère: %c, Occurrence: %u\r\n", ptrNoeud->c, ptrNoeud->occurence);
    } else {
        printf("Nœud - Occurrence: %u\r\n", ptrNoeud->occurence);
        parcourirArbre(ptrNoeud->droite); // On va à droite
        parcourirArbre(ptrNoeud->gauche); // On va à gauche
    }
}


//FONCTION POUR LIBERER L'ESPACE UTILISE POUR L'ARBRE
void libererArbre(struct noeud* ptrNoeud) {
    if (ptrNoeud != NULL) {
        libererArbre(ptrNoeud->droite);
        libererArbre(ptrNoeud->gauche);
        free(ptrNoeud);
    }
}

// FONCTION POUR CONVERTIR DECIMAL EN BINAIRE
void printBinary(uint32_t num, int size) {
    for (int i = size - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

// FONCTION POUR CREER LE CODE DE L'ARBRE DE HUFFMAN
void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille) {
    if (ptrNoeud->droite == NULL && ptrNoeud->gauche == NULL) {
        ptrNoeud->tailleCode = taille;
        ptrNoeud->code = code;

        // Imprimer le caractère, le code en décimal, et le code en binaire
        printf("%c \t code : %d \t taille : %d \t binaire : ", ptrNoeud->c, ptrNoeud->code, ptrNoeud->tailleCode);
        printBinary(ptrNoeud->code, ptrNoeud->tailleCode);
        printf("\r\n");
    } else {
        // On va à droite (on injecte un 0 à droite dans le code)
        creerCode(ptrNoeud->droite, code << 1, taille + 1);
        // On va à gauche (on injecte un 1 à droite)
        creerCode(ptrNoeud->gauche, (code << 1) + 1, taille + 1);
    }
}


