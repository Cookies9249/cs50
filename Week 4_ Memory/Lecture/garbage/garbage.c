#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int scores[3];

    for (int i = 0; i < 3; i++)
    {
        printf("%i\n", scores[i]);
    }
}

/*
GARBAGE VALUES
When no values are initialized for a variable, garbage values are used by the computer
Remnants of random stuff from computer
Bad; a cause for hacking
*/