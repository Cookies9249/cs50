#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string do_cipher(string word, string key);
int find_nonalpha(string s);
int find_repeats(string s);
string convert_upper(string s);

int main(int argc, string argv[]) // argc is int (# of words), argv = array of words
{
    /* GET KEY */
    string key = argv[1];

    /* VALIADATE KEY */
    // check no input or too many outputs
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        // convert key to uppercase
        key = convert_upper(key);

        int nonalpha = find_nonalpha(key);
        int length = strlen(key);
        int repeats = find_repeats(key);

        // check non-alphabetical characters
        if (nonalpha > 0)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }

        // check key length
        else if (length != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

        // check repeated characters
        else if (repeats != 26)
        {
            printf("Key must not contain repeated characters..\n");
            return 1;
        }

        else
        {
            /* GET PLAINTEXT */
            string input = get_string("plaintext:  ");

            /* ENCIPHER */
            string ciphertext = do_cipher(input, key);

            /* PRINT CIPHERTEXT */
            printf("ciphertext: %s\n", ciphertext);
        }
    }
}

string convert_upper(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // find case
        if (islower(s[i]))
        {
            s[i] = s[i] - 32;
        }
    }
    return s;
}

int find_nonalpha(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isalpha(s[i]) == 0)
        {
            count++;
        }
    }
    return count;
}

int find_repeats(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (s[j] == s[i])
            {
                count++;
            }
        }
    }
    return count;
}

string do_cipher(string word, string key)
{
    int cipher = 0;

    // for every letter
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // find case
        if (isupper(word[i]))
        {
            // change char from a-z to 0-25
            cipher = word[i] - 65;
            // find position in key and change input
            word[i] = key[cipher];
        }
        else if (islower(word[i]))
        {
            // change char from a-z to 0-25
            cipher = word[i] - 97;
            // find position in key and change input
            word[i] = key[cipher] + 32;
        }
    }
    return word;
}