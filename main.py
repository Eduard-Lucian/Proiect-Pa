import random

def levenshtein_distance(s1, s2):
    m = len(s1)
    n = len(s2)

    # Inițializarea primei linii și a primei coloane
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    for i in range(m + 1):
        dp[i][0] = i
    for j in range(n + 1):
        dp[0][j] = j

    # Calcularea valorilor distanței Levenshtein
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                insert_cost = dp[i][j - 1] + 1
                delete_cost = dp[i - 1][j] + 1
                replace_cost = dp[i - 1][j - 1] + 1

                # Verificarea pentru transpozitie
                if i > 1 and j > 1 and s1[i - 2] == s2[j - 1] and s1[i - 1] == s2[j - 2]:
                    swap_cost = dp[i - 2][j - 2] + 1
                    replace_cost = min(replace_cost, swap_cost)

                dp[i][j] = min(insert_cost, delete_cost, replace_cost)

    # Rezultatul se află în colțul din dreapta jos al tabelei
    return dp[m][n]

def choose_word(length):
    words = ["", "a", "to", "dog", "bird", "apple", "elephant", "monkey", "inventa", "chirurgie"]
    num_words = len(words)
    index = random.randint(0, num_words - 1)
    while len(words[index]) != length:
        index = random.randint(0, num_words - 1)
    return words[index]

def main():
    use_predefined = int(input("Doriți să utilizați funcțiile predefinite? (0 - Nu, 1 - Da): "))
    
    if use_predefined == 1:
        num_letters = int(input("Specificati dimensiunea functiei (0-9): "))
        if num_letters < 0 or num_letters > 9:
            print("Dimensiunea specificată nu este validă.")
            return
        frag = choose_word(num_letters)
        print(f"Cuvântul ales este: {frag}")
        rule = input("Introduceți regula de sintaxă: ").strip()
    elif use_predefined == 0:
        rule = input("Introduceți regula de sintaxă: ").strip()
        frag = input("Introduceți fragmentul de cod: ").strip()
    else:
        print("Opțiune invalidă.")
        return

    distance = levenshtein_distance(rule, frag)
    print(f"Numărul minim de operații necesare este: {distance}")

# Rulăm funcția main direct
main()