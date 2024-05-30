#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

void read_rules(char *str2);
void read_frag(char *str1);
int MinOfTwo(int a, int b);
int levenshtein_distance(const char *s1, const char *s2);
void write_output(const char *str1, const char *str2, int distance);

#endif // LEVENSHTEIN_H
