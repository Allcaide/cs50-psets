#include <stdio.h>
#include  <cs50.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");
    //type casting
    double z = (double) x/ (double) y;
    printf("%.20f\n", z );
}
