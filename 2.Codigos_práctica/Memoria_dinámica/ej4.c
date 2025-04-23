/*4. Escriba la siguiente función:
int *crear_vector (int n, int valor_inicial);
La función debe retornar un puntero a un vector de enteros de tamaño n creado
dinámicamente cuyas posiciones son inicializadas con valor_inicial. La
función debe retornar NULL si no se puede reservar la memoria.
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int *crear_vector (int n, int valor_inicial){
    int* ptr=NULL;
    int i;
    ptr= (int*) malloc (sizeof(char)*n);//Reservo bloque de memoria de n char y pongo a ptr apuntando al bloque
    if (ptr==NULL){
        return ptr;
    }
    else{
        for(i=0;i<n;i++){
            *(ptr+i)=valor_inicial;
        }
        return ptr;
    }
}

int main (){
    int*vec;
    int i;

    vec=crear_vector(5,99);
    for(i=0;i<5;i++){
        printf("%d-->",*(vec+i));
    }
    return 0;
}