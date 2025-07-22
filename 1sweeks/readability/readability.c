#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float L = 100 * letters / words;
    float S = 100 * sentences / words;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("%f", L);
    // Print the grade level
    // printf("Número de letras: %i\n", letters);
    // printf("Número de palavras: %i\n", words);
    // printf("Número de index: %f\n", index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int grade = round(index);
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int sum = 0;
    // Return the number of letters in text
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char letter = text[i];
        if (((char) letter <= 90 && (char) letter >= 65) ||
            ((char) letter <= 122 && (char) letter >= 97))
        {
            sum++;
        }
    }
    return sum;
}

int count_words(string text)
{
    int count = 1;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
        if (text[i] == (char) 39)
        {
            count++;
        }
        if (text[i] == '-')
        {
            count++;
        }
    }

    // Return the number of words in text
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    int len = strlen(text);

    // Return the number of sentences in text
    for (int i = 0; i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}
