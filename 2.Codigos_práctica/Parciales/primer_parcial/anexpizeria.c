//Creo el archivo preciosproductos.dat para el programa pizeria
#include <stdlib.h>
# include <stdio.h>

int main (){
    FILE* f;
    char variedad [20];
    float precio;
    int i,r,aux1=0,aux2=0;

    f=fopen("preciosproductos.dat","wb");//Abro el archivo
    if (f==NULL){
        printf("\nError al abrir el archivo");
        exit(1);
    }

    for(i=0;i<10;i++){
        printf("\nIngrese nombre de la variedad: ");
        scanf( "%s",variedad);
        printf("\nIngrese el precio: ");
        scanf("%f",&precio);
        r=fwrite(variedad,sizeof(variedad),1,f);
        if(r!=1){
            printf("\nError al guardar la variedad");
            exit(2);
        }
        aux1++;
        r=fwrite(&precio,sizeof(precio),1,f);
        if(r!=1){
            printf("\nError al guardar el precio");
            exit(3);
        }
        aux2++;
    }

    if(aux1==10 && aux2==10)
        printf("\nSe guardaron correctamente los archivos");

    if (fclose(f) !=0){
        printf("\nError al cerrar el archivo");
        exit(4);
    }
    else
        printf("\nSe cerró el archivo correctamente.");

}