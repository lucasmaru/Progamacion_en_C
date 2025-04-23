/*Genera archivo*/
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct producto {           //Producto
    short codigo;
    char nombre[20];
    float precio;
    double stock;
}producto;

int main (){
    FILE* f;
    int aux=0;
    producto p1;
    producto p2;
    producto p3;
    producto p4;

    p1.codigo =10;
    strcpy(p1.nombre,"quimico1");
    p1.precio=50;
    p1.stock=1.123;

    p2.codigo =20;
    strcpy(p2.nombre,"quimico2");
    p2.precio=5;
    p2.stock=0.321;

    p3.codigo =5;
    strcpy(p3.nombre,"quimico3");
    p3.precio=50;
    p3.stock=500;

    p4.codigo =1;
    strcpy(p4.nombre,"quimico4");
    p4.precio=46;
    p4.stock=1.301;
        
    f=fopen("stock.dat","wb");
    if(f==NULL){
        printf("Error al abrir el archivo\n\n");
        exit(1);
    }
    else{
        aux=fwrite(&p1,sizeof(p1),1,f);
        if(aux!=1){
            printf("Error al grabar\n");
            exit(2);
        }
        aux=fwrite(&p2,sizeof(p2),1,f);
        if(aux!=1){
            printf("Error al grabar\n");
            exit(3);
        }
        aux=fwrite(&p3,sizeof(p3),1,f);
        if(aux!=1){
            printf("Error al grabar\n");
            exit(4);
        }
        aux=fwrite(&p4,sizeof(p4),1,f);
        if(aux!=1){
            printf("Error al grabar\n");
            exit(5);
        }
        printf("Se guardaron los productos\n\n");
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo\n\n");
    }
    return 0;
}
