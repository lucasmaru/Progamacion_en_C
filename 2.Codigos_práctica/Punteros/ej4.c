/*Escribir una función que reciba un vector de enteros y su tamaño, y devuelva la
cantidad de números impares que contiene.*/
# include <stdio.h>
# include <stdlib.h>
#define M 10
int impares (int *v, int tam){
    int res=0, i;
    for(i=0;i<=tam;i++){
        if (*(v+i)%2==1){
                res++;
        }
    }
    return res;
}
int main (){
    int imp;
    int vec[M]={1,33,3,4,5,6,7,8,9,10};
    imp = impares(vec,M);
    printf("%d",imp);
    return 0;
}