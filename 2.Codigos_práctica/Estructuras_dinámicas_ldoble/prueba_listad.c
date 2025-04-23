# include <stdio.h>
# include <stdlib.h>

typedef struct nodo{
    short dato;
    struct nodo *ant, *sig;
}nodo;

typedef struct ldoble{              //Lista doble
    nodo *prim, *ult;
}lista;

lista Insertar_FIFO_d(lista l, short d){
    nodo* nuevo;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(1);
    }
    nuevo->dato = d;
    nuevo->sig = NULL;//estoy insertando al final
    nuevo->ant =l.ult;

    if(l.prim==NULL)          //lista vacia =>l.prim y l.ult apuntan a NULL
        l.prim=nuevo;          
    else
        l.ult->sig = nuevo;
    l.ult = nuevo;
    return l;  
}

lista Insertar_LIFO_d(lista l, short d){
    nodo* nuevo;

    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL)
        exit(1);
    nuevo->dato = d;
    nuevo->ant = NULL;
    nuevo->sig = l.prim;

    if(l.prim==NULL)          //lista vacia =>l.prim y l.ult apuntan a NULL
        l.ult=nuevo;          //pongo al l.ult apuntado al único nodo de la lista
    else                      //acá ya tengo algún nodo en la lista
        l.prim->ant = nuevo;  //poreso pongo al nuevo antes del que antes era el primerp
    l.prim = nuevo;           //esta linea se ejecuta siempre,porque como inserto al principio el nuevo nodo debe ser el primero
    return l;                 //retorno la estructura que contiene a los dos punteros ya actualizada
}

void Mostrar_lista_directo(lista l){
    if (l.prim==NULL)
        printf("\nLista vacía\n\n");
    else{
        printf("Lista:\n");
        while(l.prim!=NULL){
            printf("-->%d",l.prim->dato);
            l.prim=l.prim->sig;
        }
        printf("\n");
    }
}

lista Insertar_ordenado_doble_short(lista l,short d){
    nodo *nuevo,*actual,*anterior;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(2);
    }
    nuevo->dato=d;
    nuevo->ant=NULL;
    nuevo->sig=NULL;

    if (l.prim==NULL || l.prim->dato >= d){ //Lista vacia o primer dato en lista mayor que d, por eso inserto al incio
        l=Insertar_LIFO_d(l,d);
        return l;
    }
    actual = l.prim;
    while(actual!=NULL && actual->dato < d){
        anterior=actual;
        actual=actual->sig;
    }//Salí del while estoy en el lugar donde quiero insertar el nodo

    //acomo nuevo en la lista
    nuevo->ant=anterior;
    nuevo->sig=actual;
    
    if(actual!=NULL)
        actual->ant=nuevo;
    
    anterior->sig= nuevo;

    return l;
}

/*lista Insertar_ordenado_doble_short(lista l, short d){
    nodo *nuevo, *actual, *posterior;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(2);
    }
    nuevo->dato = d;
    nuevo->ant = NULL;
    nuevo->sig = NULL;
    
    if (l.prim == NULL || l.prim->dato >= d){
        l = Insertar_LIFO_d(l, d);
        return l;
    }

    actual = l.prim;
    while (actual != NULL && actual->dato < d) {
        posterior = actual;
        actual = actual->sig;
    }
    
    nuevo->ant = posterior;
    nuevo->sig = actual;
    
    if (actual != NULL) {
        actual->ant = nuevo;
    }
    
    posterior->sig = nuevo;
    
    return l;
}*/


int main (){
    lista l_maestra,l_ordenada;
    short vec[]={10,20,5,1,345,2};
    int i;
    
    l_ordenada.prim=NULL;
    l_ordenada.ult=NULL;
    l_maestra.prim=NULL;
    l_maestra.ult=NULL;

    Mostrar_lista_directo(l_maestra);
    for(i=0;i<6;i++)
        l_maestra=Insertar_FIFO_d(l_maestra,vec[i]);
    Mostrar_lista_directo(l_maestra);
    while(l_maestra.prim!=NULL){
        l_ordenada=Insertar_ordenado_doble_short(l_ordenada,l_maestra.prim->dato);
        l_maestra.prim=l_maestra.prim->sig;
    }
    Mostrar_lista_directo(l_ordenada);
    return 0;
}