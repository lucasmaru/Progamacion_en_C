/*3. Escriba una función que devuelva la cantidad de elementos de una lista.*/
 # include <stdio.h>
 # include <stdlib.h>

typedef struct nodo {//Declaro el tipo de esructura nodo
    int dato;
    struct nodo *sig;
}nodo;

nodo* Insertar_LIFO(nodo *l, int d){//Ingresa elementos a la lista
    nodo *nuevo;
    nuevo=(nodo*) malloc (sizeof (nodo));
    if (nuevo==NULL)
    exit (1);
    //nuevo=l;//nuevo a punta al mismo espacip que l, que es el primer elemento de la lista
    nuevo->dato=d;//Almaceno d en el nuevo nodo
    nuevo->sig =l;//Pongo a el sig del nuevo nodo apuntado a l, pues debe ser primero de la lista
    return nuevo;//devuelvo nuevo, porque es el nuevo primer elemento de la lista
}
void Mostrar_lista(nodo *l){
    printf("Lista:");
    while(l!=NULL){
        printf("-->%d",l->dato);
        l=l->sig;
    }
    printf("\n");
}

nodo* Pedir_datos(nodo *l){
    int temp;
    printf("Ingrese el entero deseado (sale con 0):\n");
    scanf("%d",&temp);
    if (temp!=0){
        while (temp!=0){            
            l=Insertar_LIFO(l,temp);
            printf("Ingrese el siguiente dato (sale con cero)\n");
            scanf("%d",&temp);
        }
    }
    else printf("Salio del programa\n");
    return l;
}

int Contar_lista(nodo *l){
    int i=0; // un contador
    nodo* aux; // para recorrer la lista 
    if (l==NULL)
        printf("La lista esta vacia\n");
    if (l!=NULL){//entonces apunta a algo    
        i++;//si l apunta a algo hay un nodo i=1
        aux=l; //para recorrer la lista sin perder el inicio
        while (aux->sig!=NULL){
            i++;
            aux=aux->sig;
        }
    }
    return i;
}

nodo* Destruir(nodo *l){
    nodo *aux;// Para no perder referencia cuando voy borrando elementos
    while (l!=NULL){
        aux=l;
        l=l->sig;
        free(aux);
    }
    printf("Lista destruida");
    return NULL;
}

 int main (){
    int elem;
    nodo* lista=NULL;
    lista=Pedir_datos(lista);
    Mostrar_lista(lista);
    elem=Contar_lista(lista);
    printf("La cantidad de elementos en la lista es %d \n",elem);
    Destruir(lista);
    return 0;
 }