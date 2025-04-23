# include <stdio.h>
# include <stdlib.h>

typedef struct nodo{
    float dato;                                  
    struct nodo *ant, *sig;
}nodo;

typedef struct ldoble{
    nodo *prim, *ult;
}lista;

lista Insertar_LIFO_d(lista l, float d){
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

lista Insertar_FIFO_d(lista l, float d){
    nodo* nuevo;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL)
        exit(1);
    nuevo->dato = d;
    nuevo->sig = NULL;
    nuevo->ant =l.ult;

    if(l.prim==NULL)          //lista vacia =>l.prim y l.ult apuntan a NULL
        l.prim=nuevo;          
    else
        l.ult->sig = nuevo;
    l.ult = nuevo;
    return l;  
}

lista Insertar_ORDENADO_d(lista l,float d){
    nodo *nuevo,*actual,*anterior;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL){
        exit(3);
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

    //acomodo nuevo en la lista
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
            printf("-->%.2f",l.prim->dato);
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
            printf("-->%2.f",l.ult->dato);
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

void Graba_lista(lista l){
    FILE *f;
    nodo *aux=NULL;
    if(l.prim==NULL){
        printf("Lista vacía");
        return;
    }
    f = fopen("prueba.dat","wb");
    if(f==NULL)                         //no puede abrir el archivo
        printf("\nError al abrir el archivo para grabar\n\n");
    else{
        aux=l.prim;
        while(aux!=NULL){
            fwrite(&aux->dato,sizeof(aux->dato),1,f);
            aux = aux->sig;
        }
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo");
        printf("\nDatos grabados\n\n");
    }
}

lista Lee_archivo_genera_lista_FIFO(lista l){
    FILE* f;
    float p;

    f = fopen("prueba.dat","rb");
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

lista Eliminar_dato(lista l){
    float d;
    nodo *aux_eliminar=NULL,*aux_ant=NULL;
    if (l.prim==NULL){
        printf("\nLista vacía\n\n");
        return l;
    }
    printf("Ingrese el dato a eliminar:");
    scanf("%f",&d);
    if(l.prim->dato == d){ //el código a eliminar es el primero
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
    else if(l.ult->dato == d){//el código a eliminar es el último
        aux_eliminar=l.ult;    
        l.ult=l.ult->ant;
        l.ult->sig=NULL;
        free(aux_eliminar);
        printf("\nSe eliminó el código solicitado\n\n");
    }
    else{//el código a eliminar esta en el medio o no está, pero debo recorrer la lista
        aux_eliminar = l.prim;
        while(aux_eliminar->sig!=NULL && aux_eliminar->sig->dato!=d){
            aux_ant = aux_eliminar;
            aux_eliminar=aux_eliminar->sig;
        }
        if(aux_eliminar->sig != NULL){//Si sigue siendo NULL salió del while porque encontró el código
            aux_ant=aux_eliminar;
            aux_eliminar=aux_eliminar->sig;    //Uso los ptr para desengachar el nodo a elminar
            aux_ant->sig=aux_eliminar->sig;
            aux_eliminar->sig->ant=aux_ant;
            printf("\nElimine=%f\n",aux_eliminar->dato);
            free(aux_eliminar);
            printf("\nSe eliminó el código solicitado\n\n");        
        }
        else
            printf("\nCódigo no existente en lista\n\n");
    }
    return l;
}

void Buscar_elemento(lista l,float d){
    nodo *aux;

    if(l.prim==NULL){
        printf("\nLista vacía");
        return;
    }
    aux=l.prim;
    while(aux!=NULL && aux->dato!=d)
        aux=aux->sig;
    if (aux!=NULL)
        printf("\nEncontré el numero %.2f",d);        
    else
        printf("\nNo existe el dato\n\n");
    return;
}

int main (){
    int op;
    float temp;
    lista lista_maestra;
    lista_maestra.prim=NULL;
    lista_maestra.ult=NULL;

    lista_maestra = Insertar_FIFO_d(lista_maestra, 4);
    lista_maestra = Insertar_FIFO_d(lista_maestra, 8);
    lista_maestra = Insertar_LIFO_d(lista_maestra, 2);
    lista_maestra = Insertar_ORDENADO_d(lista_maestra, 5);
    //lista_maestra=Eliminar_dato(lista_maestra);
    Mostrar_lista_directo(lista_maestra);
    //Graba_lista(lista_maestra);
    //lista_maestra=Lee_archivo_genera_lista_FIFO(lista_maestra);
    //Mostrar_lista_directo(lista_maestra);
    Buscar_elemento(lista_maestra,8);

    lista_maestra=Destruir_lista(lista_maestra);
    return 0;
}
