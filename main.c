#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "levenshtein.h"

char* choose_word(int length)
{
    char* words[10] = {"", "a", "to", "dog", "bird", "apple", "elephant", "monkey", "inventa", "chirurgie"};
    int num_words = 10;

    // Alegem un index aleatoriu pentru cuvântul de lungime specificată
    int index = rand() % num_words;

    // Verificăm dacă lungimea cuvântului corespunde cu lungimea specificată
    while (strlen(words[index]) != length)
    {
        index = rand() % num_words;
    }

    return words[index];
}

int main()
{
    srand(time(NULL));

    // Cerem utilizatorului să introducă un număr între 0 și 9
    int num_letters;
    char* first_word;

    do
    {
        printf("Daca doriti deja o functie predefinita, specificati dimensiunea functiei (0-9) sau daca doriti sa introduceti dumneavoastra tastati 10: ");
        char input_num[256]; // Buffer pentru citirea numărului de la tastatură
        fgets(input_num, sizeof(input_num), stdin);
        num_letters = atoi(input_num); // Convertim șirul citit într-un număr întreg

        if (num_letters == 10)
        {
            printf("Introduceti primul sir: ");
            char input_word[256];
            fgets(input_word, sizeof(input_word), stdin);
            input_word[strcspn(input_word, "\n")] = '\0'; // Eliminăm caracterul newline din buffer
            first_word = strdup(input_word); // Salvează cuvântul introdus
        }
        else if (num_letters >= 0 && num_letters <= 9)
        {
            // Alegem un cuvânt corespunzător numărului introdus
            first_word = choose_word(num_letters);
            printf("Cuvantul ales este: %s\n", first_word);
        }
        else
        {
            printf("Ati tastat o varianta invalida.\n");
            return 1;
        }
    }
    while (num_letters == 10 && first_word == NULL);

    // Citim al doilea șir de la tastatură
    printf("Introduceti al doilea sir: ");
    char second_word[256];
    fgets(second_word, sizeof(second_word), stdin);
    second_word[strcspn(second_word, "\n")] = '\0'; // Eliminăm caracterul newline din buffer

    // Scriem primul șir în fișierul data.in
    FILE *input_file = fopen("data.in", "w");
    if (input_file == NULL)
    {
        printf("Eroare la deschiderea fisierului data.in\n");
        return 1;
    }
    fprintf(input_file, "%s", first_word);
    fclose(input_file);

    // Calculăm distanța Levenshtein între cele două cuvinte
    int distance = levenshtein_distance(first_word, second_word);

    // Scriem rezultatul în fișierul data.out
    FILE *output_file = fopen("data.out", "w");
    if (output_file == NULL)
    {
        printf("Eroare la deschiderea fisierului data.out\n");
        return 1;
    }
    if (num_letters > 9)
    {
        fprintf(output_file, "Numarul minim de operatii necesare dintre cele doua este %d", distance);
    }
    else
    {
        fprintf(output_file, "Numarul minim de operatii necesare pentru: func(%s) si func(%s) este %d", first_word, second_word, distance);
    }
    fclose(output_file);

    return 0;
}
