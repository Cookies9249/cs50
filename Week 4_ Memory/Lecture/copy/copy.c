#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");

    char *t = malloc(strlen(s) + 1);

    // Error in case of lack of RAM
    if (t == NULL)
    {
        return 1;
    }

    for (int i = 0, n = strlen(s) + 1; i < n; i++)
    {
        t[i] = s[i];
    }

    /*
    Alternatively, replace for loop with a function from string.h:
    strcpy(t, s);
    */

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);
    return 0;

    /*
    INCORRECT METHOD TO COPY A STRING
    string s = get_string("s: ");

    // this copies the POINTER
    string t = s;

    t[0] = toupper(t[0]);

    printf("s: %s\n", s);
    printf("t: %s\n", t);
    */
}