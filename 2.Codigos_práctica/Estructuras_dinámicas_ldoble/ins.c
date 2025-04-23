/*
El Instituto de Nanosistemas (INS), creado por la Universidad Nacional de San Martín en 2014,
es un espacio de investigación científica en el campo de la nanotecnología. Dado que trabaja
con productos químicos, para soportar su sistema de información se le pide a usted escribir
un programa que implemente un menú cíclico con las siguientes opciones:
1) Leer un archivo binario con registros que tienen la siguiente estructura:
 Código de producto: entero de 16 bits
 Nombre del producto: cadena de hasta 20 caracteres
 Precio por unidad de masa: flotante simple precisión
 Stock en gramos: flotante doble precisión
Los datos se deben agregar al final de una lista doblemente enlazada manteniendo el
orden del archivo (lista maestra)
2) Agregar un producto ingresado por teclado a final de la lista maestra
3) Eliminar un elemento de la lista maestra dado su código
4) Generar una versión ordenada de lista, pudiendo ser el orden por cualquiera de los 4
campos según la elección del usuario
5) Mostrar la lista dando la opción de hacerlo con la maestra / ordenada en sentido
directo / inverso
6) Sobrescribir en archivo con los datos de la lista maestra
7) Informar si en la lista maestra hay productos con nombre duplicado y en caso
afirmativo informar los códigos de al menos el primer caso de duplicación encontrado
(si lo necesita puede hacer uso de la lista ordenada)
8) Salir
Las opciones del menú deben poder usarse en cualquier orden y número de veces
*/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct producto {           //Producto
    short codigo;
    char nombre[20];
    float precio;
    double stock;
}producto;

typedef struct nodo{                //Nodo
    producto prod;                                  
    struct nodo *ant, *sig;
}nodo;

typedef struct ldoble{              //Lista doble
    nodo *prim, *ult;
}lista;

lista Insertar_FIFO_d(lista l, producto d){
    nodo* nuevo;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(1);
    }
    nuevo->prod = d;
    nuevo->sig = NULL;//estoy insertando al final
    nuevo->ant =l.ult;

    if(l.prim==NULL)          //lista vacia =>l.prim y l.ult apuntan a NULL
        l.prim=nuevo;          
    else
        l.ult->sig = nuevo;
    l.ult = nuevo;
    return l;  
}

lista Insertar_LIFO_d(lista l, producto d){
    nodo* nuevo;

    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL)
        exit(1);
    nuevo->prod = d;
    nuevo->ant = NULL;
    nuevo->sig = l.prim;

    if(l.prim==NULL)          //lista vacia =>l.prim y l.ult apuntan a NULL
        l.ult=nuevo;          //pongo al l.ult apuntado al único nodo de la lista
    else                      //acá ya tengo algún nodo en la lista
        l.prim->ant = nuevo;  //poreso pongo al nuevo antes del que antes era el primerp
    l.prim = nuevo;           //esta linea se ejecuta siempre,porque como inserto al principio el nuevo nodo debe ser el primero
    return l;                 //retorno la estructura que contiene a los dos punteros ya actualizada
}


lista Insertar_ordenado_doble_short(lista l,producto d){
    nodo *nuevo,*actual,*anterior;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(2);
    }
    nuevo->prod=d;
    nuevo->ant=NULL;
    nuevo->sig=NULL;

    if (l.prim==NULL || l.prim->prod.codigo >= d.codigo){ //Lista vacia o primer dato en lista mayor que d, por eso inserto al incio
        l=Insertar_LIFO_d(l,d);
        return l;
    }
    actual = l.prim;
    while(actual!=NULL && actual->prod.codigo < d.codigo){
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

lista Insertar_ordenado_doble_float(lista l,producto d){
    nodo *nuevo,*actual,*anterior;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(3);
    }
    nuevo->prod=d;
    nuevo->ant=NULL;
    nuevo->sig=NULL;

    if (l.prim==NULL || l.prim->prod.precio >= d.precio){ //Lista vacia o primer dato en lista mayor que d, por eso inserto al incio
        l=Insertar_LIFO_d(l,d);
        return l;
    }
    actual = l.prim;
    while(actual!=NULL && actual->prod.precio < d.precio){
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

lista Insertar_ordenado_doble_double(lista l,producto d){
    nodo *nuevo,*actual,*anterior;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(3);
    }
    nuevo->prod=d;
    nuevo->ant=NULL;
    nuevo->sig=NULL;

    if (l.prim==NULL || l.prim->prod.stock >= d.stock){ //Lista vacia o primer dato en lista mayor que d, por eso inserto al incio
        l=Insertar_LIFO_d(l,d);
        return l;
    }
    actual = l.prim;
    while(actual!=NULL && actual->prod.stock < d.stock){
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

lista Insertar_ordenado_doble_nombre(lista l,producto d){
    nodo *nuevo,*actual,*anterior;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(4);
    }
    nuevo->prod=d;
    nuevo->ant=NULL;
    nuevo->sig=NULL;

    if (l.prim==NULL || strcmp(l.prim->prod.nombre,d.nombre)>=0){ //Lista vacia o primer dato en lista mayor que d, por eso inserto al incio
        l=Insertar_LIFO_d(l,d);
        return l;
    }
    actual = l.prim;
    while(actual!=NULL && strcmp(actual->prod.nombre,d.nombre)<0){
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



void Mostrar_lista_directo(lista l){
    if (l.prim==NULL)
        printf("\nLista vacía\n\n");
    else{
        printf("Lista:\n");
        while(l.prim!=NULL){
            printf("-->%d",l.prim->prod.codigo);
            printf("-->%s",l.prim->prod.nombre);
            printf("-->%f",l.prim->prod.precio);
            printf("-->%lf\n",l.prim->prod.stock);
            l.prim=l.prim->sig;
        }
        printf("\n");
    }
}

void Mostral_lista_inverso(lista l){
    if (l.prim==NULL)
        printf("\nLista vacía\n\n");
    else{
        printf("Lista:\n");
        while(l.ult!=NULL){
            printf("-->%d",l.ult->prod.codigo);
            printf("-->%s",l.ult->prod.nombre);
            printf("-->%f",l.ult->prod.precio);
            printf("-->%lf\n",l.ult->prod.stock);
            l.ult=l.ult->ant;
        }
        printf("\n");
    }
}

lista Destruir_lista(lista l){
    nodo *p, *aux;

    p=l.prim;
    while(p!=NULL){
        aux = p;
        p = p->sig;
        free(aux);
    }
    printf("\nLista destruida\n");
    l.prim = NULL;
    l.ult = NULL;
    return l;
}

lista Lee_archivo_genera_lista(lista l){
    FILE* f;
    producto p;

    f = fopen("stock.dat","rb");
    if(f==NULL)                         //no puede abrir el archivo
        printf("\nError al abrir el archivo\n\n");
    else{
        while( fread(&p,sizeof(p),1,f) == 1){
            l = Insertar_FIFO_d(l,p);
        }
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo");
        printf("\nDatos leídos\n\n");
    }
    return l;
}

lista Agregar_producto(lista l){
    producto p;
    printf("\nIngrese el código:");
    scanf("%hd",&p.codigo);
    printf("\nIngrese el nombre:");
    scanf("%s",p.nombre);
    printf("\nIngrese el precio por gramo:");
    scanf("%f",&p.precio);
    printf("\nIngrese el stock:");
    scanf("%lf",&p.stock);
    l=Insertar_FIFO_d(l,p);
    printf("Se agregó el producto a la lista\n\n");
    return l;
}

lista Eliminar_por_codigo(lista l){
    short d;
    nodo *aux_eliminar=NULL,*aux_sig=NULL,*aux_ant=NULL;
    if (l.prim==NULL){
        printf("\nLista vacía\n\n");
        return l;
    }
    printf("Ingrese el código de producto a eliminar:");
    scanf("%hd",&d);
    if(l.prim->prod.codigo == d){ //el código a eliminar es el primero
        aux_eliminar=l.prim;
        if(l.prim->sig!=NULL){//si esto sucede es porque  hay más nodos en la lista
            l.prim=l.prim->sig;    
            l.prim->ant =NULL;
        }
        else{//en este caso la lista queda vacía
            l.prim=NULL;
            l.ult=NULL;
        }
        free(aux_eliminar);
        printf("\nSe eliminó el código solicitado\n\n");
    }
    else if(l.ult->prod.codigo == d){//el código a eliminar es el último
        aux_eliminar=l.ult;    
        l.ult=l.ult->ant;
        l.ult->sig=NULL;
        free(aux_eliminar);
        printf("\nSe eliminó el código solicitado\n\n");
    }
    else{//el código a eliminar esta en el medio o no está, pero debo recorrer la lista
        aux_eliminar = l.prim;
        while(aux_eliminar->sig!=NULL && aux_eliminar->sig->prod.codigo!=d){
            aux_ant = aux_eliminar;
            aux_eliminar=aux_eliminar->sig;
        }
        if(aux_eliminar->sig != NULL){//Si sigue siendo NULL salió del while porque encontró el código
            aux_ant=aux_eliminar;
            aux_eliminar=aux_eliminar->sig;    //Uso los ptr para desengachar el nodo a elminar
            aux_ant->sig=aux_eliminar->sig;
            aux_eliminar->sig->ant=aux_ant;
            printf("\nElimine=%hd\n",aux_eliminar->prod.codigo);
            free(aux_eliminar);
            printf("\nSe eliminó el código solicitado\n\n");        
        }
        else
            printf("\nCódigo no existente en lista\n\n");
    }
    return l;
}

void Graba_lista(lista l){
    FILE *f;
    nodo *aux=NULL;
    if(l.prim==NULL){
        printf("Lista vacía");
        return;
    }
    f = fopen("stock.dat","wb");
    if(f==NULL)                         //no puede abrir el archivo
        printf("\nError al abrir el archivo para grabar\n\n");
    else{
        aux=l.prim;
        while(aux!=NULL){
            fwrite(&aux->prod,sizeof(aux->prod),1,f);
            aux = aux->sig;
        }
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo");
        printf("\nDatos grabados\n\n");
    }
}

lista Ordenar (lista l_madre){
    int op;
    short aux_short;
    nodo *aux_lista=NULL;
    lista l_ord;
    
    l_ord.prim=NULL;
    l_ord.ult=NULL;
    if (l_madre.prim==NULL){                                   //Lista vacía
        printf("\nLista vacía\n\n");
        return l_ord;
    }
    if(l_madre.prim->sig==NULL){                              //Lista con un solo elemento
        printf("\nHay un único elemento en la lista\n\n");
        return l_ord;
    }
    
    printf("1__Ordenar por código de producto\n");                
    printf("2__Ordenar por nombre\n");       
    printf("3__Ordenar por precio\n");
    printf("4__Ordenar por stock\n");
    scanf("%d",&op);
    aux_lista=l_madre.prim;
    if (op==1){
        while(aux_lista!=NULL){
            l_ord=Insertar_ordenado_doble_short(l_ord,aux_lista->prod);
            aux_lista=aux_lista->sig;
        }
        Mostrar_lista_directo(l_ord);
    }   
        
    else if (op==2){
        while(aux_lista!=NULL){
            l_ord=Insertar_ordenado_doble_nombre(l_ord,aux_lista->prod);
            aux_lista=aux_lista->sig;
        }
        Mostrar_lista_directo(l_ord);
    }
    else if (op==3){
        while(aux_lista!=NULL){
            l_ord=Insertar_ordenado_doble_float(l_ord,aux_lista->prod);
            aux_lista=aux_lista->sig;
        }
        Mostrar_lista_directo(l_ord);
    }
    else if(op==4){
        while(aux_lista!=NULL){
            l_ord=Insertar_ordenado_doble_double(l_ord,aux_lista->prod);
            aux_lista=aux_lista->sig;
        }
        Mostrar_lista_directo(l_ord);
    }
    else
        printf("\nOpción invalida\n\n");


}

/*void Duplicado(lista l){
    nodo *aux_lista,*aux_lista2;
    int duplicado =1;

    if(l.prim==NULL || l.prim->sig==NULL){
        printf("\nLista vacía o hay un único producto\n\n");
        return ;
    }

    aux_lista=l.prim;
    aux_lista2=l.prim;
    while(aux_lista!=NULL){ //Me coloco en un nodo
        if(aux_lista->ant!=NULL){//Miro para atras
            while(aux_lista!=NULL && aux_lista2->ant!=NULL){
                duplicado=strcmp(aux_lista->prod.nombre,aux_lista2->ant->prod.nombre);
                printf("1. %s  -->  %s\n",aux_lista->prod.nombre,aux_lista2->ant->prod.nombre);
                if(aux_lista==aux_lista2->ant)
                    printf("\nIguales\n");
                if(duplicado==0 && aux_lista!=aux_lista2->ant){
                    printf("1.El nombre del producto código %hd es igual al del producto %hd\n\n",aux_lista->prod.codigo,aux_lista2->ant->prod.codigo);
                    return;
                }
                duplicado=1;
                aux_lista2=aux_lista2->ant;
            }
        }
        if(aux_lista->sig!=NULL){//Miro para adelante
            while(aux_lista!=NULL && aux_lista2->sig!=NULL){
                duplicado=strcmp(aux_lista->prod.nombre,aux_lista2->sig->prod.nombre);
                printf("2. %s  -->  %s\n",aux_lista->prod.nombre,aux_lista2->sig->prod.nombre);
                if(duplicado==0 && aux_lista!=aux_lista2->sig){
                    printf("2.El nombre del producto código %hd es igual al del producto %hd\n\n",aux_lista->prod.codigo,aux_lista2->sig->prod.codigo);
                    return;
                }
                aux_lista2=aux_lista2->sig;
            }
        }
        aux_lista=aux_lista->sig;
        aux_lista2=aux_lista;
    }
    printf("\nNo hay productos duplicados\n\n");
    return;
}*/
void Duplicado (lista l){
    nodo *actual=NULL, *siguiente=NULL;

    if(l.prim==NULL || l.prim->sig==NULL){
        printf("\nLista vacía o hay un único producto\n\n");
        return ;
    }

    actual=l.prim;
    siguiente=l.prim->sig;
    while(actual!=NULL && siguiente!=NULL){//Me paro en el nodo y comparo con todos los restantes
        
        printf("adadad\n");
        while(siguiente!=NULL){
            if (strcmp(actual->prod.nombre,siguiente->prod.nombre)==0){
                printf("El nombre del producto código %hd es igual al del producto %hd\n\n",actual->prod.codigo,siguiente->prod.codigo);
                return;
            }
            siguiente=siguiente->sig;
        }
        
        actual=actual->sig;
        siguiente=actual->sig;
        
    }
    printf("No hay nombres repetidos\n");
}
int main(){
    int opcion;
    lista lista_maestra,lista_aux;
    int sentido;

    lista_maestra.prim=NULL;
    lista_maestra.ult=NULL;
    lista_aux.prim=NULL;
    lista_aux.ult=NULL;
    
    
    do{
        printf("1__Leer el archivo y generar lista maestra\n");                
        printf("2__Agregar producto al final de la lista maestra\n");       
        printf("3__Eliminar un producto dado su código\n");
        printf("4__Ordenar lista\n");
        printf("5__Mostrar lista\n");
        printf("6__Grabar lista maestra\n");
        printf("7__Buscar productos duplicados\n");
        printf("8__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                lista_maestra=Lee_archivo_genera_lista(lista_maestra);
                break;
            case 2:
                lista_maestra=Agregar_producto(lista_maestra);
                break;
            case 3:
                lista_maestra=Eliminar_por_codigo(lista_maestra);
                break;
            case 4:
                lista_aux=Ordenar(lista_maestra);
                break;
            case 5:
                printf("Ingrese 1 para verla al derecho o 2 para verla en sentido inverso:");
                scanf("%d",&sentido);
                if (sentido==1)
                Mostrar_lista_directo(lista_maestra);
                else
                Mostral_lista_inverso(lista_maestra);
                break;
            case 6:
                Graba_lista(lista_maestra);
                break;
            case 7:
                Duplicado(lista_maestra);
                break;
            case 8:
                printf("Finalizó programa\n");
                break;
        }
    }while (opcion != 8);

    lista_maestra = Destruir_lista(lista_maestra);
    lista_aux = Destruir_lista(lista_aux);
    return 0;
}