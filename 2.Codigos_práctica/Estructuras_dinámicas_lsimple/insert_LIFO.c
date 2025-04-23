/*1. Escriba una función que permita insertar un nuevo elemento antes del primer nodo de una lista
enlazada de enteros.*/

# include <stdio.h>
# include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *sig;
}nodo;

nodo* Insertar_LIFO(nodo *l, int d){
    nodo *nuevo;
    nuevo=(nodo*) malloc (sizeof (nodo));
    if (nuevo==NULL)
        exit (1);
    nuevo->dato=d;//Almaceno d en el nuevo nodo
    nuevo->sig =l;//Pongo a el sig del nuevo nodo apuntado a l
    return nuevo;//devuelvo nuevo, porque es el nuevo primer elemento de la lista
}
void Mostrar_lista(nodo *l){
    printf("Lista:");
    while(l!=NULL){
        printf("-->%d",l->dato);
        l=l->sig;
    }
    printf("\n");
}
nodo* Destruir(nodo *l){
    nodo *aux;// Para no perder referencia cuando voy borrando elementos
    while (l!=NULL){
        aux=l;
        l=l->sig;
        free(aux);
    }
    printf("Lista destruida");
    return NULL;
}

int main (){
    nodo *lista=NULL;
    lista=Insertar_LIFO(lista,1);
    lista=Insertar_LIFO(lista,2);
    lista=Insertar_LIFO(lista,3);
    Mostrar_lista(lista);
    lista=Destruir(lista);
    return 0;
}