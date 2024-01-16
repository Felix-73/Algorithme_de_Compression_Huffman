/*
 * huffman.h
 *
 *  Created on: Jan 15, 2024
 *      Author: Felix
 */
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

// Fonctions
void creerFeuille(struct noeud* arbre[256], uint32_t tab[256],_Bool debug);
void afficherTabArbreHuffman(struct noeud* arbre[256], uint32_t taille);
void triArbre(struct noeud* arbre[256], uint32_t taille);
struct noeud* construireArbreHuffman(struct noeud* arbre[256], int n);
void afficherArbreHuffman(struct noeud* racine);
void parcourirArbre(struct noeud* ptrNoeud);
void libererArbre(struct noeud* ptrNoeud);
void printBinary(uint32_t num, int size);
void creerCode(struct noeud* ptrNoeud, uint32_t code, uint32_t taille);
#endif // HUFFMAN_H
