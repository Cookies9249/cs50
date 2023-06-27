#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

// Array Examples

int main(void)
/*{
    int n = get_int("How many scores? ");

    int scores[n];

    for (int i = 0; i < n; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);
}*/

{
    string s = "hi0f";
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isalpha(s[i]) == 0)
        {
            count++;
        }
    }
    printf("%i\n", count);
}