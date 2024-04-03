#include <stdio.h>
#include <math.h>

typedef struct
{
    int rgbtRed;
    int rgbtGreen;
    int rgbtBlue;
}
RGBTRIPLE;

RGBTRIPLE edge1px(int height, int width, RGBTRIPLE image[height][width], int pixelx, int pixely);

int main(void)
{

    int height = 3;
    int width = 3;

    RGBTRIPLE image[height][width];

    // Make image same as one used in check50

    image[0][0].rgbtRed = 0;
    image[0][1].rgbtRed = 0;
    image[0][2].rgbtRed = 40;
    image[1][0].rgbtRed = 20;
    image[1][1].rgbtRed = 30;
    image[1][2].rgbtRed = 80;
    image[2][0].rgbtRed = 20;
    image[2][1].rgbtRed = 30;
    image[2][2].rgbtRed = 50;

    image[0][0].rgbtGreen = 10;
    image[0][1].rgbtGreen = 10;
    image[0][2].rgbtGreen = 60;
    image[1][0].rgbtGreen = 30;
    image[1][1].rgbtGreen = 40;
    image[1][2].rgbtGreen = 70;
    image[2][0].rgbtGreen = 20;
    image[2][1].rgbtGreen = 10;
    image[2][2].rgbtGreen = 40;

    image[0][0].rgbtBlue = 25;
    image[0][1].rgbtBlue = 30;
    image[0][2].rgbtBlue = 80;
    image[1][0].rgbtBlue = 90;
    image[1][1].rgbtBlue = 100;
    image[1][2].rgbtBlue = 90;
    image[2][0].rgbtBlue = 40;
    image[2][1].rgbtBlue = 30;
    image[2][2].rgbtBlue = 10;


    RGBTRIPLE storedimg[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            storedimg[i][j] = edge1px(height, width, image, j, i);
        }
    }
        for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = storedimg[i][j];
            printf("%i %i %i \n", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
    }
}

RGBTRIPLE edge1px(int height, int width, RGBTRIPLE image[height][width],int pixelx,int pixely)
{
    int Gx[3][3];
    int Gy[3][3];

    // Make Gx array

    Gx[0][0] = -1;
    Gx[1][0] = 0;
    Gx[2][0] = 1;
    Gx[0][1] = -2;
    Gx[1][1] = 0;
    Gx[2][1] = 2;
    Gx[0][2] = -1;
    Gx[1][2] = 0;
    Gx[2][2] = 1;

    // Make Gy array

    Gy[0][0] = -1;
    Gy[1][0] = -2;
    Gy[2][0] = -1;
    Gy[0][1] = 0;
    Gy[1][1] = 0;
    Gy[2][1] = 0;
    Gy[0][2] = 1;
    Gy[1][2] = 2;
    Gy[2][2] = 1;

    // Make container for 3 color values and sums for all color values for Gx and Gy

    RGBTRIPLE edged;

    int sumGxR = 0;
    int sumGxG = 0;
    int sumGxB = 0;
    int sumGyR = 0;
    int sumGyG = 0;
    int sumGyB = 0;

    // Make a loop doing all adjacent cells to the currently focused cell

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            // make it ignore pixels outside of the actual frame, skip if any number is less than zero or G/E height or width.

            if (((pixelx - 1 + j) >= 0 && (pixely - 1 + i) >= 0 ) && ((pixelx - 1 + j) < width && (pixely - 1 + i) < height))
            {
                sumGxR = sumGxR + (image[pixely - 1 + i][pixelx - 1 + j].rgbtRed * Gx[j][i]);
                sumGxG = sumGxG + (image[pixely - 1 + i][pixelx - 1 + j].rgbtGreen * Gx[j][i]);
                sumGxB = sumGxB + (image[pixely - 1 + i][pixelx - 1 + j].rgbtBlue * Gx[j][i]);

                sumGyR = sumGyR + (image[pixely - 1 + i][pixelx - 1 + j].rgbtRed * Gy[j][i]);
                sumGyG = sumGyG + (image[pixely - 1 + i][pixelx - 1 + j].rgbtGreen * Gy[j][i]);
                sumGyB = sumGyB + (image[pixely - 1 + i][pixelx - 1 + j].rgbtBlue * Gy[j][i]);
            }
        }
    }

    // Do math

    edged.rgbtRed = round (sqrt ((sumGxR * sumGxR) + (sumGyR * sumGyR)));
    edged.rgbtGreen = round (sqrt ((sumGxG * sumGxG) + (sumGyG * sumGyG)));
    edged.rgbtBlue = round (sqrt ((sumGxB * sumGxB) + (sumGyB * sumGyB)));

    // Make sure everything is capped at 255

    if (edged.rgbtRed >= 255)
    {
        edged.rgbtRed = 255;
    }
    if (edged.rgbtGreen >= 255)
    {
        edged.rgbtGreen = 255;
    }
    if (edged.rgbtBlue >= 255)
    {
        edged.rgbtBlue = 255;
    }
    return edged;
}