#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

// Initiate Functions
int count_letters(string word);
int count_words(string word);
int count_sentences(string word);

int main(void)
{
    // Get Input of Text from User
    string input = get_string("Text: ");

    // Determine Number of Letters, Sentences, and Words
    float letters = count_letters(input);
    float sentences =  count_sentences(input);
    float words = count_words(input);

    // Calculate L and S in Coleman-Liau Index
    float varL = letters / words * 100.0;
    float varS = sentences / words * 100.0;

    // Calculate Coleman-Liau Index
    int index = round(0.0588 * varL - 0.296 * varS - 15.8);

    // Print Index to User
    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    printf("Letters: %f\n", letters);
    printf("Words: %f\n", words);
    printf("Sentences: %f\n", sentences);
    printf("L: %f\n", varL);
    printf("S: %f\n", varS);
    printf("%f\n", 0.0588 * varL - 0.296 * varS - 15.8);
}

// Count Number of Letters (alphanumeric characters)
int count_letters(string word)
{
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalnum(word[i]))
        {
            count++;
        }
    }
    return count;
}

// Count Number of Words (spaces)
int count_words(string word)
{
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Ascii 32 = " "
        if (word[i] == 32)
        {
            count++;
        }
    }
    return count + 1;
}

// Count Number of Sentences (".", "!", "?")
int count_sentences(string word)
{
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Ascii 46 = ".", Ascii 33 = "!", Ascii 63 = "?"
        if (word[i] == 46 || word[i] == 33 || word[i] == 63)
        {
            count++;
        }
    }
    return count;
}