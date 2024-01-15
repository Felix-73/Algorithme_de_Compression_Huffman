// huffman.h

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure pour représenter un nœud de l'arbre de Huffman
struct noeud {
    uint8_t c;           // Caractère initial
    uint32_t occurence;   // Nombre d'occurrences
    uint32_t code;        // Code binaire dans l'arbre
    uint32_t tailleCode;  // Nombre de bits du code
    struct noeud *gauche, *droite; // Lien vers les nœuds suivants
};

// Fonction pour créer une feuille de l'arbre de Huffman
void creerFeuille(struct noeud* arbre[256], uint32_t tab[256],_Bool debug);
void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille);
void triArbre(struct noeud* arbre[256], uint32_t taille);

#endif // HUFFMAN_H
