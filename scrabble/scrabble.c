#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // isalpha plus && booleans make limit imput to alpha punctuation
    string word1 = get_string("Player 1: ");
    for (int i = 0; i < strlen(word1); i++)
        if (isalpha(word1[i]) == 0 && word1[i] != '!' && word1[i] != '?' && word1[i] != '.' && word1[i] != ',')
        {
            get_string("Player 1: ");
        }

    string word2 = get_string("Player 2: ");
    for (int j = 0; j < strlen(word2); j++)
        if (isalpha(word2[j]) == 0 && word2[j] != '!' && word2[j] != '?' && word2[j] != '.' && word2[j] != ',')
        {
            get_string("Player 2: ");
        }

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}


int compute_score(string word)
{

    int i;
    int n = strlen(word);
    char charUpper[n];
    int sum = 0;
    int j;

    // Converts to uppercase and assigns
    for (i = 0; i < n; i++)
    {
        if (islower(word[i]))
        {
            charUpper[i] = toupper(word[i]);
        }
        else
        {
            charUpper[i] = word[i];
        }
    }
    //filters out punctuation, accumulates points per char
    for (j = 0; j < n; j++)

        if (charUpper[j] != '!' && charUpper[j] != '?' && charUpper[j] != '.' && charUpper[j] != ',')
        {
            charUpper[j] = POINTS[(charUpper[j] - 65)];
            sum += charUpper[j];
        }
    return sum;
}