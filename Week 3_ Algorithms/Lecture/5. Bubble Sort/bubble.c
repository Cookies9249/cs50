#include <cs50.h>
#include <stdio.h>
#define SIZE 10

int main(void)
{
    int array[] = {1, 2, 2, 4, 5, 1, 5, 8, 9, 10};
    int place;

    for (int i = 0; i < SIZE - 1; i++)
    {
        // for pair j
        for (int j = 0; j < SIZE; j++)
        {
            if (array[j] < array[j + 1])
            {
                place = array[j];
                array[j] = array[j + 1];
                array[j + 1] = place;
            }
        }
    }

    // print
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}