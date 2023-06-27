#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declare name variable and get name input
    string name = get_string("What is Your Name? ");

    // print hello with name
    printf("hello, %s\n", name);
}
