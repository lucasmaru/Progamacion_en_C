/*Lee el archivo lista.dat y arma una lista*/
# include <stdio.h>
# include <stdlib.h>

typedef struct nodo {//Declaro el tipo de esructura nodo
    int dato;
    struct nodo *sig;
}nodo;

void Mostrar_lista(nodo *l){
    printf("Lista:");
    while(l!=NULL){
        printf("-->%d",l->dato);
        l=l->sig;
    }
    printf("\n");
}

nodo* Insertar_FIFO(nodo *l, int d){//Ingresa elementos a la lista
    nodo* nuevo;
    nodo* aux;//recorrer la lista 
    nuevo=(nodo*) malloc (sizeof (nodo));//reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (2);//valida la reserva de memoria
    nuevo->dato=d;//Almaceno d en el nuevo nodo
    nuevo->sig =NULL;//Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)//si no hay nodos
        return nuevo;
    aux=l;//pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;//ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;
    }//devuelvo l, porque sigue siendo el primer elemento de la lista

nodo* leer(nodo *l){
    FILE *f;
    int *aux;
    int j=0;//cuenta los datos que lee
    f=fopen("lista.dat","rb");//Abro archivo
    if (f==NULL){
        printf("Error al abrir el archivo \n");//Valido la apertura
        exit(1);
    }
    else{
        aux;
        aux=(int*)malloc(sizeof(int));//Reservo memoria para almacenar un dato
        while(fread(&aux[j],sizeof(int),1,f)==1){
            printf("Dato:%d \n",aux[j]);
            j++;
            l=Insertar_FIFO(l,aux[j]);
        }
        printf("Se leyeron %d datos \n",j);
        if(fclose(f)!=0){
            printf("Error al cerrar el archivo");
            exit (2);
        }
        return l;
    }
}

int main(){
    nodo *lista=NULL;
    int *datos;
    printf("chequ");
    lista=leer(lista);
    printf("chequ");
    Mostrar_lista(lista);
    

    return 0;
}