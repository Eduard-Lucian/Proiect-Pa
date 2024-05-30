#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "levenshtein.h"

// Funcția pentru citirea fragmentului corect
void read_rules(char *str2)
{
    FILE *fl = fopen("data.in", "r");
    if (fl == NULL)
    {
        printf("Eroare la citire\n");
        exit(1);
    }
    // Citim prima linie din fișier, presupunând că este regula
    if (fgets(str2, 256, fl) == NULL)
    {
        printf("Eroare la citire\n");
        fclose(fl);
        exit(1);
    }
    // Eliminăm caracterul newline dacă există
    str2[strcspn(str2, "\n")] = '\0';
    fclose(fl);
}

// Funcția pentru citirea fragmentului dat de utilizator
void read_frag(char *str1)
{
    FILE *fl = fopen("data.in", "r");
    if (fl == NULL)
    {
        printf("Eroare la citire\n");
        exit(1);
    }
    // Sărim peste prima linie (regula)
    fgets(str1, 256, fl);
    // Citim a doua linie din fișier, presupunând că este fragmentul de cod
    if (fgets(str1, 256, fl) == NULL)
    {
        printf("Eroare la citire\n");
        fclose(fl);
        exit(1);
    }
    // Eliminăm caracterul newline dacă există
    str1[strcspn(str1, "\n")] = '\0';
    fclose(fl);
}

// Funcția care returnează minimul dintre două valori întregi
int MinOfTwo(int a, int b)
{
    return a < b ? a : b;
}

// Funcția care calculează distanța Levenshtein între două șiruri de caractere
int levenshtein_distance(const char *s1, const char *s2)
{
    int m = strlen(s1);
    int n = strlen(s2);

    // Alocarea memoriei pentru tabela de programare dinamică
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    // Inițializarea primei linii și a primei coloane
    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j;
    }

    // Calcularea valorilor distanței Levenshtein
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s1[i] == s2[j])
            {
                dp[i + 1][j + 1] = dp[i][j];
            }
            else
            {
                int insert_cost = dp[i + 1][j] + 1;
                int delete_cost = dp[i][j + 1] + 1;
                int replace_cost = dp[i][j] + 1;

                // Verificarea pentru transpozitie
                if (i > 0 && j > 0 && s1[i - 1] == s2[j] && s1[i] == s2[j - 1])
                {
                    int swap_cost = dp[i - 1][j - 1] + 1;
                    replace_cost = MinOfTwo(replace_cost, swap_cost);
                }
                dp[i + 1][j + 1] = MinOfTwo(MinOfTwo(insert_cost, delete_cost), replace_cost);
            }
        }
    }

    // Rezultatul se află în colțul din dreapta jos al tabelei
    int result = dp[m][n];

    // Eliberarea memoriei alocate pentru tabela de programare dinamică
    for (int i = 0; i <= m; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return result;
}

// Funcția pentru scrierea rezultatului în fișier
void write_output(const char *str1, const char *str2, int distance)
{
    FILE *output_file = fopen("data.out", "w");
    if (output_file == NULL)
    {
        printf("Eroare la scriere\n");
        return;
    }

    fclose(output_file);
}
