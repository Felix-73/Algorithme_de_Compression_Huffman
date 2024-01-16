# Algorithme de Compression Huffman

## Introduction
Bienvenue dans l'algorithme de compression Huffman, implémenté sur un microcontrôleur STM32F446. Ce programme démontre le processus de compression d'une chaîne de caractères à l'aide de l'algorithme de Huffman.

## Fonctionnalités

- Initialisation du GPIO, USART et SysTick pour le microcontrôleur STM32F446.
- Interface utilisateur via la liaison série.
- Calcul des occurrences des caractères dans le texte.
- Création de l'arbre de Huffman à partir des occurrences.
- Parcours de l'arbre de Huffman pour générer les codes de compression.

## Comment utiliser le programme

1. Connectez le microcontrôleur STM32F446.
2. Compilez et téléversez le programme sur le microcontrôleur.
3. L'interface utilisateur affichera des informations sur le texte à encoder.
4. Les étapes de compression seront exécutées, et les résultats seront affichés.

## Fichiers inclus

- `main.c`: Contient la fonction principale du programme.
- `gpio.h`, `usart.h`, `timer.h`, `occurence.h`, `huffman.h`: Fichiers d'en-tête pour les différentes fonctionnalités.
- `gpio.c`, `usart.c`, `timer.c`, `occurence.c`, `huffman.c`: Implémentations des fonctions correspondantes.

## Dépendances

- Bibliothèque STM32F446xx.
- En-têtes standard C (`stdint.h`, `stdio.h`, `stdbool.h`).

## Auteur
Félix Gueydan

## Licence
Ce programme est distribué sous la licence [Licence X]. Consultez le fichier LICENCE pour plus de détails.
