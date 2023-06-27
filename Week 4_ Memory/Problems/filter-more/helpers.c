#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average out RGB values
            int gray = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set RBG to new grayscale value
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    for (int i = 0; i < height; i++)
    {
        // For each pixel on one half
        for (int j = 0; j < width / 2; j++)
        {
            // Swap left and right pixels
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = 0;
            float green = 0;
            float blue = 0;
            float pixel = 0;

            // For each pixel in 3x3 square
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // Ensures pixels are in image
                    if (i + k >= 0 && i + k <= height - 1 && j + l >= 0 && j + l <= width - 1)
                    {
                        // Add RGB values to RGB variables
                        red += image[i + k][j + l].rgbtRed;
                        green += image[i + k][j + l].rgbtGreen;
                        blue += image[i + k][j + l].rgbtBlue;
                        pixel++;
                    }
                }
            }

            // Set output to average of RGB variables
            tmp[i][j].rgbtRed = round(red / pixel);
            tmp[i][j].rgbtGreen = round(green / pixel);
            tmp[i][j].rgbtBlue = round(blue / pixel);
        }
    }

    // Copy output into original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // For each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Gx and Gy for 3x3 pixels
            int gxR = 0;
            int gxG = 0;
            int gxB = 0;
            int gyR = 0;
            int gyG = 0;
            int gyB = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k >= 0 && i + k <= height - 1 && j + l >= 0 && j + l <= width - 1)
                    {

                        // Add RGB values with corresponding multipliers
                        gxR += gx[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        gxG += gx[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        gxB += gx[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;

                        gyR += gy[k + 1][l + 1] * image[i + k][j + l].rgbtRed;
                        gyG += gy[k + 1][l + 1] * image[i + k][j + l].rgbtGreen;
                        gyB += gy[k + 1][l + 1] * image[i + k][j + l].rgbtBlue;
                    }
                }
            }

            // Final RGB values
            int red = round(sqrt(pow(gxR, 2) + pow(gyR, 2)));
            int green = round(sqrt(pow(gxG, 2) + pow(gyG, 2)));
            int blue = round(sqrt(pow(gxB, 2) + pow(gyB, 2)));

            // Set output image RGB values and cap at 255
            tmp[i][j].rgbtRed = (red > 255) ? 255 : red;
            tmp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            tmp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }

    // Copy output into original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
