#include <stdio.h>
#include <cs50.h>

/*
Main Points:
    int numbers[] = {...} to specify arrays
    linear search
*/

int main(void)
{
    int numbers[] = {4, 6, 8, 2, 7, 5, 0};

    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == -1)
        {
            printf("Found in Position %i\n", i+1);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}