#include <cs50.h>
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Recieve an integer to put on cash var, bigger than 0
    int cash;
    do
    {
        cash = get_int("Change owed: ");
    }
    while (cash < 0);

    // Way to count how many pennys, but adding on to them
    int penny_counter = 0;

    int penny_25 = 25;
    int penny_10 = 10;
    int penny_5 = 5;
    int penny_1 = 1;

    // Removing the cash from bigger to smaller
    while (cash >= penny_25)
    {
        cash = cash - penny_25;
        penny_counter++;
    }
    while (cash >= penny_10)
    {
        cash = cash - penny_10;
        penny_counter++;
    }
    while (cash >= penny_5)
    {
        cash = cash - penny_5;
        penny_counter++;
    }
    while (cash >= penny_1)
    {
        cash = cash - penny_1;
        penny_counter++;
    }
    printf("%i\n", penny_counter);
}
