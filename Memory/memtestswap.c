#include <stdio.h>



void swap(int *a, int *b);

int main(void)
{

    int x = 1;
    int y = 2;
    swap( &x, &y);
    printf("%i , %i \n", x , y );

    printf("endereço de x %p , e de y %p \b", &x , &y );

    printf("valor contido no endereço de x %i", *x);

}

void swap( int *a , int *b )
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}
