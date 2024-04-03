// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    int bytes = 0;
    while (fgetc(input) != EOF)
    {
        bytes++;
    }
    bytes = bytes - HEADER_SIZE;
    fclose(input);
    fopen(argv[1], "r");
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // atof converts a string to a float. Volume in this case is a fraction

    // TODO: Copy header from input file to output file
    // Reading the first Header_size bytes from input.wav and writing them to output.wav. Writing them will delete
    // previous contents making the header always start at the beginning of the file.

    uint8_t header[HEADER_SIZE];

    int16_t buffer;
    // Initialize an int buffer to store read values and do operations on

    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    // This reads the input file and reads the first HEADER_SIZE amount of uint_8 bytes and stores them in an array
    // called header

    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
    // This writes those read bytes to the new output file. Now must append outpt with new volume results. append
    // won't replace data like write will.


    // TODO: Read samples from input file and write updated data to output file

    // Initialize an int buffer to store read values and do operations on

    // int to make sure we aren't appending another header
    for ( int i = 0; i < (bytes/2); i++)
        //read only when not end of file
    {
        fread(&buffer, sizeof(int16_t), 1, input);

        buffer = factor * buffer;
        // Apply volume operation

        fwrite(&buffer, sizeof(int16_t), 1, output);
        //write to new file
    }

    // Close files
    fclose(input);
    fclose(output);
}
