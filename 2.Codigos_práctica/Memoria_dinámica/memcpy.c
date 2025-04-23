#include <stdio.h>
#include <string.h>

int main ()
{
    char a[]="abcdefghijklmnñopqrstuvwxyz";
    char b[28];//las 27 letras mas el fin de cadena
    memcpy(b,a,sizeof(a));
    printf("b: %s",b);

    

    return(0);
}