#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char c1 = 'H';
    char c2 = 'I';
    char c3 = '!';

    printf("%i %i %i\n", c1, c2, c3);

    // equivalent to

    string w = "HI!";

    printf("%i %i %i\n", w[0], w[1], w[2]);
}