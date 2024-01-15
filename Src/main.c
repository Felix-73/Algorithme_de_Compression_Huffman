#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "occurence.h"
#include "huffman.h"



int main(void)
{
	GPIO_Init();
	USART2_Init();
	SYSTICK_Init();
	printf("*******************************************\r\n");
	printf("Bienvenue dans l'algorithme de compression\r\n");
	printf("*******************************************\r\n\n");
	uint32_t tabCaractere[256];
	uint8_t texte[] = "bbbbiiioo";


	// Calcul des occurences
	occurence(texte, tabCaractere);


	// Tableau d'arbre de Huffman
	struct noeud* arbreHuffman[256];

	// Création des feuilles de l'arbre
	creerFeuille(arbreHuffman, tabCaractere);


	// Libérer la mémoire allouée pour les feuilles de l'arbre
	for (int i = 0; i < 256; i++) {
		free(arbreHuffman[i]);
	}
	return 0;
}
