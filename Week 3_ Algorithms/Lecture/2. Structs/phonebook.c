#include <stdio.h>
#include <cs50.h>
#include <string.h>

/*
Main Points:
    data structures ():

    (above int main)
    typedef struct
    {
        string string_name1;
        string string_name2;
    }
    struct_name;

    (in int main - declaring array)
    struct_name array_name[]

    (in int main - using array)
    array_name.string_name1 = ...
    array_name.string_name2 = ...
*/

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    people[0].name = "Carter";
    people[0].number = "+1-123-456-7890";

    people[0].name = "David";
    people[0].number = "+1-345-678-9012";

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[0].name, "David") == 0)
        {
            printf("Phone number is %s\n", people[0].number);
            return 0;
        }
    }

    printf("Person not found\n");
    return 1;
}