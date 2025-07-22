#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_key_valid(string key);
string cipher(string text, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || (!is_key_valid(argv[1])))
    {
        printf("Error 1: Insert key (positive integer)\n");
        return 1;
    }

    // Atoi converts a series of number in a string to int
    int keyint = atoi(argv[1]);

    string plaintext = get_string("Plaintext: ");
    string cipheredtext = cipher(plaintext, keyint);
    printf("Ciphertext: %s\n", cipheredtext);
}

// Test the string present in argv[1], there for the i iterates through out all the values and
// garatees that there all integers
//
bool is_key_valid(string key)
{
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        if (!isdigit(key[i]))
        {
            return false;
        }
    }
    return true;
}

// Recieves the text and the key
// Setsup each caracter for the X position on the alphabet by subtracting the 'a' ou 'A'th position
// on the alfabet Uses the formula to adjust that position with the key sence it sums the key and
// goes for the rest of the division by 26 (number of character on the alphabet) Then adjusts the
// ASCII value ny adding the ASCII of 'a' or 'A' Then returns the text
string cipher(string text, int key)
{

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] >= 65 && text[i] <= 90)
        {
            char c = (text[i] - 65 + key) % 26;
            text[i] = c + 65;
        }
        else if (text[i] >= 97 && text[i] <= 122)
        {
            char c = (text[i] - 97 + key) % 26;
            text[i] = c + 97;
        }
    }
    return text;
}
