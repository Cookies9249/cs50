#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Create height variable
    int height = 0;

    do
    {
        // Getting an input
        height = get_int("Height: ");
    }
    // Validating the input
    while (height < 1 || height > 8);

    // For each row
    for (int row = 0; row < height; row++)
    {
        // For the spaces before the stairs
        for (int i = 0; i < height - row - 1; i++)
        {
            printf(" ");
        }

        // For the first set of stairs
        for (int i = 0; i <= row; i++)
        {
            printf("#");
        }

        // For the space in between the stairs
        printf("  ");

        // For the second set of stairs
        for (int i = 0; i <= row; i++)
        {
            printf("#");
        }

        // Move to the next row
        printf("\n");
    }
}