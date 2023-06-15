#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    string text = get_string("Text: ");

    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    float L = letters / words * 100;
    float S = sentences / words * 100;

    float rough = 0.0588 * L - 0.296 * S - 15.8;

    int index = round(rough);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %d\n", index);
    }

}

int count_letters(string text)
{
    int total = 0;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            total += 1;
        }
    }

    return total;
}

int count_words(string text)
{
    int total = 0;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ')
        {
            total += 1;
        }
    }
    total += 1;
    return total;
}

int count_sentences(string text)
{
    int total = 0;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            total += 1;
        }
    }

    return total;
}