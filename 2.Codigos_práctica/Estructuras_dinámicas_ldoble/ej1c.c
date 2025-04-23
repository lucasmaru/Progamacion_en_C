/*Escribir funciones que inserten un elemento de numérico en una lista doblemente enlazada:
a. Al principio de la lista.
b. Al final de la lista.
c. En un lugar intermedio (por ejemplo la posición n)*/
# include <stdio.h>
# include <stdlib.h>

typedef struct nodo_doble{//Nodo de estructura doble con dos punteros para conectar con el anterior y el primero
    int dato;
    struct nodo_doble *ant, *sig;
}nodo;//con typedef lo llamo nodo pues son los únicos nodos que tengo

typedef struct lista_doble{//estrucura que contiene los punteros que apuntan al primer y último nodo de la lista
    nodo *prim, *ult;
}lista;//llamó lista pues son las únicas listas que tengo

lista Ingresar_LIFO (lista l, int d){//Recibo una lista que la trato como l y un dato a ingresar d
    nodo *nuevo; //declaro un puntero a nodo que lo llamo nuevo

    nuevo=(nodo*)malloc(sizeof(nodo));//reservo memoria
    if (nuevo==NULL)//valido que haya podido reservar memoria, si no pudo salgo del programa
        exit (1);
    //preparo el nodo
    nuevo->dato=d;
    nuevo->ant=NULL;//Por que es el primero de la lista
    nuevo->sig=l.prim;//Pongo al sig del nodo nuevo  a puntar al nodo que antes era el primero
    //tengo listo el nuevo nodo, ahora decido como insertar
    if (l.ult==NULL)//lista vacia
        l.ult=nuevo;//tanto l.ult como l.prim apuntan al primer y único nodo de la lista
    else//si entra acá es por que ya hay algún nodo en la lista
        l.prim->ant=nuevo;//accede al puntero ant del primer nodo de la lista y le asigna el nodo nuevo, antes este apuntaba a NULL
    l.prim=nuevo;//ahora nuevo pasa a ser el primer nodo tanto si era el único como si había otros

    return l;//devuelve la nueva lista
}

lista Ingresar_FIFO (lista l, int d){//Recibo una lista que la trato como l y un dato a ingresar d
    nodo *nuevo; //declaro un puntero a nodo que lo llamo nuevo
    nuevo=(nodo*)malloc(sizeof(nodo));//reservo memoria
    if (nuevo==NULL)//valido que haya podido reservar memoria, si no pudo salgo del programa
        exit (2);
    //preparo el nodo
    nuevo->dato=d;
    nuevo->sig=NULL;//Por que es el último de la lista
    nuevo->ant=l.ult;
    //tengo listo el nuevo nodo, ahora decido como insertar
    if (l.prim==NULL)//lista vacia
        l.prim=nuevo;//tanto l.ult como l.prim apuntan al primer y único nodo de la lista
    else//si entra acá es por que ya hay algún nodo en la lista
        l.ult->sig=nuevo;//accede al puntero ant del primer nodo de la lista y le asigna el nodo nuevo, antes este apuntaba a NULL
    l.ult=nuevo;//ahora nuevo pasa a ser el primer nodo tanto si era el único como si había otros
    return l;//devuelve la nueva lista
}

lista Ingresar_MEDIO(lista l,int d){
    int pos,i=0,j=2;//Lugar en la lista
    nodo *nuevo; //declaro un puntero a nodo que lo llamo nuevo
    nodo *ptr;//para recorrer la lista
    nuevo=(nodo*)malloc(sizeof(nodo));//reservo memoria
    if (nuevo==NULL)//valido que haya podido reservar memoria, si no pudo salgo del programa
        exit (2);
    nuevo->dato=d;//guardo el dato
    printf("Posicion de ingreso:\n");
    scanf("%d",&pos);
    if (l.prim==NULL)//Si la lista está vacia me da igual como lo inserto
        l=Ingresar_LIFO(l,d);
    else{
        for(ptr=l.prim;ptr!=NULL;ptr=ptr->sig)
            i++;//Como la lista no esta vacía me interesa saber cuantos datos tiene
        printf("cantidad de datos en lista: %d \n",i);//cheq
        if(pos>=(i+1))//Si me pide que lo coloque último o en una posición mayor que nodos en lista lo coloco último
            l=Ingresar_FIFO(l,d);
        else{
            ptr=l.prim;
            while(j<pos){
                ptr=ptr->sig;
                j++;
            }
            nuevo->sig=ptr->sig;//Nuevo apuntando al sig dato
            nuevo->ant=ptr;//Nuevo apuntando al dato anterior
            ptr->sig=nuevo;//El anterior ahora apunta a nuevo
            nuevo->sig->ant=nuevo;//el de adelante de nuevo apunta nuevo
        }
    }
    return l;
}

lista Destruir(lista l){
    nodo *aux,*ptr;
    aux=l.prim;
    while (aux!=NULL){
        ptr=aux;
        aux=aux->sig;
        free(aux);
    }
    printf("Listra destruida \n");
    l.prim=NULL;
    l.ult=NULL;
    return l;
}

void mostrar (lista l){
    nodo *p;
    for(p=l.prim;p!=NULL;p=p->sig)
        printf("-->%d",p->dato);
}

int main (){
    int temp,modo;
    lista l;
    l.prim=NULL;//inicializo los dos punteros de la lista
    l.ult=NULL;
    printf("Ingrese el dato (sale con cero): ");
    scanf("%d",&temp);
    if (temp!=0){//verifico que el dato cumpla la condición
        do{
            printf("Modo de ingreso:\n 1.LIFO 2.FIFO 3.MEDIO: \n");
            scanf("%d",&modo);
            switch (modo)
            {
            case 1:
                l=Ingresar_LIFO(l,temp);
                break;
            case 2:
                l=Ingresar_FIFO(l,temp);
                break;
            case 3:
                l=Ingresar_MEDIO(l,temp);
                break;
            }
            printf("Ingrese el siguiente dato (sale con cero):");
            scanf("%d",&temp);
        }while(temp!=0);
    }
    else{
        printf("Salio del programa \n");
        exit(4);
    }
    mostrar(l);
}