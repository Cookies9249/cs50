#include <cs50.h>
#include <stdio.h>

int main(void)
{
    /*
    POINTERS INTRO
    int n = 50;
    int *p = &n;

    printf("%p\n", p);
    printf("%p\n", &n);
    printf("%i\n", *p);
    */

    /*
    STRINGS AS POINTERS OF CHARS
    char *s = "HI!";
    printf("%s\n", s);
    */

    /*
    STRINGS IN CS50.H
    string s = "HI!";
    char *p = &s[0];
    printf("%p\n", s);
    printf("%p\n", p);
    */

    /*
    POINTER ARITHMETICS
    char *s = "HI!";
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));
    */

    /*
    POINTER ARITHEMETICS WITH INTS
    int numbers[] = {4, 6, 8, 2, 7, 5, 0};

    printf("%i\n", *numbers);
    printf("%i\n", *(numbers + 1));
    printf("%i\n", *(numbers + 2));
    printf("%i\n", *(numbers + 3));
    printf("%i\n", *(numbers + 4));
    printf("%i\n", *(numbers + 5));
    printf("%i\n", *(numbers + 6));
    */

    /*
    SUMMARY:
    int *p = &n sets p to location of int n

    printf("%p", &n) prints out location of n
    printf("%i", *p) prints out int at location p

    Strings are pointers for chars
    %s instructs program to go to location of char and print until '/0'

    Pointer arithmetic used to locate the next piece of data
    Arrays can be treated as the address of the first piece of data
    */
}