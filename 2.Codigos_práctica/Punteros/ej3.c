/*Escribir un programa que imprima los elementos de un vector de enteros en orden
inverso utilizando punteros (no usar subíndices []).*/
# include <stdio.h>
# include <stdlib.h>
 int main (){
    int v[10] = {1,2,3,4,5,6,7,8,9,10};
    int *p;
    int i;
    p=&v[0];
    for(i=0;i<10;i++){
        printf("%d ",*p+(9-i));
    }

 }
