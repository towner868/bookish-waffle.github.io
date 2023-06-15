#include <cs50.h>
#include <stdio.h>

int lengthFunction(double n, int *firstDigit);
long multSum(long x, long y);
long addSum(long x, long y);

int main(void)
{
    double input;
    int cardNumberlength;
    long sum;
    int firstDigit;

    input = get_long("Number: ");

    /* First card number length and first digits are tabulated*/
    cardNumberlength = lengthFunction(input, &firstDigit);

    /* multSum calculates the multiplied portions, addSum the add-only*/
    sum = multSum(input, cardNumberlength) + addSum(input, cardNumberlength);


    /*Now checksum can be performed, screening for appropriate range and respective card start number(s)*/
    if (cardNumberlength < 13 || cardNumberlength > 16)
    {
        printf("INVALID\n");
    }

    else if (sum % 10 == 0 && (firstDigit == 34 || firstDigit == 37))
    {
        printf("AMEX\n");
    }

    else if (sum % 10 == 0 && (firstDigit / 10 == 4))
    {
        printf("VISA\n");
    }

    else if (sum % 10 == 0 && (firstDigit == 51 || firstDigit == 52 || firstDigit == 53 || firstDigit == 54 || firstDigit == 55))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

/* Calculates length of number string looping by 10; passes firstDigit by reference*/
int lengthFunction(double n, int *firstDigit)
{
    int i;

    for (i = 0; n > 1; i++)
    {
        n /= 10;
    }
    *firstDigit = n * 100;
    return i;
}

/*Loop uses input value*/
long multSum(long x, long y)
{
    int i = y;
    int multDig[i];
    int multSum = 0;

    for (i = y; x > 0; i--)
    {
        x /= 10;
        multDig[i] += x % 10;
        x /= 10;
        multSum += ((multDig[i] * 2) / 10) + ((multDig[i] * 2) % 10);
    }
    return multSum;
}

/*Loop uses length value*/
long addSum(long x, long y)
{
    int i = y;
    int addDig[i];
    int addSum = 0;

    for (i = y / 2 + 1; i > 0; i--)
    {
        addDig[i] = x % 10;
        x /= 100;
        addSum += addDig[i];
    }
    return addSum;
}