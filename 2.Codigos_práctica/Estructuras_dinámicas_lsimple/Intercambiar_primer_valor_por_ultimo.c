# include <stdio.h>
# include <stdlib.h>

typedef struct nodo {
    int dato;
    struct nodo *sig;
}nodo;

nodo* Insertar_FIFO(nodo *l, int d){      //Ingresa elementos a la lista
    nodo* nuevo;
    nodo* aux;                            //recorrer la lista 
    nuevo=(nodo*) malloc (sizeof (nodo)); //reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);                             //valida la reserva de memoria
    nuevo->dato=d;                        //Almaceno d en el nuevo nodo
    nuevo->sig =NULL;                     //Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)                           //si no hay nodos
        return nuevo;
    aux=l;                                //pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;                     //ahora aux es el último nodo
    aux->sig=nuevo;                       //guardo el dato en el último nodo
    return l;}                             //devuelvo l, porque sigue siendo el primer elemento de la lista

void Mostrar_lista(nodo *l){
    if(l==NULL)
        printf("\nLista vacía\n\n");
    else{
        printf("Lista:");
        while(l!=NULL){
            printf("-->%d",l->dato);
            l=l->sig;
        }
        printf("\n");
    }
}

nodo* Eliminar_nodo (nodo*l,int d){
    nodo *ret =l, *aux=NULL;
    if(l==NULL)                        //lista nula
        printf("\nLista vacía\n");
    else{                              //lista no nula
        if(l->dato == d){              //caso en el que el nodo a borrar es el primero                
            ret = l->sig;
            free(l);
            printf("\nDato eliminado\n");
        }
        else{                                           //caso en el que el nodo a borrar no es el primero
            while(l->sig!=NULL && l->sig->dato!=d)
                l=l->sig;                               //pongo a l apuntando al siguiente
            if(l->sig!=NULL){                           //si l->sig!=NULL es porque el dato a borar existe, de lo contrario hubiera llegado al final de la lista
                aux = l->sig;
                l->sig = aux->sig;
                free(aux);
                printf("\nDato %d eliminado\n",d);
            }
            else
                printf("El dato %d no existe en la lista\n",d);
       }
    }
    return ret;
}

nodo* Insertar_ordenado(nodo* l,int d){
    nodo* aux;
    nodo* nuevo;
    
    nuevo = (nodo*)malloc(sizeof(nodo));    //reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);
    nuevo->dato = d; 
    if (l == NULL || l->dato > d){       //si la lista esta vacia o el 1er elemento es mayor que el nuevo
        nuevo->sig = l;
        return nuevo;                       //nuevo es el primer nodo de la lista
    }
    else{
        aux=l;                              //mientras no es esté en el ultimo nodo y el dato del sig sea menor que el dato a insertat continua en el while
        while(aux->sig!=NULL && aux->sig->dato<=d )
            aux=aux->sig;
/*sale del while porque esta en el último nodo y no debe seguir avanzando o porque encontro el lugar
donde insertar el nodo*/
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
        return l;
    }
}

nodo* Intercambia_primero_por_ultimo(nodo* l){
    nodo* aux = NULL;
    int primero, ultimo;
    if (l == NULL){
        printf("Lista vacía");
        return l;
    }
    else{
        aux=l;
        while(aux->sig!=NULL){
            aux=aux->sig;
        }
        ultimo = aux->dato;
        primero = l->dato;

        l->dato = ultimo;
        aux->dato = primero;
        return l;
    }
}

int main (){
    nodo* lista = NULL;
    lista= Insertar_ordenado(lista,3);
    lista= Insertar_ordenado(lista,54);
    lista= Insertar_ordenado(lista,4);
    lista= Insertar_ordenado(lista,2);
    lista= Insertar_ordenado(lista,7);  

    Mostrar_lista(lista);
    //Intercambia_primero_por_ultimo(lista);
    lista = Eliminar_nodo(lista, 54);
    Mostrar_lista(lista);   
    return 0;
}