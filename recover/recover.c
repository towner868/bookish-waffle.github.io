#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512

typedef uint8_t  BYTE;


int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Alias and pointer alias for argv file, and opening it in read mode
    char *input = argv[1];
    FILE *inptr  = fopen(input, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", input);
        return 1;
    }

    BYTE buffer[BLOCK];
    char filename[8];
    int count = 0;

    //Pointer for read/write functions
    FILE *imgptr;


    while (fread(buffer, BLOCK, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", count);

            if (count == 0)
            {
                imgptr  = fopen(filename, "w");
                fwrite(buffer, BLOCK, 1, imgptr);
                count++;
            }

            else
            {
                fclose(imgptr);
                imgptr  = fopen(filename, "w");
                fwrite(buffer, BLOCK, 1, imgptr);
                count++;
            }
        }
        else if (count)
        {
            fwrite(buffer, BLOCK, 1, imgptr);
        }
    }

    fclose(imgptr);
    fclose(inptr);
    return 0;
}