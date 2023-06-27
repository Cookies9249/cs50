#include <cs50.h>
#include <stdio.h>

int string_length(string word);

int main(void)
{
    string name = get_string("Name: ");

    /*
    int length = 0;
    while (name[length] != '\0')
    {
        i++;
    }*/

    int length = string_length(name);

    printf("%i\n",length);
}

int string_length(string word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }
    return i;
}

