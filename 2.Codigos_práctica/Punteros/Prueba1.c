# include <stdio.h>
# include <stdlib.h>
 int main (){
    int *p;
    int i;
    int k;
    i = 42;
    k = i;
    p = &i;
    printf("El valor de i: %d \n",i);
    printf("El valor de p: %p \n",p);
    *p=75;
    printf("El valor de i: %d \n",i);
    return 0;
 }