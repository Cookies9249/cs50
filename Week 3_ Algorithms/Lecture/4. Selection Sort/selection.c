#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 10; // size of array
    int numbers[] = {3, 7, 6, 5, 9, 4, 8, 2, 1, 0};

    int small = 0;
    int location = 0;

    for (int i = 0; i < n; i++)
    {
        small = n + 1;

        // find smallest number
        for (int j = i; j < n; j++)
        {
            if (numbers[j] < small)
            {
                small = numbers[j];
                location = j;
            }
        }

        // switch
        numbers[location] = numbers[i];
        numbers[i] = small;

        printf("%i\n", numbers[i]);
    }
}