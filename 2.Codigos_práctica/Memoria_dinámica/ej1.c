/*1. Escribir un prog. en el que el usuario informa la cantidad de elementos que va a
ingresar y luego los valores de los elementos (enteros).
Los elementos deben almacenarse en un vector y luego en el archivo vector.dat. No
se debe limitar la cantidad de elementos.
*/
# include <stdio.h>
# include <stdlib.h>

int* carga_elem(int cant){
    int elem,i=0;
    int* vec=NULL;
    vec= (int*) realloc (vec,sizeof(int) * cant);//Reservo un bloque de memoria del tamaño solicitado por el usuario
    if (vec != NULL){
        printf("Ingrese el primer elemento: ");
        scanf("%d",&elem);
        while(elem != 0 && (i+1)<cant){
            *(vec+i) = elem;
            i++;
            printf("Ingrese el siguiente elemento o 0 para salir: ");
            scanf("%d",&elem);
            //printf("%d\n",cant);
            //printf("%d\n",i+1);
        }
        *(vec+i) = elem;
        i++;
        printf("Salio con 0 o llego a la cantidad de datos solicitada");
    }
    return vec;
}

void graba (int *datos, int n){
    FILE *f;
    int aux;
    f=fopen("vector.dat","wb");
    if(f == NULL)
        printf("Error al abrir el archivo");
    else{
        aux=fwrite(datos,sizeof(int),n,f);
        if(aux!=n)
            printf("Error al grabar");
        if( fclose(f)!=0 )
            printf("Error al cerrar el archivo");
    }
}

int main (){
    int cant;
    int*datos;
    printf("Seleccione la cantidad de elementos a ingresar: ");
    scanf("%d",&cant);
    datos=carga_elem(cant);
    graba(datos,cant);
    free(datos);
    datos=NULL;
    return 0;
}