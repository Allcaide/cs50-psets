#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // get height limited to an interval (1 and 8)
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);

    int cycle = 1; // cycle variable to reinitialize the space variable with the correct number of
                   // cycles remaining

    // prince space variable
    int spvar = 1;
    int cardvar = height;
    // initialize the line counter
    for (int line = 0; line < height; line++)
    {
        // print a number of # until reaches column lenght   cardvar=height-1
        //                                                   cardvar=height-2
        //                                                   cardvar=height-3
        for (int card = cardvar; card <= height; card++)
        {
            while (spvar < height)
            {
                printf(" ");
                spvar++;
            }

            printf("#");
        }
        // reinitialize var
        cycle++;
        spvar = cycle;
        printf("\n");
        cardvar--;
    }
}
