#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt
    long first_number = get_long("First Number: ");
    long second_number = get_long("Second Number: ");

    // Calculation
    if (first_number > second_number)
    {
        printf("The First Number is Bigger than the Second Number\n");
    }
    else if (first_number < second_number)
    {
        printf("The First Number is Smaller than the First Number\n");
    }
    else
    {
        printf("The First Number and the Second Number are Equal\n");
    }
}