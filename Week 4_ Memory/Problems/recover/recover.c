#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: recover IMAGE\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");

    // Check from invalid file
    if (file == NULL)
    {
        printf("Image cannot be opened\n");
        return 1;
    }

    FILE *img = NULL;

    // Initialize variables
    BYTE buffer[BLOCK_SIZE]; // 512 B per block
    char file_name[8]; // 7 chars + '\0' = 8 B per file_name
    int count = 0;

    // For every block
    // Reads from file to buffer
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // If first JPEG
            if (count == 0)
            {
                // Sets new file_name to ###.jpg
                sprintf(file_name, "%03i.jpg", count);

                // Sets img to new file
                img = fopen(file_name, "w");

                // Writes from buffer to img
                fwrite(buffer, 1, BLOCK_SIZE, img);

                // Increment jpeg count
                count++;
            }
            // If not first JPEG
            else
            {
                // Close previous JPEG
                fclose(img);

                // Sets new file_name to ###.jpg (prints string to location of file_name)
                sprintf(file_name, "%03i.jpg", count);

                // Sets img to new file (opens file at location file_name)
                img = fopen(file_name, "w");

                // Writes from buffer to img
                fwrite(buffer, 1, BLOCK_SIZE, img);

                // Increment jpeg count
                count++;
            }
        }
        // If not start of new JPEG
        else if (count > 0)
        {
            // Writes from buffer to img
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }
    fclose(file);
    fclose(img);
}