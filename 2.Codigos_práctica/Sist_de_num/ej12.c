# include <stdio.h>

int* dec_a_bin(int n){
    int cociente,i=0;
    int* vec=NULL;
    if (n==0)
        printf("El decimal %d en binario vale 0 ",n);
    if (n==1)
        printf("El decimal %d en binario vale 1",n);
    else{
        do {
            if(cociente=n/2 >=1)
                vec[7-i]=n%2;
            i++;
        }while (cociente>1);
    }
}

int main (){
    int valor;
    int* bin;
    printf("Ingrese un entero ");
    scanf("%d",&valor);
    bin=dec_a_bin(valor);
}