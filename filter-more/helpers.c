#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float redFloat = 0;
    float greenFloat = 0;
    float blueFloat = 0;
    int average = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            redFloat = image[i][j].rgbtRed;
            greenFloat = image[i][j].rgbtGreen;
            blueFloat = image[i][j].rgbtBlue;

            average = round((redFloat + greenFloat + blueFloat) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = swap;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // to avoid an array scramble, make copy of 2d array:

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Local-global variables:

    float redFloat[9];
    float greenFloat[9];
    float blueFloat[9];

    float totalRed = 0;
    float totalGreen = 0;
    float totalBlue = 0;

    float redAverage = 0;
    float greenAverage = 0;
    float blueAverage = 0;

    // Top left corner

    totalRed = copy[0][0].rgbtRed + copy[0][1].rgbtRed +
               copy[1][1].rgbtRed + copy[1][0].rgbtRed;

    totalGreen = copy[0][0].rgbtGreen + copy[0][1].rgbtGreen +
                 copy[1][1].rgbtGreen + copy[1][0].rgbtGreen;

    totalBlue = copy[0][0].rgbtBlue + copy[0][1].rgbtBlue +
                copy[1][1].rgbtBlue + copy[1][0].rgbtBlue;

    redAverage = round(totalRed / 4);
    greenAverage = round(totalGreen / 4);
    blueAverage = round(totalBlue / 4);

    image[0][0].rgbtRed = redAverage;
    image[0][0].rgbtGreen = greenAverage;
    image[0][0].rgbtBlue = blueAverage;

    // Top Row
    for (int i = 0; i < 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            totalRed = copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                       copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed;

            totalGreen = copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                         copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen;

            totalBlue = copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                        copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue;

            redAverage = round(totalRed / 6);
            greenAverage = round(totalGreen / 6);
            blueAverage = round(totalBlue / 6);

            image[i][j].rgbtRed = redAverage;
            image[i][j].rgbtGreen = greenAverage;
            image[i][j].rgbtBlue = blueAverage;

        }
    }

    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;

    redAverage = 0;
    greenAverage = 0;
    blueAverage = 0;

    // Top Right corner

    totalRed = copy[0][width - 2].rgbtRed + copy[0][width - 1].rgbtRed +
               copy[1][width - 1].rgbtRed + copy[1][width - 2].rgbtRed;

    totalGreen = copy[0][width - 2].rgbtGreen + copy[0][width - 1].rgbtGreen +
                 copy[1][width - 1].rgbtGreen + copy[1][width - 2].rgbtGreen;

    totalBlue = copy[0][width - 2].rgbtBlue + copy[0][width - 1].rgbtBlue +
                copy[1][width - 1].rgbtBlue + copy[1][width - 2].rgbtBlue;

    redAverage = round(totalRed / 4);
    greenAverage = round(totalGreen / 4);
    blueAverage = round(totalBlue / 4);

    image[0][width - 1].rgbtRed = redAverage;
    image[0][width - 1].rgbtGreen = greenAverage;
    image[0][width - 1].rgbtBlue = blueAverage;

    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;

    redAverage = 0;
    greenAverage = 0;
    blueAverage = 0;

    // Left Column
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            totalRed = copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed +
                       copy[i + 1][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j].rgbtRed;

            totalGreen = copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                         copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j].rgbtGreen;

            totalBlue = copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                        copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j].rgbtBlue;

            redAverage = round(totalRed / 6);
            greenAverage = round(totalGreen / 6);
            blueAverage = round(totalBlue / 6);

            image[i][j].rgbtRed = redAverage;
            image[i][j].rgbtGreen = greenAverage;
            image[i][j].rgbtBlue = blueAverage;

        }
    }

    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;

    redAverage = 0;
    greenAverage = 0;
    blueAverage = 0;



    // Middle Loop
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {

            redFloat[8] = copy[i - 1][j - 1].rgbtRed;
            redFloat[7] = copy[i - 1][j].rgbtRed;
            redFloat[6] = copy[i - 1][j + 1].rgbtRed;
            redFloat[5] = copy[i][j - 1].rgbtRed;
            redFloat[4] = copy[i][j].rgbtRed;
            redFloat[3] = copy[i][j + 1].rgbtRed;
            redFloat[2] = copy[i + 1][j - 1].rgbtRed;
            redFloat[1] = copy[i + 1][j].rgbtRed;
            redFloat[0] = copy[i + 1][j + 1].rgbtRed;

            greenFloat[8] = copy[i - 1][j - 1].rgbtGreen;
            greenFloat[7] = copy[i - 1][j].rgbtGreen;
            greenFloat[6] = copy[i - 1][j + 1].rgbtGreen;
            greenFloat[5] = copy[i][j - 1].rgbtGreen;
            greenFloat[4] = copy[i][j].rgbtGreen;
            greenFloat[3] = copy[i][j + 1].rgbtGreen;
            greenFloat[2] = copy[i + 1][j - 1].rgbtGreen;
            greenFloat[1] = copy[i + 1][j].rgbtGreen;
            greenFloat[0] = copy[i + 1][j + 1].rgbtGreen;

            blueFloat[8] = copy[i - 1][j - 1].rgbtBlue;
            blueFloat[7] = copy[i - 1][j].rgbtBlue;
            blueFloat[6] = copy[i - 1][j + 1].rgbtBlue;
            blueFloat[5] = copy[i][j - 1].rgbtBlue;
            blueFloat[4] = copy[i][j].rgbtBlue;
            blueFloat[3] = copy[i][j + 1].rgbtBlue;
            blueFloat[2] = copy[i + 1][j - 1].rgbtBlue;
            blueFloat[1] = copy[i + 1][j].rgbtBlue;
            blueFloat[0] = copy[i + 1][j + 1].rgbtBlue;

            for (int k = 8; k >= 0; k--)
            {
                totalRed += redFloat[k];
                totalGreen += greenFloat[k];
                totalBlue += blueFloat[k];

                redFloat[k] = 0;
                greenFloat[k] = 0;
                blueFloat[k] = 0;
            }


            image[i][j].rgbtRed = round(totalRed / 9);
            image[i][j].rgbtGreen = round(totalGreen / 9);
            image[i][j].rgbtBlue = round(totalBlue / 9);

            totalRed = 0;
            totalGreen = 0;
            totalBlue = 0;
        }
    }

    redAverage = 0;
    greenAverage = 0;
    blueAverage = 0;

    // Right Column
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = width - 1; j < width; j++)
        {
            totalRed = copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed +
                       copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed;

            totalGreen = copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                         copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen;

            totalBlue = copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                        copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue;

            redAverage = round(totalRed / 6);
            greenAverage = round(totalGreen / 6);
            blueAverage = round(totalBlue / 6);

            image[i][j].rgbtRed = redAverage;
            image[i][j].rgbtGreen = greenAverage;
            image[i][j].rgbtBlue = blueAverage;

        }
    }

    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;

    redAverage = 0;
    greenAverage = 0;
    blueAverage = 0;

    // Bottom Left Corner

    totalRed = copy[height - 2][0].rgbtRed + copy[height - 2][1].rgbtRed +
               copy[height - 1][1].rgbtRed + copy[height - 1][0].rgbtRed;

    totalGreen = copy[height - 2][0].rgbtGreen + copy[height - 2][1].rgbtGreen +
                 copy[height - 1][1].rgbtGreen + copy[height - 1][0].rgbtGreen;

    totalBlue = copy[height - 2][0].rgbtBlue + copy[height - 2][1].rgbtBlue +
                copy[height - 1][1].rgbtBlue + copy[height - 1][0].rgbtBlue;

    redAverage = round(totalRed / 4);
    greenAverage = round(totalGreen / 4);
    blueAverage = round(totalBlue / 4);

    image[height - 1][0].rgbtRed = redAverage;
    image[height - 1][0].rgbtGreen = greenAverage;
    image[height - 1][0].rgbtBlue = blueAverage;

    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;

    redAverage = 0;
    greenAverage = 0;
    blueAverage = 0;


    // Bottom Row
    for (int i = height - 1; i < height; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            totalRed = copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                       copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed;

            totalGreen = copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                         copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen;

            totalBlue = copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                        copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue;

            redAverage = round(totalRed / 6);
            greenAverage = round(totalGreen / 6);
            blueAverage = round(totalBlue / 6);

            image[i][j].rgbtRed = redAverage;
            image[i][j].rgbtGreen = greenAverage;
            image[i][j].rgbtBlue = blueAverage;

        }
    }

    totalRed = 0;
    totalGreen = 0;
    totalBlue = 0;

    redAverage = 0;
    greenAverage = 0;
    blueAverage = 0;

    // Bottom Right corner

    totalRed = copy[height - 1][width - 1].rgbtRed + copy[height - 1][width - 2].rgbtRed +
               copy[height - 2][width - 2].rgbtRed + copy[height - 2][width - 1].rgbtRed;

    totalGreen = copy[height - 1][width - 1].rgbtGreen + copy[height - 1][width - 2].rgbtGreen +
                 copy[height - 2][width - 2].rgbtGreen + copy[height - 2][width - 1].rgbtGreen;

    totalBlue = copy[height - 1][width - 1].rgbtBlue + copy[height - 1][width - 2].rgbtBlue +
                copy[height - 2][width - 2].rgbtBlue + copy[height - 2][width - 1].rgbtBlue;

    redAverage = round(totalRed / 4);
    greenAverage = round(totalGreen / 4);
    blueAverage = round(totalBlue / 4);

    image[height - 1][width - 1].rgbtRed = redAverage;
    image[height - 1][width - 1].rgbtGreen = greenAverage;
    image[height - 1][width - 1].rgbtBlue = blueAverage;

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // to avoid an array scramble, make copy of 2d array:

    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    float redFloatX[9];
    float greenFloatX[9];
    float blueFloatX[9];

    float redFloatY[9];
    float greenFloatY[9];
    float blueFloatY[9];

    float totalRedX = 0;
    float totalGreenX = 0;
    float totalBlueX = 0;

    float totalRedY = 0;
    float totalGreenY = 0;
    float totalBlueY = 0;

    float redSobel = 0;
    float greenSobel = 0;
    float blueSobel = 0;

    // Top left corner

    totalRedX = (copy[0][0].rgbtRed * 0) + (copy[0][1].rgbtRed * 2) +
                (copy[1][1].rgbtRed * 1) + (copy[1][0].rgbtRed * 0);

    totalGreenX = (copy[0][0].rgbtGreen * 0) + (copy[0][1].rgbtGreen * 2) +
                  (copy[1][1].rgbtGreen * 1) + (copy[1][0].rgbtGreen * 0);

    totalBlueX = (copy[0][0].rgbtBlue * 0) + (copy[0][1].rgbtBlue * 2) +
                 (copy[1][1].rgbtBlue * 1) + (copy[1][0].rgbtBlue * 0);

    totalRedY = (copy[0][0].rgbtRed * 0) + (copy[0][1].rgbtRed * 0) +
                (copy[1][1].rgbtRed * 1) + (copy[1][0].rgbtRed * 2);

    totalGreenY = (copy[0][0].rgbtGreen * 0) + (copy[0][1].rgbtGreen * 0) +
                  (copy[1][1].rgbtGreen * 1) + (copy[1][0].rgbtGreen * 2);

    totalBlueY = (copy[0][0].rgbtBlue * 0) + (copy[0][1].rgbtBlue * 0) +
                 (copy[1][1].rgbtBlue * 1) + (copy[1][0].rgbtBlue * 2);


    redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
    if (redSobel >= 255)
    {
        redSobel = 255;
    }
    greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
    if (greenSobel >= 255)
    {
        greenSobel = 255;
    }
    blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
    if (blueSobel >= 255)
    {
        blueSobel = 255;
    }

    image[0][0].rgbtRed = round(redSobel);
    image[0][0].rgbtGreen = round(greenSobel);
    image[0][0].rgbtBlue = round(blueSobel);

    totalRedX = 0;
    totalGreenX = 0;
    totalBlueX = 0;

    totalRedY = 0;
    totalGreenY = 0;
    totalBlueY = 0;

    redSobel = 0;
    greenSobel = 0;
    blueSobel = 0;

    // Top Row
    for (int i = 0; i < 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            totalRedX = (copy[i][j].rgbtRed * 0) + (copy[i][j - 1].rgbtRed * -2) + (copy[i + 1][j - 1].rgbtRed * -1) +
                        (copy[i + 1][j].rgbtRed * 0) + (copy[i + 1][j + 1].rgbtRed * 1) + (copy[i][j + 1].rgbtRed * 2);

            totalGreenX = (copy[i][j].rgbtGreen * 0) + (copy[i][j - 1].rgbtGreen * -2) + (copy[i + 1][j - 1].rgbtGreen * -1) +
                          (copy[i + 1][j].rgbtGreen * 0) + (copy[i + 1][j + 1].rgbtGreen * 1) + (copy[i][j + 1].rgbtGreen * 2);

            totalBlueX = (copy[i][j].rgbtBlue * 0) + (copy[i][j - 1].rgbtBlue * -2) + (copy[i + 1][j - 1].rgbtBlue * -1) +
                         (copy[i + 1][j].rgbtBlue * 0) + (copy[i + 1][j + 1].rgbtBlue * 1) + (copy[i][j + 1].rgbtBlue * 2);

            totalRedY = (copy[i][j].rgbtRed * 0) + (copy[i][j - 1].rgbtRed * 0) + (copy[i + 1][j - 1].rgbtRed * 1) +
                        (copy[i + 1][j].rgbtRed * 2) + (copy[i + 1][j + 1].rgbtRed * 1) + (copy[i][j + 1].rgbtRed * 0);

            totalGreenY = (copy[i][j].rgbtGreen * 0) + (copy[i][j - 1].rgbtGreen * 0) + (copy[i + 1][j - 1].rgbtGreen * 1) +
                          (copy[i + 1][j].rgbtGreen * 2) + (copy[i + 1][j + 1].rgbtGreen * 1) + (copy[i][j + 1].rgbtGreen * 0);

            totalBlueY = (copy[i][j].rgbtBlue * 0) + (copy[i][j - 1].rgbtBlue * 0) + (copy[i + 1][j - 1].rgbtBlue * 1) +
                         (copy[i + 1][j].rgbtBlue * 2) + (copy[i + 1][j + 1].rgbtBlue * 1) + (copy[i][j + 1].rgbtBlue * 0);

            redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
            if (redSobel >= 255)
            {
                redSobel = 255;
            }

            greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
            if (greenSobel >= 255)
            {
                greenSobel = 255;
            }

            blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
            if (blueSobel >= 255)
            {
                blueSobel = 255;
            }

            image[i][j].rgbtRed = round(redSobel);
            image[i][j].rgbtGreen = round(greenSobel);
            image[i][j].rgbtBlue = round(blueSobel);

            totalRedX = 0;
            totalGreenX = 0;
            totalBlueX = 0;

            totalRedY = 0;
            totalGreenY = 0;
            totalBlueY = 0;

            redSobel = 0;
            greenSobel = 0;
            blueSobel = 0;
        }
    }

    totalRedX = 0;
    totalGreenX = 0;
    totalBlueX = 0;

    totalRedY = 0;
    totalGreenY = 0;
    totalBlueY = 0;

    redSobel = 0;
    greenSobel = 0;
    blueSobel = 0;

    // Top Right corner

    totalRedX = (copy[0][width - 2].rgbtRed * -2) + (copy[0][width - 1].rgbtRed * 0) +
                (copy[1][width - 1].rgbtRed * 0) + (copy[1][width - 2].rgbtRed * -1);

    totalGreenX = (copy[0][width - 2].rgbtGreen * -2) + (copy[0][width - 1].rgbtGreen * 0) +
                  (copy[1][width - 1].rgbtGreen * 0) + (copy[1][width - 2].rgbtGreen * -1);

    totalBlueX = (copy[0][width - 2].rgbtBlue * -2) + (copy[0][width - 1].rgbtBlue * 0) +
                 (copy[1][width - 1].rgbtBlue * 0) + (copy[1][width - 2].rgbtBlue * -1);

    totalRedY = (copy[0][width - 2].rgbtRed * 0) + (copy[0][width - 1].rgbtRed * 0) +
                (copy[1][width - 1].rgbtRed * 2) + (copy[1][width - 2].rgbtRed * 1);

    totalGreenY = (copy[0][width - 2].rgbtGreen * 0) + (copy[0][width - 1].rgbtGreen * 0) +
                  (copy[1][width - 1].rgbtGreen * 2) + (copy[1][width - 2].rgbtGreen * 1);

    totalBlueY = (copy[0][width - 2].rgbtBlue * 0) + (copy[0][width - 1].rgbtBlue * 0) +
                 (copy[1][width - 1].rgbtBlue * 2) + (copy[1][width - 2].rgbtBlue * 1);

    redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
    if (redSobel >= 255)
    {
        redSobel = 255;
    }
    greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
    if (greenSobel >= 255)
    {
        greenSobel = 255;
    }
    blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
    if (blueSobel >= 255)
    {
        blueSobel = 255;
    }

    image[0][width - 1].rgbtRed = round(redSobel);
    image[0][width - 1].rgbtGreen = round(greenSobel);
    image[0][width - 1].rgbtBlue = round(blueSobel);

    totalRedX = 0;
    totalGreenX = 0;
    totalBlueX = 0;

    totalRedY = 0;
    totalGreenY = 0;
    totalBlueY = 0;

    redSobel = 0;
    greenSobel = 0;
    blueSobel = 0;

// Left Column
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            totalRedX = (copy[i - 1][j].rgbtRed * 0) + (copy[i - 1][j + 1].rgbtRed * 1) + (copy[i][j + 1].rgbtRed * 2) +
                        (copy[i + 1][j + 1].rgbtRed * 1) + (copy[i + 1][j].rgbtRed * 0) + (copy[i][j].rgbtRed * 0);

            totalGreenX = (copy[i - 1][j].rgbtGreen * 0) + (copy[i - 1][j + 1].rgbtGreen * 1) + (copy[i][j + 1].rgbtGreen * 2) +
                          (copy[i + 1][j + 1].rgbtGreen * 1) + (copy[i + 1][j].rgbtGreen * 0) + (copy[i][j].rgbtGreen * 0);

            totalBlueX = (copy[i - 1][j].rgbtBlue * 0) + (copy[i - 1][j + 1].rgbtBlue * 1) + (copy[i][j + 1].rgbtBlue * 2) +
                         (copy[i + 1][j + 1].rgbtBlue * 1)  + (copy[i + 1][j].rgbtBlue * 0) + (copy[i][j].rgbtBlue * 0);

            totalRedY = (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1) + (copy[i][j + 1].rgbtRed * 0) +
                        (copy[i + 1][j + 1].rgbtRed * 1) + (copy[i + 1][j].rgbtRed * 2) + (copy[i][j].rgbtRed * 0);

            totalGreenY = (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1) + (copy[i][j + 1].rgbtGreen * 0) +
                          (copy[i + 1][j + 1].rgbtGreen * 1) + (copy[i + 1][j].rgbtGreen * 2) + (copy[i][j].rgbtGreen * 0);

            totalBlueY = (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1) + (copy[i][j + 1].rgbtBlue * 0) +
                         (copy[i + 1][j + 1].rgbtBlue * 1) + (copy[i + 1][j].rgbtBlue * 2) + (copy[i][j].rgbtBlue * 0);

            redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
            if (redSobel >= 255)
            {
                redSobel = 255;
            }
            greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
            if (greenSobel >= 255)
            {
                greenSobel = 255;
            }
            blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
            if (blueSobel >= 255)
            {
                blueSobel = 255;
            }

            image[i][j].rgbtRed = round(redSobel);
            image[i][j].rgbtGreen = round(greenSobel);
            image[i][j].rgbtBlue = round(blueSobel);

            totalRedX = 0;
            totalGreenX = 0;
            totalBlueX = 0;

            totalRedY = 0;
            totalGreenY = 0;
            totalBlueY = 0;

            redSobel = 0;
            greenSobel = 0;
            blueSobel = 0;
        }
    }


    // Middle Loop
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {

            redFloatX[8] = (copy[i - 1][j - 1].rgbtRed * -1);
            redFloatX[7] = (copy[i - 1][j].rgbtRed * 0);
            redFloatX[6] = (copy[i - 1][j + 1].rgbtRed * 1);
            redFloatX[5] = (copy[i][j - 1].rgbtRed * -2);
            redFloatX[4] = (copy[i][j].rgbtRed * 0);
            redFloatX[3] = (copy[i][j + 1].rgbtRed * 2);
            redFloatX[2] = (copy[i + 1][j - 1].rgbtRed * -1);
            redFloatX[1] = (copy[i + 1][j].rgbtRed * 0);
            redFloatX[0] = (copy[i + 1][j + 1].rgbtRed * 1);

            greenFloatX[8] = (copy[i - 1][j - 1].rgbtGreen * -1);
            greenFloatX[7] = (copy[i - 1][j].rgbtGreen * 0);
            greenFloatX[6] = (copy[i - 1][j + 1].rgbtGreen * 1);
            greenFloatX[5] = (copy[i][j - 1].rgbtGreen * -2);
            greenFloatX[4] = (copy[i][j].rgbtGreen * 0);
            greenFloatX[3] = (copy[i][j + 1].rgbtGreen * 2);
            greenFloatX[2] = (copy[i + 1][j - 1].rgbtGreen * -1);
            greenFloatX[1] = (copy[i + 1][j].rgbtGreen * 0);
            greenFloatX[0] = (copy[i + 1][j + 1].rgbtGreen * 1);

            blueFloatX[8] = (copy[i - 1][j - 1].rgbtBlue * -1);
            blueFloatX[7] = (copy[i - 1][j].rgbtBlue * 0);
            blueFloatX[6] = (copy[i - 1][j + 1].rgbtBlue * 1);
            blueFloatX[5] = (copy[i][j - 1].rgbtBlue * -2);
            blueFloatX[4] = (copy[i][j].rgbtBlue * 0);
            blueFloatX[3] = (copy[i][j + 1].rgbtBlue * 2);
            blueFloatX[2] = (copy[i + 1][j - 1].rgbtBlue * -1);
            blueFloatX[1] = (copy[i + 1][j].rgbtBlue * 0);
            blueFloatX[0] = (copy[i + 1][j + 1].rgbtBlue * 1);

            redFloatY[8] = (copy[i - 1][j - 1].rgbtRed * -1);
            redFloatY[7] = (copy[i - 1][j].rgbtRed * -2);
            redFloatY[6] = (copy[i - 1][j + 1].rgbtRed * -1);
            redFloatY[5] = (copy[i][j - 1].rgbtRed * 0);
            redFloatY[4] = (copy[i][j].rgbtRed * 0);
            redFloatY[3] = (copy[i][j + 1].rgbtRed * 0);
            redFloatY[2] = (copy[i + 1][j - 1].rgbtRed * 1);
            redFloatY[1] = (copy[i + 1][j].rgbtRed * 2);
            redFloatY[0] = (copy[i + 1][j + 1].rgbtRed * 1);

            greenFloatY[8] = (copy[i - 1][j - 1].rgbtGreen * -1);
            greenFloatY[7] = (copy[i - 1][j].rgbtGreen * -2);
            greenFloatY[6] = (copy[i - 1][j + 1].rgbtGreen * -1);
            greenFloatY[5] = (copy[i][j - 1].rgbtGreen * 0);
            greenFloatY[4] = (copy[i][j].rgbtGreen * 0);
            greenFloatY[3] = (copy[i][j + 1].rgbtGreen * 0);
            greenFloatY[2] = (copy[i + 1][j - 1].rgbtGreen * 1);
            greenFloatY[1] = (copy[i + 1][j].rgbtGreen * 2);
            greenFloatY[0] = (copy[i + 1][j + 1].rgbtGreen * 1);

            blueFloatY[8] = (copy[i - 1][j - 1].rgbtBlue * -1);
            blueFloatY[7] = (copy[i - 1][j].rgbtBlue * -2);
            blueFloatY[6] = (copy[i - 1][j + 1].rgbtBlue * -1);
            blueFloatY[5] = (copy[i][j - 1].rgbtBlue * 0);
            blueFloatY[4] = (copy[i][j].rgbtBlue * 0);
            blueFloatY[3] = (copy[i][j + 1].rgbtBlue * 0);
            blueFloatY[2] = (copy[i + 1][j - 1].rgbtBlue * 1);
            blueFloatY[1] = (copy[i + 1][j].rgbtBlue * 2);
            blueFloatY[0] = (copy[i + 1][j + 1].rgbtBlue * 1);

            for (int k = 0; k < 9; k++)
            {
                totalRedX += redFloatX[k];
                totalGreenX += greenFloatX[k];
                totalBlueX += blueFloatX[k];

                totalRedY += redFloatY[k];
                totalGreenY += greenFloatY[k];
                totalBlueY += blueFloatY[k];

                redFloatX[k] = 0;
                greenFloatX[k] = 0;
                blueFloatX[k] = 0;

                redFloatY[k] = 0;
                greenFloatY[k] = 0;
                blueFloatY[k] = 0;
            }

            redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
            if (redSobel >= 255)
            {
                redSobel = 255;
            }

            greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
            if (greenSobel >= 255)
            {
                greenSobel = 255;
            }

            blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
            if (blueSobel >= 255)
            {
                blueSobel = 255;
            }

            image[i][j].rgbtRed = round(redSobel);
            image[i][j].rgbtGreen = round(greenSobel);
            image[i][j].rgbtBlue = round(blueSobel);

            totalRedX = 0;
            totalGreenX = 0;
            totalBlueX = 0;

            totalRedY = 0;
            totalGreenY = 0;
            totalBlueY = 0;

            redSobel = 0;
            greenSobel = 0;
            blueSobel = 0;

        }
    }

    // Right Column
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = width - 1; j < width; j++)
        {
            totalRedX = (copy[i + 1][j].rgbtRed * 0) + (copy[i + 1][j - 1].rgbtRed * -1) + (copy[i][j - 1].rgbtRed * -2) +
                        (copy[i - 1][j - 1].rgbtRed * -1) + (copy[i - 1][j].rgbtRed * 0) + (copy[i][j].rgbtRed * 0);

            totalGreenX = (copy[i + 1][j].rgbtGreen * 0) + (copy[i + 1][j - 1].rgbtGreen * -1) + (copy[i][j - 1].rgbtGreen * -2) +
                          (copy[i - 1][j - 1].rgbtGreen * -1) + (copy[i - 1][j].rgbtGreen * 0) + (copy[i][j].rgbtGreen * 0);

            totalBlueX = (copy[i + 1][j].rgbtBlue * 0) + (copy[i + 1][j - 1].rgbtBlue * -1) + (copy[i][j - 1].rgbtBlue * -2) +
                         (copy[i - 1][j - 1].rgbtBlue * -1) + (copy[i - 1][j].rgbtBlue * 0) + (copy[i][j].rgbtBlue * 0);

            totalRedY = (copy[i + 1][j].rgbtRed * -2) + (copy[i + 1][j - 1].rgbtRed * -1) + (copy[i][j - 1].rgbtRed * 0) +
                        (copy[i - 1][j - 1].rgbtRed * 1) + (copy[i - 1][j].rgbtRed * 2) + (copy[i][j].rgbtRed * 0);

            totalGreenY = (copy[i + 1][j].rgbtGreen * -2) + (copy[i + 1][j - 1].rgbtGreen * -1) + (copy[i][j - 1].rgbtGreen * 0) +
                          (copy[i - 1][j - 1].rgbtGreen * 1) + (copy[i - 1][j].rgbtGreen * 2) + (copy[i][j].rgbtGreen * 0);

            totalBlueY = (copy[i + 1][j].rgbtBlue * -2) + (copy[i + 1][j - 1].rgbtBlue * -1) + (copy[i][j - 1].rgbtBlue * 0) +
                         (copy[i - 1][j - 1].rgbtBlue * 1) + (copy[i - 1][j].rgbtBlue * 2) + (copy[i][j].rgbtBlue * 0);

            redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
            if (redSobel >= 255)
            {
                redSobel = 255;
            }
            greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
            if (greenSobel >= 255)
            {
                greenSobel = 255;
            }
            blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
            if (blueSobel >= 255)
            {
                blueSobel = 255;
            }

            image[i][j].rgbtRed = round(redSobel);
            image[i][j].rgbtGreen = round(greenSobel);
            image[i][j].rgbtBlue = round(blueSobel);

            totalRedX = 0;
            totalGreenX = 0;
            totalBlueX = 0;

            totalRedY = 0;
            totalGreenY = 0;
            totalBlueY = 0;

            redSobel = 0;
            greenSobel = 0;
            blueSobel = 0;
        }
    }

    // Bottom Left Corner

    totalRedX = (copy[height - 2][0].rgbtRed * 0) + (copy[height - 2][1].rgbtRed * 1) +
                (copy[height - 1][1].rgbtRed * 2) + (copy[height - 1][0].rgbtRed * 0);

    totalGreenX = (copy[height - 2][0].rgbtGreen * 0) + (copy[height - 2][1].rgbtGreen * 1) +
                  (copy[height - 1][1].rgbtGreen * 2) + (copy[height - 1][0].rgbtGreen * 0);

    totalBlueX = (copy[height - 2][0].rgbtBlue * 0) + (copy[height - 2][1].rgbtBlue * 1) +
                 (copy[height - 1][1].rgbtBlue * 2) + (copy[height - 1][0].rgbtBlue * 0);

    totalRedY = (copy[height - 2][0].rgbtRed * -2) + (copy[height - 2][1].rgbtRed * -1) +
                (copy[height - 1][1].rgbtRed * 0) + (copy[height - 1][0].rgbtRed * 0);

    totalGreenY = (copy[height - 2][0].rgbtGreen * -2) + (copy[height - 2][1].rgbtGreen * -1) +
                  (copy[height - 1][1].rgbtGreen * 0) + (copy[height - 1][0].rgbtGreen * 0);

    totalBlueY = (copy[height - 2][0].rgbtBlue * -2) + (copy[height - 2][1].rgbtBlue * -1) +
                 (copy[height - 1][1].rgbtBlue * 0) + (copy[height - 1][0].rgbtBlue * 0);

    redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
    if (redSobel >= 255)
    {
        redSobel = 255;
    }
    greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
    if (greenSobel >= 255)
    {
        greenSobel = 255;
    }
    blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
    if (blueSobel >= 255)
    {
        blueSobel = 255;
    }

    image[height - 1][0].rgbtRed = round(redSobel);
    image[height - 1][0].rgbtGreen = round(greenSobel);
    image[height - 1][0].rgbtBlue = round(blueSobel);

    totalRedX = 0;
    totalGreenX = 0;
    totalBlueX = 0;

    totalRedY = 0;
    totalGreenY = 0;
    totalBlueY = 0;

    redSobel = 0;
    greenSobel = 0;
    blueSobel = 0;

    // Bottom Row
    for (int i = height - 1; i < height; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            totalRedX = (copy[i][j].rgbtRed * 0) + (copy[i][j - 1].rgbtRed * -2) + (copy[i - 1][j - 1].rgbtRed * -1) +
                        (copy[i - 1][j].rgbtRed * 0) + (copy[i - 1][j + 1].rgbtRed * 1) + (copy[i][j + 1].rgbtRed * 2);

            totalGreenX = (copy[i][j].rgbtGreen * 0) + (copy[i][j - 1].rgbtGreen * -2) + (copy[i - 1][j - 1].rgbtGreen * -1) +
                          (copy[i - 1][j].rgbtGreen * 0) + (copy[i - 1][j + 1].rgbtGreen * 1) + (copy[i][j + 1].rgbtGreen * 2);

            totalBlueX = (copy[i][j].rgbtBlue * 0) + (copy[i][j - 1].rgbtBlue * -2) + (copy[i - 1][j - 1].rgbtBlue * -1) +
                         (copy[i - 1][j].rgbtBlue * 0) + (copy[i - 1][j + 1].rgbtBlue * 1)  + (copy[i][j + 1].rgbtBlue * 2);

            totalRedY = (copy[i][j].rgbtRed * 0) + (copy[i][j - 1].rgbtRed * 0) + (copy[i - 1][j - 1].rgbtRed * -1) +
                        (copy[i - 1][j].rgbtRed * -2) + (copy[i - 1][j + 1].rgbtRed * -1) + (copy[i][j + 1].rgbtRed * 0);

            totalGreenY = (copy[i][j].rgbtGreen * 0) + (copy[i][j - 1].rgbtGreen * 0) + (copy[i - 1][j - 1].rgbtGreen * -1) +
                          (copy[i - 1][j].rgbtGreen * -2) + (copy[i - 1][j + 1].rgbtGreen * -1) + (copy[i][j + 1].rgbtGreen * 0);

            totalBlueY = (copy[i][j].rgbtBlue * 0) + (copy[i][j - 1].rgbtBlue * 0) + (copy[i - 1][j - 1].rgbtBlue * -1) +
                         (copy[i - 1][j].rgbtBlue * -2) + (copy[i - 1][j + 1].rgbtBlue * -1) + (copy[i][j + 1].rgbtBlue * 0);

            redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
            if (redSobel >= 255)
            {
                redSobel = 255;
            }
            greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
            if (greenSobel >= 255)
            {
                greenSobel = 255;
            }
            blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
            if (blueSobel >= 255)
            {
                blueSobel = 255;
            }

            image[i][j].rgbtRed = round(redSobel);
            image[i][j].rgbtGreen = round(greenSobel);
            image[i][j].rgbtBlue = round(blueSobel);

        }
    }

    // Bottom Right corner

    totalRedX = (copy[height - 1][width - 1].rgbtRed * 0)  + (copy[height - 1][width - 2].rgbtRed * -2) +
                (copy[height - 2][width - 2].rgbtRed * -1) + (copy[height - 2][width - 1].rgbtRed * 0);

    totalGreenX = (copy[height - 1][width - 1].rgbtGreen * 0) + (copy[height - 1][width - 2].rgbtGreen * -2) +
                  (copy[height - 2][width - 2].rgbtGreen * -1) + (copy[height - 2][width - 1].rgbtGreen * 0);

    totalBlueX = (copy[height - 1][width - 1].rgbtBlue * 0) + (copy[height - 1][width - 2].rgbtBlue * -2) +
                 (copy[height - 2][width - 2].rgbtBlue * -1) + (copy[height - 2][width - 1].rgbtBlue * 0);

    totalRedY = (copy[height - 1][width - 1].rgbtRed * 0) + (copy[height - 1][width - 2].rgbtRed * 0) +
                (copy[height - 2][width - 2].rgbtRed * -1) + (copy[height - 2][width - 1].rgbtRed * -2);

    totalGreenY = (copy[height - 1][width - 1].rgbtGreen * 0) + (copy[height - 1][width - 2].rgbtGreen * 0) +
                  (copy[height - 2][width - 2].rgbtGreen * -1) + (copy[height - 2][width - 1].rgbtGreen * -2);

    totalBlueY = (copy[height - 1][width - 1].rgbtBlue * 0) + (copy[height - 1][width - 2].rgbtBlue * 0) +
                 (copy[height - 2][width - 2].rgbtBlue * -1) + (copy[height - 2][width - 1].rgbtBlue * -2);

    redSobel = sqrt(pow(totalRedX, 2) + pow(totalRedY, 2));
    if (redSobel >= 255)
    {
        redSobel = 255;
    }
    greenSobel = sqrt(pow(totalGreenX, 2) + pow(totalGreenY, 2));
    if (greenSobel >= 255)
    {
        greenSobel = 255;
    }
    blueSobel = sqrt(pow(totalBlueX, 2) + pow(totalBlueY, 2));
    if (blueSobel >= 255)
    {
        blueSobel = 255;
    }

    image[height - 1][width - 1].rgbtRed = round(redSobel);
    image[height - 1][width - 1].rgbtGreen = round(greenSobel);
    image[height - 1][width - 1].rgbtBlue = round(blueSobel);

    return;
}
