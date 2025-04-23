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

lista Ingresar_medio (lista l, int d, int c){//Recibo una lista que la trato como l y un dato a ingresar d
    int pos;
    int i=0;
    nodo *nuevo,*p;
    nuevo=(nodo*)malloc(sizeof(nodo));//reservo memoria
    if (nuevo==NULL)//valido que haya podido reservar memoria, si no pudo salgo del programa
        exit (2);
    nuevo->dato=d;
    printf("Posicion deseada en la lista:\n");
    scanf("%d",&pos);
    while(pos>c&&pos!=0){
        printf("menor cantidad de elmentos en lista, ingrese nuevamente \n Posición en la lista:");
        scanf("%d",&pos);
    }
    if(pos==1)//Si lo quiere primero LIFO
        l=Ingresar_LIFO(l,d);
    if(pos==c)//Si lo quiere último FIFO
        l=Ingresar_FIFO(l,d);
    else{//En posiciones intermedias entra acá
        p=l.prim; //Pongo p apuntando al principio de la lista
        printf("adentro del else\n");
        while(i<pos){
            p=p->sig; //Avanzo p tanta veces como pos lo indica
            i++;
            printf("adentro del while\n");
        }
        printf("Llegue a salir del else\n");
    }
    nuevo->ant=p;
    nuevo->sig=p->sig;
    return l;
    }

    
      

typedef struct pdat{
    int* dat;
    int cant;
}pdat;

pdat* Pedir_datos(){
int temp,j;
int i=0;
int*d=NULL;
pdat *p;
printf("Ingrse el dato (sale con cero)");
scanf("%d",&temp);
if (temp!=0){//verifico que el dato cumpla la condición
        while(temp!=0){
            d=(int*)realloc(d,sizeof(int)*(i+1));//reservo memoria
            if (d==NULL)//valido la reserva
                exit (3);
            d[i]=temp;//almaceno el dato
            i++;
            printf("Ingrese el siguiente dato (sale con cero) \n");
            scanf("%d",&temp);
        }
    }
    else{
        printf("Salio del programa \n");
        exit(4);
    }
    p=(pdat*)malloc(sizeof(int)*(i+1));//memoria para todos los int del vector + un int de la cantidad
    if(p==NULL)
        exit(5);
    p->dat=d;
    p->cant=i;
    return p;
}

void mostrar (lista l){
    nodo *p;
    for(p=l.prim;p!=NULL;p=p->sig)
        printf("Dato = %d \n",p->dato);
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

int main (){
    lista l;
    pdat *p;
    int i,como;

    l.prim=NULL;//inicializo los dos punteros de la lista
    l.ult=NULL;
    p=Pedir_datos();
    printf("Ingresar LIFO (1) o FIFO (2) o intermedio(3):");
    scanf("%d",&como);
    while(como!=1 && como!=2 && como!=3){
        printf("Ingrese nuevamente, dato incorrecto\n Ingresar LIFO (1) o FIFO (2) o intermedio (3): ");
        scanf("%d",&como);
    }
    if(como==1)
        for(i=0;i<p->cant;i++)
            l=Ingresar_LIFO(l,p->dat[i]);
    if(como==2)
        for(i=0;i<p->cant;i++)
            l=Ingresar_FIFO(l,p->dat[i]);
    if(como==3)
        for(i=0;i<p->cant;i++)
            l=Ingresar_medio(l,p->dat[i],p->cant);
    mostrar(l);
    l=Destruir(l);            
    return 0;
}