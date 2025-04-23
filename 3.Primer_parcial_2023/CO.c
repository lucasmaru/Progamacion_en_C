# include <stdio.h>
# include <stdlib.h>

typedef struct mediciones{
    int ppm;
    float temp;
}mediciones;

typedef struct extremos{
    int max;
    int min;
}extremos;

typedef struct nodo{                   
    mediciones dato; 
    struct nodo* sig; 
}nodo;

nodo* Insertar_LIFO(nodo *l, mediciones d){        //Inserta elementos al incio de la lista
    nodo *nuevo;
    nuevo=(nodo*) malloc (sizeof (nodo));
    if (nuevo==NULL)
        exit (1);
    nuevo->dato=d;                          //Almaceno d en el nuevo nodo
    nuevo->sig =l;                          //Pongo a el sig del nuevo nodo apuntado a l
    return nuevo;                           //devuelvo nuevo, porque es el nuevo primer elemento de la lista
}

nodo* Insertar_FIFO(nodo *l, mediciones d){      //Ingresa elementos al final de la lista
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

nodo* Lee_archivo_LIFO(){
    FILE* f;
    nodo *l=NULL;
    int i=0;
    int temp_int;
    float temp_float;
    mediciones temp_med;
    
    f = fopen("mediciones.dat","rb");
    if(f==NULL){                         //no puede abrir el archivo
        printf("Error al abrir el archivO\n\n");
        exit(2);
    }
    else{                               //abre el archivo
        while(fread(&temp_med.ppm,sizeof(temp_med.ppm),1,f)== 1 && fread(&temp_med.temp,sizeof(temp_med.temp),1,f)==1){
            l= Insertar_LIFO(l,temp_med);
            i++;
        }
        printf("\nSe leyeron %d mediciones\n",i);
        if (fclose(f)!=0){
            printf("Error al cerrar el archivo\n\n");
            exit (3);
        }
        printf("Archivo leído correctamente\n");
    }
    return l;
}

void Mostrar_lista(nodo *l){
    if(l==NULL)
        printf("\nLista vacía\n\n");
    else{
        printf("Lista:");
        while(l!=NULL){
            printf("->(%d",l->dato.ppm);
            printf(",%.2f)",l->dato.temp);
            l=l->sig;
        }
        printf("\n\n");
    }
}

nodo* Inserta_med(nodo* l){
    mediciones temp_med;
    printf("\nIngrese la concentación de CO en ppm:");
    scanf("%d",&temp_med.ppm);
    printf("\nIngrese la temperatura:");
    scanf("%f",&temp_med.temp);
    l=Insertar_FIFO(l,temp_med);
    printf("\n Dato ingresado\n");
    Mostrar_lista(l);
    return l;
}

extremos Busca_extremos(nodo* l){
    nodo *actual=NULL;
    extremos temp;

    temp.max=0;
    temp.min=0;    

    if(l==NULL){
        printf("\nLista vacía\n\n");
        return temp;
    }
    else{
        temp.max=l->dato.ppm;
        temp.min=l->dato.ppm;
        actual=l;
        while(actual!=NULL){
            if(actual->dato.ppm >= temp.min)
                temp.max=actual->dato.ppm;
            if(actual->dato.ppm <= temp.min)
                temp.min=actual->dato.ppm;
            actual=actual->sig;
        }
        printf("\nLa máxima concentración es %d y la mínima es %d\n\n", temp.max,temp.min);
        return temp;
    }
}

nodo* Eliminar_nodo (nodo*l,int d){
    nodo *ret =l, *aux=NULL;
    if(l==NULL)                        //lista nula
        printf("\nLista vacía\n");
    else{                              //lista no nula
        if(l->dato.ppm == d){              //caso en el que el nodo a borrar es el primero                
            ret = l->sig;
            free(l);
            printf("Medición de concetración CO %d ppm eliminada\n",d);
        }
        else{                                           //caso en el que el nodo a borrar no es el primero
            while(l->sig!=NULL && l->sig->dato.ppm!=d)
                l=l->sig;                               //pongo a l apuntando al siguiente
            if(l->sig!=NULL){                           //si l->sig!=NULL es porque el dato a borar existe, de lo contrario hubiera llegado al final de la lista
                aux = l->sig;
                l->sig = aux->sig;
                free(aux);
                printf("\nMedición de concetración CO %d ppm eliminada\n",d);
            }
            else
                printf("El dato %d no existe en la lista\n",d);
       }
    }
    return ret;
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

int main (){
    int opcion;
    nodo *lista_m=NULL;
    extremos pc;
    
    do{
        printf("1__Leer y almacenar en lista\n");                
        printf("2__Agregar medición\n");       
        printf("3__Mediciones de  CO máximas y mínimas\n");
        printf("4__Eliminar medicion máxima y mínima\n");
        printf("5__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                lista_m = Lee_archivo_LIFO();
                Mostrar_lista(lista_m);
                break;
            case 2:
                lista_m=Inserta_med(lista_m);
                break;
            case 3:
                pc =Busca_extremos(lista_m);
                break;
            case 4:
                lista_m =Eliminar_nodo(lista_m,pc.max);
                lista_m =Eliminar_nodo(lista_m,pc.min);
                Mostrar_lista(lista_m);
                break;
            case 5:
                printf("Finalizó programa\n");
                break;
            default:
                printf("Opción inválida\n");
        }
    }while (opcion != 5);
    lista_m=Destruir_lista(lista_m);
    return 0;
}
