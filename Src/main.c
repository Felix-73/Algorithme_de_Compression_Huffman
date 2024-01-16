/**
 * @file main.c
 * @brief Main program file for Huffman Compression Algorithm on STM32F446 microcontroller.
 * @author Félix
 */

#include <stdint.h>
#include <stm32f446xx.h>
#include <stdio.h>
#include "main.h"
#include "gpio.h"
#include "usart.h"
#include "timer.h"
#include "occurence.h"
#include "huffman.h"
#include <stdbool.h>

/**
 * @brief Main function
 * @return 0 upon successful execution
 */
int main(void)
{
    // Initialize GPIO, USART, and SysTick
    GPIO_Init();
    USART2_Init();
    SYSTICK_Init();

    // Display welcome message
    printf("\n\n\n*******************************************\r\n");
    printf("Bienvenue dans l'algorithme de compression\r\n");
    printf("*******************************************\r\n\n");

    // Initialize variables
    uint32_t tabCaractere[256];
    uint8_t texte[] = "aaaabccc";
    int caracterePresent[256] = {0};
    int nbCaracteresDifferents = 0;

    // display the original text
    printf("Contenu du texte : ");
    for (int i = 0; texte[i] != '\0'; i++) {
        printf("%c", texte[i]);
    }
    printf("\r\n");

    for (int i = 0; texte[i] != '\0'; i++) {
        if (caracterePresent[texte[i]] == 0) {
            caracterePresent[texte[i]] = 1;
            nbCaracteresDifferents++;
        }
    }

    printf("votre chaine de caractères à %d caractères differents\r\n\n", nbCaracteresDifferents);


    // Calculate character occurrences
    occurence(texte, tabCaractere);


    // Array of Huffman tree nodes
    struct noeud* arbreHuffman[256];

    // Create leaves of the Huffman tree
    creerFeuille(arbreHuffman, tabCaractere, true);

    // Display information for the first three elements of the array
    printf("				~~~~ Avant le tri ~~~~\r\n");
    afficherTabArbreHuffman(arbreHuffman, nbCaracteresDifferents);

    // Sort the array
    triArbre(arbreHuffman, 3);

    // Display information after sorting
    printf("\n				~~~~ Après le tri ~~~~ \r\n");
    afficherTabArbreHuffman(arbreHuffman, nbCaracteresDifferents);

    struct noeud* racineArbreHuffman = construireArbreHuffman(arbreHuffman, 3);

    printf("----- Arbre de Huffman -----\r\n");
    afficherArbreHuffman(racineArbreHuffman);

    // Free memory allocated for the leaves of the tree
    for (int i = 0; i < 256; i++) {
        free(arbreHuffman[i]);
    }

    return 0;
}
