#include <stdio.h>
#include <cs50.h>
#include <string.h>

/*
Main Points: strcmp to compare strings
*/

int main(void)
{
    string names[] = {"Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ronald"};

    for (int i = 0; i < 7; i++)
    {
        if (strcmp(names[i], "Ronald") == 0)
        {
            printf("Person Found!\n");
            return 0;
        }
    }
    printf("No Person Found!\n");
    return 1;
}