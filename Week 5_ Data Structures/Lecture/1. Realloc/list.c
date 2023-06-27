#include <stdio.h>
#include <stdlib.h>

/*
Realloc Summary:

To add on to an already declared array, a:
    1. Allocate tmp array with more space
    2. Copy numbers from original to tmp
    3. Free original array
    4. Add on to tmp
    5. Set original to tmp

!!! Realloc does steps 1 to 3 !!!
*/

int main(void)
{
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Time Passes

    int *tmp = realloc(list, 4 * sizeof(int));
    // Creates tmp with size 4 * sizeof(int) + copies list to tmp

    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    /*
    // Alternatively
    int *tmp = malloc(4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }
    tmp[3] = 4;

    free(list);
    */

    list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list);
    return 0;
}