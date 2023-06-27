#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *s = mollac(4);
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);

    free(s);
}

/*
SCANF
scanf("%", &x)

Scans for an input from user
    Expected value type from %
    Assigns output to values at address of x (&x)

Doesn't work individually with strings (needs mollac)
*/