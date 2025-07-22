#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void upperstring(string s);
int main(void)
{
    string Player1 = get_string("Player 1: ");
    string Player2 = get_string("Player 2: ");

    // Make full string uppercase
    upperstring(Player1);
    upperstring(Player2);

    // introduce scoreboard
    int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    string scoreindex = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int Player1score = 0;
    int Player2score = 0;

    // Identify the score throgh the letter and adds the points for P1
    for (int i = 0, p1len = strlen(Player1); i < p1len; i++)
    {
        char letra = Player1[i];

        for (int j = 0, lensi = strlen(scoreindex); j < lensi; j++)
        {
            if (letra == scoreindex[j])
            {
                Player1score = Player1score + score[j];
            }
        }
    }
    // Identify the score throgh the letter and adds the points for P2
    for (int i = 0, p2len = strlen(Player2); i < p2len; i++)
    {
        char letra = Player2[i];

        for (int j = 0, lensi = strlen(scoreindex); j < lensi; j++)
        {
            if (letra == scoreindex[j])
            {
                Player2score = Player2score + score[j];
            }
        }
    }
    // Ifs to know who wins
    if (Player1score > Player2score)
    {
        printf("Player 1 wins!\n");
    }
    else if (Player1score < Player2score)
    {
        printf("Player 2 wins!\n");
    }
    else
        printf("Tie!\n");
}

// Function the uppercase the full string char by char
void upperstring(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        s[i] = toupper(s[i]);
    }
    return;
}
