#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbav;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Changing the constant 3 to 3.0000 did the trick rearding rounding errors (before it would omit the decimals, leading it to erroneously round down)

            rgbav = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0000;
            rgbav = round(rgbav);
            image[i][j].rgbtRed = rgbav;
            image[i][j].rgbtBlue = rgbav;
            image[i][j].rgbtGreen = rgbav;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare variables to be used to store the original and sepia values of each color BECAUSE I DON'T WANT TO KEEP TYPING image[i][j].rgbwhatever OVER AND OVER AGAIN.

    int ro;
    int go;
    int bo;
    int rs;
    int gs;
    int bs;

    // Loop over each row

    for (int i = 0; i < height; i++)
    {
        // Loop over each column

        for (int j = 0; j < width; j++)
        {
            //store original values in variables

            ro = image[i][j].rgbtRed;
            go = image[i][j].rgbtGreen;
            bo = image[i][j].rgbtBlue;

            // Apply sepia corrections

            rs = round(.393 * ro + .769 * go + .189 * bo);
            gs = round(.349 * ro + .686 * go + .168 * bo);
            bs = round(.272 * ro + .534 * go + .131 * bo);

            // Make sure values are 255 or less

            if (rs > 255)
            {
                rs = 255;
            }
            if (gs > 255)
            {
                gs = 255;
            }
            if (bs > 255)
            {
                bs = 255;
            }

            // Store pixel information in original array

            image[i][j].rgbtRed = rs;
            image[i][j].rgbtGreen = gs;
            image[i][j].rgbtBlue = bs;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int rightr;
    int rightg;
    int rightb;

    // Loop over all rows

    for (int i = 0; i < height; i++)
    {
        // Loop over left half of pixels (odd numbers should discard the .5, keeping things symmetrical)
        // NOTE TO FUTURE SELF: You messed up the 0 indexing of arrays by trying just width/2 as opposed to the correct (width - 1) / 2. Underlying logic was correct but small offsets happened because of this. Also note the <= as opposed to the < for the i loop.
        // i is zero indexed like height is so the last place can be discarded. We can't just divide width by 2 as j will reach a higher number than it should due to width being the amount of zero indexed places. J goes up to and including the zero indexed midpoint.
        // Odd numbers will have a central column that won't change, but dividing by 2 and keepint it as an integer will round it down, conveniently skipping this column. Even if it didn't, we'd be shuffling the same numbers around. Should be good.

        for (int j = 0; j <= ((width - 1) / 2); j++)
        {
            // Store right side pixels. array iz 0 indexed so take width - (j + 1) to get mirror image

            rightr = image[i][width - (j + 1)].rgbtRed;
            rightg = image[i][width - (j + 1)].rgbtGreen;
            rightb = image[i][width - (j + 1)].rgbtBlue;

            // Right side is now left side

            image[i][width - (j + 1)].rgbtRed = image[i][j].rgbtRed;
            image[i][width - (j + 1)].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - (j + 1)].rgbtBlue = image[i][j].rgbtBlue;

            // Left side is now stored right side

            image[i][j].rgbtRed = rightr;
            image[i][j].rgbtGreen = rightg;
            image[i][j].rgbtBlue = rightb;
        }
    }
    return;
}

RGBTRIPLE blur1px(int height, int width, RGBTRIPLE image[height][width], int i1, int i2, int j1, int j2, float pixelamnt);

// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // This involves the use of storage arrays as we change the pixels based on the surrounding ones, and we need those values for multiple calcs.
    // edges and corners will use less neighboring pixels so must be treated differently.

    // Start by blurring edges and corners and storing them in a new array to preserve the original values

    // Make arrays to store edges

    RGBTRIPLE topedge[width];
    RGBTRIPLE bottomedge[width];
    RGBTRIPLE leftedge[height];
    RGBTRIPLE rightedge[height];

    //Populate arrays with corners

    topedge[0] = blur1px(height, width, image, 0, 1, 0, 1, 4.000);
    topedge[width - 1] = blur1px(height, width, image, 0, 1, (width - 2), (width - 1), 4.000);
    bottomedge[0] = blur1px(height, width, image, (height - 2), (height - 1), 0, 1, 4.000);
    bottomedge[width - 1] = blur1px(height, width, image, (height - 2), (height - 1), (width - 2), (width - 1), 4.000);

    // Populate edges
    // Top and bottom edge have the corner values, so no need to use left/right edge corners.

    for (int j = 1; j <= (width - 2); j++)
    {
        topedge[j] = blur1px(height, width, image, 0, 1, (j - 1), (j + 1), 6.000);
        bottomedge[j] = blur1px(height, width, image, (height - 2), (height - 1), (j - 1), (j + 1), 6.000);

    }
    for (int i = 1; i <= (height - 2); i++)
    {
        leftedge[i] = blur1px(height, width, image, (i - 1), (i + 1), (0), (1), 6.000);
        rightedge[i] = blur1px(height, width, image, (i - 1), (i + 1), (width - 2), (width - 1), 6.000);
    }

    // Now that edges are stored in arrays, the main body can be changed uniformly with the edges added in last.
    // Need to blur from image[1][1] to image[(height - 2)][(width - 2)]
    // Could copy image or do something more elegant?

    // Prime transient arrays

    RGBTRIPLE leadblur[width - 2];
    RGBTRIPLE lagblur[width - 2];

    for (int j = 1; j <= (width - 2); j++)
    {
        lagblur[j - 1] = blur1px(height, width, image, 0, 2, (j - 1), (j + 1), 9.000);
        leadblur[j - 1] = blur1px(height, width, image, 1, 3, (j - 1), (j + 1), 9.000);
    }
    // Arrays now hold first two rows of blurred pixels
    // make first row (row n) of 3x3 blurred pixels = lastrgb
    // make lastrgb = currentrgb
    // make currentrgb = bluripx( row n + 2)
    // repeat until currentrgb is populated with blurred pixels from row height - 2
    if (height > 3)
    {
        for (int i = 1; i <= (height - 5); i++)
        {
            for (int j = 1; j <= (width - 2); j++)
            {
                image[i][j] = lagblur[j - 1];
                lagblur[j - 1] = leadblur[j - 1];
                leadblur[j - 1] = blur1px(height, width, image, i + 2, i + 4, j - 1, j + 1, 9.000);
            }
        }


        // populate last 2 3x3 rows

        for (int j = 1; j <= width - 2; j++)
        {
            image[height - 3][j] = lagblur[j - 1];
            image[height - 2][j] = leadblur[j - 1];
        }
    }
    else
    {
        image[1][1] = blur1px(height, width, image, 0, 2, 0, 2, 9.000);
    }

    // Populate perimeter with blurred pixels

    // Top, bottom with corners

    for (int j = 0; j <= (width - 1); j++)
    {
        image[0][j] = topedge[j];
        image[height - 1][j] = bottomedge[j];
    }

    // Left, Right edges have no corners

    for (int i = 1; i <= (height - 2); i++)
    {
        image[i][0] = leftedge[i];
        image[i][width - 1] = rightedge[i];
    }

    return;
}

RGBTRIPLE blur1px(int height, int width, RGBTRIPLE image[height][width], int i1, int i2, int j1, int j2, float pixelamnt)
{
    RGBTRIPLE blurredpx;

    // Make variables to store numerical sum of each color

    int totalred = 0;
    int totalgreen = 0;
    int totalblue = 0;

    // Loop from start to finish inclusive values given when function is called.

    for (int i = i1; i <= i2; i++)
    {
        for (int j = j1; j <= j2; j++)
        {
            totalred = totalred + image[i][j].rgbtRed;
            totalgreen = totalgreen + image[i][j].rgbtGreen;
            totalblue = totalblue + image[i][j].rgbtBlue;
        }
    }

    // Give blurredpx struct the values.

    blurredpx.rgbtRed = round(totalred / pixelamnt);
    blurredpx.rgbtGreen = round(totalgreen / pixelamnt);
    blurredpx.rgbtBlue = round(totalblue / pixelamnt);

    //return the blurredpx

    return blurredpx;
}