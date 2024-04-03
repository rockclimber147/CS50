#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Make sure only one argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    typedef uint8_t BYTE;

    // Make array to store 512 bytes

    BYTE data[512];

    // Make string to store numerals (make sure to include \0 to end string)

    char fname[8];

    int i = 0;

    int firstheader = 0;

    FILE *img;

    while (fread(data, 1, 512, input) == 512)
    {
        while ((firstheader == 0) && (fread(data, 1, 512, input) == 512))
        {

            // Scan through data until the first header is encountered then break out

            if ((data[0] == 0xff) && (data[1] == 0xd8) && (data[2] == 0xff) && ((data[3] & 0xf0) == 0xe0))
            {
                firstheader++;
            }
        }

        // Scan for headers

        if ((data[0] == 0xff) && (data[1] == 0xd8) && (data[2] == 0xff) && ((data[3] & 0xf0) == 0xe0))
        {

            //Close previous file unless it's the first one

            if (i > 0)
            {
                fclose(img);
            }
            sprintf(fname, "%03i.jpg", i);
            img = fopen(fname, "w");
            i++;
        }
        fwrite(data, 1, 512, img);
    }
    fclose(img);
    fclose(input);
    return 0;
}