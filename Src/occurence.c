#include <stdint.h>

void occurence(uint8_t* chaine, uint32_t tab[256]) {
    // Initialiser le tableau à zéro
    for (int i = 0; i < 256; i++) {
        tab[i] = 0;
    }
    // Parcour la chaîne de caractères
    while (*chaine != '\0') {
        tab[*chaine]++;			// Incrémenter le compteur du caractère correspondant dans le tableau
        chaine++;				// Compteur des occurences
    }
}
