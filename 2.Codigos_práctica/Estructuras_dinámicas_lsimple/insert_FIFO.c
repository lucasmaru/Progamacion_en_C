/*5. Escribir una función que inserte un elemento después del último nodo de una lista enlazada.*/
# include <stdio.h>
# include <stdlib.h>

typedef struct nodo {//Declaro el tipo de esructura nodo
    int dato;
    struct nodo *sig;}nodo;

nodo* Insertar_FIFO(nodo *l, int d){//Ingresa elementos a la lista
    nodo* nuevo;
    nodo* aux;//recorrer la lista 
    nuevo=(nodo*) malloc (sizeof (nodo));//reservo memoria para el nuevo dato
    if (nuevo==NULL)
    exit (1);//valida la reserva de memoria
    nuevo->dato=d;//Almaceno d en el nuevo nodo
    nuevo->sig =NULL;//Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)//si no hay nodos
        return nuevo;
    aux=l;//pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;//ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;}//devuelvo l, porque sigue siendo el primer elemento de la lista

nodo* Pedir_datosFIFO(nodo *l){
    int temp;
    printf("Ingrese el entero deseado (sale con 0):\n");
    scanf("%d",&temp);
    if (temp!=0){
        while (temp!=0){            
            l=Insertar_FIFO(l,temp);
            printf("Ingrese el siguiente dato (sale con cero)\n");
            scanf("%d",&temp);
        }
    }
    else printf("Salio del programa\n");
    return l;}


void Mostrar_lista(nodo *l){
printf("Lista:");
while(l!=NULL){
    printf("-->%d",l->dato);
    l=l->sig;
}
printf("\n");
}

int main(){
    nodo* lista=NULL;
    lista=Pedir_datosFIFO(lista);
    Mostrar_lista(lista);
    return 0;
}
