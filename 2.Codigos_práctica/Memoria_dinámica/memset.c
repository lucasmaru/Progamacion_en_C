#include <stdio.h>
#include <string.h>

int main ()
{
     char str[50];

     strcpy(str,"Probando la funcion mem set");
     printf("%s \n",str);

     memset(str,'l',3);
     puts(str);

     return(0);
}