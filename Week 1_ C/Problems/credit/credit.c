#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Declare variables
    long credit = get_long("Credit Card Number: ");
    int length = 0;
    long creditCount = credit;

    // Get Length of Number
    while (creditCount > 0)
    {
        // Divide by 10 until int < 0 while incrementing length
        creditCount = creditCount / 10;
        length++;
    }

    // Calculate sum of digits using Luhn's Algorithm
    int sum = 0;

    // For every digit
    for (int i = 0; i < length; i++)
    {
        // Find ith digit
        long power = pow(10, i);
        int digit = (credit / power) % 10;

        // If every other location
        if (i % 2 == 0)
        {
            sum += digit;
        }
        else
        {
            int otherDigit = digit * 2;
            int otherOnes = otherDigit % 10;
            int otherTens = otherDigit / 10;
            int otherSum = otherOnes + otherTens;
            sum += otherSum;
        }
    }

    // Rule: Sum has last digit 0
    if (sum % 10 == 0)
    {
        // Determine which company credit card belongs to
        long power = pow(10, length - 1);

        int d1 = (credit / power) % 10; // digit 1
        int d2 = (credit / (power / 10)) % 10; // digit 2

        // VISA
        if ((length == 13 || length == 16) && d1 == 4)
        {
            printf("VISA\n");
        }
        // American Express
        else if (length == 15 && d1 == 3 && (d2 == 4 || d2 == 7))
        {
            printf("AMEX\n");
        }
        // Mastercard
        else if (length == 16 && d1 == 5 && d2 >= 1 && d2 <= 5)
        {
            printf("MASTERCARD\n");
        }
        // Invalid (Doesn't match requirements)
        else
        {
            printf("INVALID\n");
        }
    }
    // Invalid (Doesn't end with 0)
    else
    {
        printf("INVALID\n");
    }
}