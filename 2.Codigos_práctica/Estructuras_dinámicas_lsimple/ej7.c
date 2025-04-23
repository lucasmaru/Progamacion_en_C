/*7. Se tiene una lista ordenada de números enteros y se pide hacer una función que inserte un
elemento a la lista, manteniéndola ordenada.
*/
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

nodo* Insertar_ordenado(nodo *l, int d){//Asume que la lista esta ordenada previamente y que los datos van aumentando en modulo
    nodo *aux;//recorre la lista    
    nodo *nuevo;//almacena el nuevo dato
    nuevo=(nodo*)malloc(sizeof(nodo));
    if (nuevo==NULL)
        exit (3);//Si no puede reservar memoria interrumpe el programa
    nuevo->dato=d;//almaceno el nuevo dato y luego decido donde pongo el nodo
    if (l==NULL||d<=l->dato){//Lista vacia o d es menor que el primer dato
        nuevo->sig=l;//Cambio el primer elemento de la lista
        return nuevo;
    }
    aux=l;//Si esto no pasa uso aux para buscar la poscisión correcta
    while(aux->sig!=NULL && aux->sig->dato<d)//Recorro la lista, hasta que veo el final o encontre el lugar adecuado
        aux=aux->sig;
    //cuando sale del while aux apunta al último nodo o al nodo anterior la posición indicada
    nuevo->sig=aux->sig;
    aux->sig=nuevo;
    return l;
}

nodo* Pedir_datos(nodo *l){
    int temp, modo;
    printf("Ingrese el entero deseado (sale con 0):\n");
    scanf("%d",&temp);
    if (temp!=0){
        while (temp!=0){  
            printf("Insertar LIFO(1) o FIFO(2) o Ordenado(3):");
            scanf("%d",&modo);
            if (modo==1)          
                l=Insertar_LIFO(l,temp);
            else if(modo==2)    
                l=Insertar_FIFO(l,temp);
            else if(modo==3)
                l=Insertar_ordenado(l,temp);
            else
                printf("Modo de ingreso erroneo, dato no insertado \n");
            printf("Ingrese el siguiente dato (sale con cero)\n");
            scanf("%d",&temp);
        }
    }
    else printf("Salio del programa\n");
    return l;
}

nodo* Eliminar(nodo *l, int d){//Elimina el dato deseado de la lista
nodo *aux=NULL;
nodo *ret=l;
if (l==NULL)//Si la lista esta vacia no entra al else
    printf("Lista vacia");
else//Si hay algo en la lista entra acá
    if(l->dato==d){//Si el valor a borrar es el primero
        ret=l->sig;
        free(l);
        printf("Elemento elminiado\n");
    }
    else{//El elemento a borrar no es el primero
        while(l->sig!=NULL && l->sig->dato!=d)
            l=l->sig;
        if(l->sig!=NULL){//Salio del while porque encontró d, entonces tengo a l apuntando al nodo anterior al que quiero elminar
            aux=l->sig;//Aux apunta al nodo a eliminar
            l->sig=aux->sig;
            free(aux);
        }
        else//Salio del while porque llegó al final
            printf("Dato a eliminar no existe en lista");    
    }
    return ret;
}

void Guardar(nodo *l){
    FILE *arch;
    int n=0;
    arch=fopen("lista.dat","wb");
    if (arch==NULL){
        printf("Error al abrir el archivo para escritura");
        exit(4);
    }
    else{
        while(fwrite(&(l->dato),sizeof(l->dato),1,arch) == 1){
            printf("guardo: %d\n", l->dato);
            l=l->sig;
            n++;
        }
        printf("Se grabo %d datos\n",n);
        if(fclose(arch)!=0){
            printf("Error al cerrar el archivo");
            exit(5);
        }
    }
}

void Mostrar_lista(nodo *l){
    printf("Lista:");
    while(l!=NULL){
        printf("-->%d",l->dato);
        l=l->sig;
    }
    printf("\n");
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
    nodo *lista=NULL;
    int opcion, elim;
    
    do{
        printf("1_Ingresar datos a la lista\n");
        printf("2_Mostrar lista\n");
        printf("3_Eliminar un nodo de la lista\n");
        printf("4_Guardar lista\n");
        printf("5_Salir\n");
        printf("Seleccione una opcion del menu ");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1: lista=Pedir_datos(lista);
            break;
        case 2: Mostrar_lista(lista);
            break;
        case 3: printf("Dato a elminar: \n");
                scanf("%d",&elim);
                lista=Eliminar(lista,elim);
            break;
        case 4: Guardar(lista);
            break;
        case 5: lista=Destruir(lista);
            break;        
        default:printf("Opcion incorrecta\n");
            break;
        }

    } while (opcion!=5);
    return 0;
}