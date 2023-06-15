#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    int i;
    int j;

    do
    {
        height = get_int("Please choose a number between 1 and 8, inclusive: \n");
    }
    while (height < 1 || height > 8);

    // Parent Loop
    for (i = 1; i <= height; i++)
    {
        // Left void
        for (j = height - i; j >= 1; j--)
        {
            printf(" ");
        }

        // Left triangle
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }

        // Double space
        printf("  ");

        // Right triangle
        for (j = 1; j <= i; j++)
        {
            printf("#");
        }

        // Move to next row
        printf("\n");
    }
}