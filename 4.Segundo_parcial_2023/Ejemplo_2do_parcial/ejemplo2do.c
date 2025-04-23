/*Ejemplo de ejercicio tomado en segundo en 2do parcial

El archivo rtc.bin es un archivo binario de tamaño desconocido pero menor a 256 bytes.
Los primeros 64 bytes del archivo corresponden a los registros/memoria del RTC de una PC.
Se pide escribir un programa en C que lea el archivo y muestre un menú repetitivo que en base a su contenido permita las
siguientes opciones

1) Informar el tamaño del archivo
2) Mostrar la hora en formato hh:mi:ss
3) Mostrar el año completo en formato aaaa, es decir, si fuera 2022 debería mostrar "2022"
4) Informar si el bit AIE está activo (si/no)
5) Salir


Ejemplos de preguntas teóricas:

¿Cúal es la diferencia entre un Microprocesador y un Microcontrolador?

¿Cúales son las 3 etapas del Pipeline de un Cortex M3 y cúal es su ventaja?*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct nodo{                   
    unsigned char dato; 
    struct nodo* sig; 
}nodo;

nodo* Insertar_FIFO(nodo *l, unsigned char d){      //Ingresa elementos al final de la lista
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

nodo* Lee_archivo_FIFO(){
    FILE* f;
    nodo* l = NULL;
    int i=0;
    unsigned char temp;
    
    f = fopen("rtc.bin","rb");
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

void Tamaño_archivo(nodo *l){
    int i=0;
    if(l==NULL)
        printf("\nLista vacía\n\n");
    else{
        while(l!=NULL){
            i++;
            l=l->sig;
        }
    printf("\nHay %d datos en el archivo.\n\n",i);
    }
}

nodo* Adelanta(nodo *l,int cant){
    int i;
    for (i=0;i<cant;i++)
        l=l->sig;
    return l;        
}

void Mostrar_hora(nodo *l){
   unsigned char hora,min,seg;
    nodo *aux;
    if(l==NULL)
        printf("\nLista vacía\n\n");
    else{
        aux=l;
        seg=aux->dato;
        aux=Adelanta(aux,2);
        min=aux->dato;
        aux=Adelanta(aux,2);
        hora=aux->dato;
        printf("\nLa hora es %02x:%02x:%02x\n\n",hora,min,seg);
    }
}

void Mostrar_año(nodo *l){
    unsigned char año_ult,año_prim;
    nodo *aux;
    if(l==NULL)
        printf("\nLista vacía\n\n");
    else{
        aux=l;
        aux=Adelanta(aux,9);
        año_ult=aux->dato;
        aux=l;
        aux=Adelanta(aux,50);
        año_prim =aux->dato;
        printf("\n%02x%02x\n\n",año_prim,año_ult);

    }
}

void AIE(nodo *l){
    nodo *aux;
    unsigned char reg_b;
    aux=l;
    aux=Adelanta(aux,10);
    reg_b = aux->dato;
    printf("%x\n",reg_b);
    if((reg_b & 0x20) != 0)
        printf("\nAIE activado\n\n");
    else
        printf("AIE desactivado");
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


int main(){
    int opcion;
    nodo* lista=NULL;

    lista=Lee_archivo_FIFO();
    
    do{
        printf("1__Informar el tamaño del archivo\n");                
        printf("2__Mostrar la hora en formato hh:mi:ss\n");       
        printf("3__Mostrar el año completo en formato aaaa\n");
        printf("4__Informar si el bit AIE está activo (si/no)\n");
        printf("5__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                Tamaño_archivo(lista);
                break;
            case 2:
                Mostrar_hora(lista);
                break;
            case 3:
                Mostrar_año(lista);
                break;
            case 4:
                AIE(lista);
                break;                
            case 5:
                lista=Destruir_lista(lista);
                printf("Finalizó programa\n");
                break;
            default:
                printf("Opción inválida\n");
        }
    }while (opcion != 5);
    return 0;
}
