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

// GitHub: https://github.com/FelixGueyd/Gueydan.git

int main(void)
{
// -------------------------------- INITIALISATION --------------------------------------------------

    // Initialisation du GPIO, USART, et SysTick pour le microcontroller STM32F446
    GPIO_Init();
    USART2_Init();
    SYSTICK_Init();

    // Interface utilisateur via la liaison série
    printf("\n\n\n\r#---------------------------------------------------------------------------------------------#\r\n");
    printf("                             Bienvenue dans l'algorithme de compression\r\n");
    printf("#---------------------------------------------------------------------------------------------#\r\n\n");

    // Initialisation du code à compresser
    uint32_t tabCaractere[256];
    uint8_t texte[] = "aaaaabbbbccdde";
    int caracterePresent[256] = {0};
    int nbCaracteresDifferents = 0;

    // Affichage à l'utilisateur sa chaine de caractères
    printf("Contenu du texte à encoder: ");
    for (int i = 0; texte[i] != '\0'; i++) {
        printf("%c", texte[i]);
    }
    printf("\r\n");
    // Calcul du nombre de cactères differents et l'affiche
    for (int i = 0; texte[i] != '\0'; i++) {
        if (caracterePresent[texte[i]] == 0) {
            caracterePresent[texte[i]] = 1;
            nbCaracteresDifferents++;
        }
    }
    printf("votre chaine de caractères à %d caractères differents\r\n\n", nbCaracteresDifferents);


// -------------------------------- COMPRESSION --------------------------------------------------

    occurence(texte, tabCaractere);    									// Calcul des occurences dans notre texte

    struct noeud* arbreHuffman[256];    								// Declaration de notre structure noeux

    creerFeuille(arbreHuffman, tabCaractere, true);     				// Creation des feuilles de notre arbre

//    printf("				~~~~ Avant le tri ~~~~\r\n");
//    afficherTabArbreHuffman(arbreHuffman, nbCaracteresDifferents);		// Fonction de DEBUG

    triArbre(arbreHuffman, nbCaracteresDifferents);						// Range les noeuds dans l'ordre des occurrences ( + petit au plus grand )

//    printf("\n				~~~~ Après le tri ~~~~ \r\n");
//    afficherTabArbreHuffman(arbreHuffman, nbCaracteresDifferents);		// Fonction pour DEBUG

    struct noeud* racineArbreHuffman = construireArbreHuffman(arbreHuffman, nbCaracteresDifferents ); //declaration de notre racine/arbre

//    printf("----- Arbre de Huffman -----\r\n");
//    afficherArbreHuffman(racineArbreHuffman);								//	Fonction de DEBUG

    printf("\n -------------------- Parcourir l'arbre de Huffman --------------------\r\n\n");
    parcourirArbre(racineArbreHuffman);    // Appeler la fonction pour parcourir l'arbre
    libererArbre(racineArbreHuffman);    // Libérer l'espace utilisé pour l'arbre

    printf("\n -------------------- Creation du code --------------------\r\n\n");
    creerCode(racineArbreHuffman, 0, 0);



    for (int i = 0; i < 256; i++) {											// Libere l'espace reservé
        free(arbreHuffman[i]);
    }

    return 0;
}
