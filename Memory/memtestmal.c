#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{

    char *s = get_string("s: ");

    char *t = malloc(strlen(s) + 1 );

    string a = t;
    string *b = &t;


    for ( int i = 0, n = strlen(s); i < n; i++)
    {
        t[i] = s[i];
    }

    if ( strlen > 0 )
    {
        t[0] = toupper(t[0]);
    }
        printf("%s\n", t);

    *t = 1; //O endereço remete para a primeira posição, se imprimirmos a string imprime tudo
    printf("%i%s\n", t[0],t);

    printf("string a que era suposto ser igual à s: %s\n", a);
    printf("string *b=&t  ºp: %p\n", *b);
    printf("string *b=&t  ºs:: %s\n", *b);
    printf("string *b=&t  º(p+1):: %p\n", *(b+1));
    printf("string *b=&t  º(s+1):: %s\n", *(b+1));

    printf("string *s  ºs:: %p\n", &s);

    for ( int i = 0; i < strlen(*b); i++)
    {
        printf("%d\n", (unsigned char)(*b)[i]);
    }
}
