#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[1])
{
    // Nothing is entered.
    if (argv[1] == NULL)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];
    int letterCount = strlen(key);

    for (int i = 0; i < letterCount; i++)
    {
        if (isalpha(key[i]) == 0 || argc > 2)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else
        {
            for (int j = i + 1; j < letterCount; j++)
            {
                if (key[i] == key[j])
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
        }
    }
    if (letterCount != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    int n = strlen(plaintext);
    int i = 0;
    char ciphertext[n];

    //Encryption algo:
    for (i = 0; i <= n; i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = key[(plaintext[i] - 65)];
            ciphertext[i] = toupper(ciphertext[i]);
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = key[(plaintext[i] - 97)];
            ciphertext[i] = tolower(ciphertext[i]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }

    }

    printf("ciphertext: %s\n", ciphertext);
}