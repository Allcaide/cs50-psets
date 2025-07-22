// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    uint8_t header[HEADER_SIZE]; // Declarar array do tipo uint8_8(8 bits or 1 byte) com tamanho 44
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    int16_t buffer; // Dado para percorrer 2bytes at a time

    while (fread(&buffer, sizeof(int16_t), 1,
                 input)) //(Lê do input 2 bytes a dois bytes para futuramente escrever no buffer. o
                         //valor que lê fica anexado ao buffer no endereço que eu lhe dei)
    { // Aproveitamos que o é valor a valor e fazemos que enquanto lê um valor, corre o input
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // TODO: Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}
