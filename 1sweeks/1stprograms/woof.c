#include <stdio.h>
#include <cs50.h>

void meow (int n);


int main(void)
{
int meows_number = get_int("how many meows?");
meow(meows_number);
}


void meow ( int n)
{
        for (int i = 0 ; i<n ; i++)
    {
           printf("meow\n");
    }

}
