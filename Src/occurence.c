#include <stdint.h>

void occurence(uint8_t* chaine, uint32_t tab[256]) {
    // Initialiser le tableau à zéro
    for (int i = 0; i < 256; i++) {
        tab[i] = 0;
    }
    // Parcourir la chaîne de caractères
    while (*chaine != '\0') {
        // Incrémenter le compteur du caractère correspondant dans le tableau
        tab[*chaine]++;
        chaine++;
    }
}

void afficherTableau(const int tableau[], int taille) {
    printf("[");
    for (int i = 0; i < taille; i++) {
        printf("%d", tableau[i]);

        // Ajouter une virgule après chaque élément, sauf le dernier
        if (i < taille - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}
