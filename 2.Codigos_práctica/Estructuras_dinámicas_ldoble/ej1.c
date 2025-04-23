/*Escribir funciones que inserten un elemento de numérico en una lista doblemente enlazada:
a. Al principio de la lista.
b. Al final de la lista.
c. En un lugar intermedio (por ejemplo la posición n)*/
# include <stdio.h>
# include <stdlib.h>

typedef struct nodo_doble{//Nodo de estructura doble con dos punteros para conectar con el anterior y el primero
    int dato;
    struct nodo_doble *ant, *sig;
}nodo_doble;//con typedef lo llamo nodo_d de nodo doble

typedef struct lista_doble{//estrucura que contiene los punteros que apuntan al primer y último nodo de la lista
    nodo_doble *prim, *ult;
}lista_doble;

/*typedef struct devuelve_pedir_datos{//Almacena lo que devuelve la función pedir datos
    int*  datos;//vector de enteros que recojió
    int cant;//cantidad de datos que hay
}devdatos;*/

lista_doble inser_LIFO (lista_doble l,int d){
    nodo_doble *nuevo;

    nuevo=(nodo_doble*)malloc(sizeof(nodo_doble));//reservo memoria
    if (nuevo==NULL)//valido que haya podido reservar memoria, si no pudo salgo del programa
        exit (1);
    nuevo->dato=d;//asigno el dato al nuevo nodo
    nuevo->ant=NULL;//como lo inserto primero se que antes nuevo no hay otro nodo
    nuevo->sig=l.prim;//apunto con nuevo->sig a el que antes era el primer puntero de la lista

    //tengo listo el nuevo nodo, ahora tengo que ver como lo inserto
    if (l.ult==NULL)//lista vacia
        l.ult=nuevo;//tanto l.ult como l.prim apuntan al primer y único nodo de la lista
    else//si entra acá es por que ya hay algún nodo en la lista
        l.prim->ant=nuevo;//accede al puntero ant del primer nodo de la lista y le asigna el nodo nuevo, antes este apuntaba a NULL
    l.prim=nuevo;//ahora nuevo pasa a ser el primer nodo tanto si era el único como si había otros

    return l;//devuelve la nueva lista
}

lista_doble inser_FIFO (lista_doble l,int d){
    nodo_doble *nuevo;

    nuevo=(nodo_doble*)malloc(sizeof(nodo_doble));//reservo memoria
    if (nuevo==NULL)//valido que haya podido reservar memoria, si no pudo salgo del programa
        exit (1);
    nuevo->dato=d;//asigno el dato al nuevo nodo
    nuevo->sig=NULL;//como lo inserto último se que despues de nuevo no hay otro nodo
    nuevo->ant=l.ult;//apunto con nuevo->ant a el que antes era el último puntero de la lista
    //tengo listo el nuevo nodo, ahora tengo que ver como lo inserto
    if (l.ult==NULL)//lista vacia
        l.prim=nuevo;//tanto l.ult como l.prim apuntan al primer y único nodo de la lista
    else//si entra acá es por que ya hay algún nodo en la lista
        l.ult->sig=nuevo;//accede al puntero ant del primer nodo de la lista y le asigna el nodo nuevo, antes este apuntaba a NULL
    l.ult=nuevo;//ahora nuevo pasa a ser el primer nodo tanto si era el único como si había otros

    return l;//devuelve la nueva lista
}

/*devdatos* pedir_datos(devdatos ingresar){
    //devdatos *ingresar=NULL;
    int temp;
    int i=0;
    int* d=NULL;

    printf("Ingrese el dato (sale con cero)\n");//pido dato
    scanf("%d",&temp);//almaceno el dato temporalmente
    if (temp!=0){//verifico que el dato cumpla la condición
        while(temp!=0){
            d=(int*)realloc(d,sizeof(int)*(i+1));//reservo memoria
            if (d==NULL)//valido la reserva
                exit (2);
            d[i]=temp;//almaceno el dato
            i++;
            printf("Ingrese el siguiente dato (sale con cero) \n");
            scanf("%d",&temp);
        }
    }
    else{
        printf("Salio del programa \n");
        exit(3);
    }
    printf("%d",i);//cheq
    ingresar->datos=d;
    ingresar->cant=i;
    return ingresar;
}*/

int main(){
    lista_doble lista_main;
    lista_main=inser_FIFO(lista_main,3);
    printf("%d",lista_main.prim->*dato);
    return 0;
}

