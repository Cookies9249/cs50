#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Global Variables
#define SIZE 10
int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Initialize functions
void sort(int start, int end);
void merge(int start, int middle, int end);

// Main function
int main(void)
{
    // Declare Variables
    int start = 0;
    int end = SIZE - 1;

    // Start Sort
    sort(start, end);

    // Print Result
    for (int i = 0; i < SIZE; i++)
    {
        printf("%i\n", numbers[i]);
    }
}

void sort(int start, int end)
{
    // If only one number, quit
    if (start == end)
    {
        return;
    }
    else
    {
        int middle = (start + end) / 2;

        // Sort Left Side
        sort(start, middle);

        // Sort Right Side
        sort(middle + 1, end);

        // Merge Two Sides
        merge(start, middle + 1, end);
    }

    return;
}

void merge(int start, int middle, int end)
{
    // Initialize Variables
    int size = end - start + 1;
    int output[size];
    int left = start;
    int right = middle;

    // Sort Numbers
    for (int i = 0; i < size; i++)
    {
        // If the Right-Side Number is Larger
        if ((numbers[left] <= numbers[right] || right > end) && left < middle)
        {
            output[i] = numbers[left];
            left++;
        }
        // If the Left-Side Number is Larger
        else
        {
            output[i] = numbers[right];
            right++;
        }
    }

    // Copy Result into Original Array
    for (int i = 0; i < size; i++)
    {
        numbers[start + i] = output[i];
    }

    return;
}