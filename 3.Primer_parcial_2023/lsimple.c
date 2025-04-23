# include <stdio.h>
# include <stdlib.h>

typedef struct nodo{                   
    int dato; 
    struct nodo* sig; 
}nodo;

nodo* Insertar_LIFO(nodo *l, int d){        //Inserta elementos al incio de la lista
    nodo *nuevo;
    nuevo=(nodo*) malloc (sizeof (nodo));
    if (nuevo==NULL)
        exit (1);
    nuevo->dato=d;                          //Almaceno d en el nuevo nodo
    nuevo->sig =l;                          //Pongo a el sig del nuevo nodo apuntado a l
    return nuevo;                           //devuelvo nuevo, porque es el nuevo primer elemento de la lista
}

nodo* Insertar_FIFO(nodo *l, int d){      //Ingresa elementos al final de la lista
    nodo* nuevo;
    nodo* aux;                            //recorrer la lista 
    nuevo=(nodo*) malloc (sizeof (nodo)); //reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);                         //valida la reserva de memoria

    nuevo->dato=d;                        //Almaceno d en el nuevo nodo
    nuevo->sig =NULL;                     //Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)                           //si no hay nodos
        return nuevo;

    aux=l;                                //pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;                     //ahora aux es el último nodo
    aux->sig=nuevo;                       //guardo el dato en el último nodo
    return l;                             //devuelvo l, porque sigue siendo el primer elemento de la lista
}

nodo* Insertar_ORDENADO(nodo* l,int dato){
    nodo* aux;
    nodo* nuevo;
    
    nuevo = (nodo*)malloc(sizeof(nodo));    //reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);
    nuevo->dato = dato; 
    if (l == NULL || l->dato > dato){       //si la lista esta vacia o el 1er elemento es mayor que el nuevo
        nuevo->sig = l;
        return nuevo;                       //nuevo es el primer nodo de la lista
    }
    else{
        aux=l;                              //mientras no es esté en el ultimo nodo y el dato del sig sea menor que el dato a insertat continua en el while
        while(aux->sig!=NULL && aux->sig->dato<=dato )
            aux=aux->sig;
/*sale del while porque esta en el último nodo y no debe seguir avanzando 
  o porque encontro el lugar donde insertar el nodo*/
        nuevo->sig = aux->sig;
        aux->sig = nuevo;
        return l;
    }
}

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

nodo* Destruir_lista(nodo* l){
    nodo* aux;
    if (l==NULL)
        printf("\nLista vacía\n");
    else{
        while(l!=NULL){
            aux=l;
            l = l->sig;
            free(aux);
        }
        printf("\nLista destruida\n");
    }
    return NULL;
}

void Guardar_lista(nodo* l){
    FILE* f;
    nodo* aux;
    if (l==NULL)                                                     //caso lista NULL
        printf("Lista vacia\n\n");
    else{                                                            //caso lista NO NULL
        f=fopen("PRUEBASIMPLE.dat","wb");
        if(f==NULL){
            printf("Error al abrir el archivo\n\n");
            exit(2);
        }
        else{
            if(l->sig == NULL){                                      //lista con un solo nodo
                if(fwrite(&l->dato,sizeof(l->dato),1,f) == 1){
                    printf("Archivo guardado correctamente\n\n");
                }
                else
                    printf("No se pudo guardar el archivo\n\n");  
            }
            else{
                aux = l;                                             //lista con mas nodos
                if(fwrite(&l->dato,sizeof(l->dato),1,f)!=1)          //leo el primero separado
                    printf("Error al leer el primer archivo\n\n");
                while(aux->sig!=NULL && fwrite(&aux->sig->dato,sizeof(l->dato),1,f) == 1)
                    aux= aux->sig;
                if (aux->sig == NULL)
                    printf("Archivo guardado correctamente\n\n");
                else
                    printf("No se pudo guardar el archivo");
            }
        }
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo");
    }
}

nodo* Lee_archivo_FIFO(){
    FILE* f;
    nodo* l = NULL;
    int i=0, temp;
    
    f = fopen("PRUEBASIMPLE.dat","rb");
    if(f==NULL){                         //no puede abrir el archivo
        printf("Error al abrir el archivO\n\n");
        exit(1);
    }
    else{                               //abre el archivo
        while( fread(&temp,sizeof(temp),1,f) == 1){
            l = Insertar_FIFO(l,temp);
            i++;
        }
        if (fclose(f)!=0){
            printf("Error al cerrar el archivo\n\n");
            exit (1);
        }
        printf("Archivo leído correctamente\n\n");
    }
    return l;
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

void Buscar_elemento(nodo* l,int d){
    nodo *aux;

    if(l==NULL)                        //lista vacía
        printf("\nLista vacía\n");
    else{
        if(l->dato==d){               //la coincidencia está en el primer nodo
            printf("\n1.Encontré\n\n");
        }
        else{
            aux=l;
            while(aux->sig!=NULL && aux->sig->dato!=d)
                aux=aux->sig;
            //sale de while porque encontró el dato o llegó al final
            if(aux->sig!=NULL)//no llegó al final => encontró el dato
                printf("\n2.Encontré\n\n");
            else
                printf("No existe el número %d en la lista",d);
        }
    }
}

int main (){
    nodo *lista_m=NULL;
    
    lista_m=Insertar_LIFO(lista_m,10);
    lista_m=Insertar_ORDENADO(lista_m,22);
    lista_m=Insertar_FIFO(lista_m,55);
    lista_m=Insertar_FIFO(lista_m,534);
    lista_m=Insertar_FIFO(lista_m,6);
    lista_m=Insertar_FIFO(lista_m,29);
    lista_m=Insertar_LIFO(lista_m,57);
    Mostrar_lista(lista_m);
    Guardar_lista(lista_m);
    lista_m=Lee_archivo_FIFO();
    Mostrar_lista(lista_m);
    lista_m=Eliminar_nodo(lista_m,57);
    Mostrar_lista(lista_m);
    Buscar_elemento(lista_m,534);

    lista_m=Destruir_lista(lista_m);

    return 0;
}