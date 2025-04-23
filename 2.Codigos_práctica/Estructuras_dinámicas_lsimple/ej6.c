/*6. Escribir una función que busque un elemento de la lista, por comparación con una clave e
indique si se encuentra o no. Si se encuentra se informará este elemento y también el anterior
(en caso de existir).*/
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
    //nuevo=l;//nuevo a punta al mismo espacio que l, que es el primer elemento de la lista
    nuevo->dato=d;//Almaceno d en el nuevo nodo
    nuevo->sig =l;//Pongo a el sig del nuevo nodo apuntado a l, pues debe ser primero de la lista
    return nuevo;//devuelvo nuevo, porque es el nuevo primer elemento de la lista
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
    return l;}//devuelvo l, porque sigue siendo el primer elemento de la lista

nodo* Pedir_datos(nodo *l){
    int temp, modo;
    printf("Ingrese el entero deseado (sale con 0):\n");
    scanf("%d",&temp);
    if (temp!=0){
        while (temp!=0){  
            printf("Insertar LIFO(1) o FIFO(2):");
            scanf("%d",&modo);
            if (modo==1)          
                l=Insertar_LIFO(l,temp);
            else if(modo==2)    
                l=Insertar_FIFO(l,temp);
            else
                printf("Modo de ingreso erroneo, dato no insertado \n");
            printf("Ingrese el siguiente dato (sale con cero)\n");
            scanf("%d",&temp);
        }
    }
    else printf("Salio del programa\n");
    return l;
}

void Mostrar_lista(nodo *l){
    printf("Lista:");
    while(l!=NULL){
        printf("-->%d",l->dato);
        l=l->sig;
    }
    printf("\n");
}

void Busca_y_Muestra(nodo* l){
    int busca;
    int cont=1;
    nodo *aux;
    if (l==NULL){
        printf("Lista vacía");
        exit(3);
    }//Si llega acá es porque hay al menos un dato
    printf("Entero a buscar en lista: \n");
    scanf("%d",&busca);
    if (l->dato==busca)//evaluo el primer dato
        printf("Dato del primer nodo coincide con el dato buscado: %d, no hay nodo anterior",busca);
    aux=l->sig;//aux y l apuntan al primer nodo de la lista        
    while(aux!=NULL){
        cont++;
        if (aux->dato==busca){//Si el dato coincide lo muestro y muestro el anterior
            printf("Dato de nodo %d coincide con el elemento buscado %d \n",cont,busca);
            printf("El elemento anterior es el nodo %d y contiene el dato %d\n",cont-1,l->dato);
        }
        aux=aux->sig;//Avanzo aux al sig nodo
        l=l->sig;//Avanzo l al siguiente nodo
    }
    printf("fin de lista sin mas coincidencias");
}

int main (){
    nodo* lista=NULL;
    lista=Pedir_datos(lista);
    Mostrar_lista(lista);
    Busca_y_Muestra(lista);

    return 0;
}