/*4. Dada una lista enlazada, formada por números enteros, hacer un programa que la divida en dos
listas: pares e impares.*/
# include <stdio.h>
# include <stdlib.h>

typedef struct nodo {//Declaro el tipo de esructura nodo
    int dato;
    struct nodo *sig;}nodo;

nodo* Insertar_LIFO(nodo *l, int d){//Ingresa elementos a la lista
    nodo *nuevo;
    nuevo=(nodo*) malloc (sizeof (nodo));
    if (nuevo==NULL)
    exit (1);
    nuevo->dato=d;//Almaceno d en el nuevo nodo
    nuevo->sig =l;//Pongo a el sig del nuevo nodo apuntado a l, pues debe ser primero de la lista
    return nuevo;}//devuelvo nuevo, porque es el nuevo primer elemento de la lista


void Mostrar_lista(nodo *l){
    printf("Lista:");
    while(l!=NULL){
        printf("-->%d",l->dato);
        l=l->sig;
    }
    printf("\n");}


nodo* Pedir_datosLIFO(nodo *l){
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
    return l;}


nodo* Destruir(nodo *l){
    nodo *aux;// Para no perder referencia cuando voy borrando elementos
    while (l!=NULL){
        aux=l;
        l=l->sig;
        free(aux);
    }
    printf("Lista destruida");
    return NULL;}


nodo** Separa(nodo *l){//la función devuelve un puntero a puntero nodo
    nodo* par=NULL;
    nodo* impar=NULL;
    nodo* aux=NULL;//puntero que recorre la lista original
    nodo** ptr;//puntero a punteros tipo nodo que vuelve al main
    int temp;//almacena temporalmente el dato del nodo
    if (l==NULL){ //Si l no apunta a un nodo entonces esta vacío y cierra el programa
        printf("La lista esta vacia");
        exit (1);
    }//Si llegó acá la lista tiene al menos un nodo
    aux = l; //uso aux para moverme en la lista sin perder l

    while (aux != NULL){ //Si esto sucede debo ver si el dato es par o impar
        if(aux->dato%2 == 0){
            temp=aux->dato;//si es par me copio el dato en temp
            par=Insertar_LIFO(par,temp);//Inserto el dato par en la nueva lista
        }else{
            temp=aux->dato;//si es impar me copio el dato en temp
            impar=Insertar_LIFO(impar,temp);//Inserto el dato par en la nueva lista
        }
        aux=aux->sig;//avanzo un nodo para que pase por la condicion del while
    }
    ptr=(nodo**)malloc(sizeof(nodo)*2);
    ptr[0]=par;
    ptr[1]=impar;
    return ptr;
}

int main (){
    nodo* lista=NULL;
    nodo* lpar=NULL;
    nodo* limpar=NULL;
    nodo** aux;
    lista = Pedir_datosLIFO(lista);
    aux=Separa(lista);
    lpar=aux[0];
    limpar=aux[1];
    Mostrar_lista(lista);
    Mostrar_lista(lpar);
    Mostrar_lista(limpar);
    lista=Destruir(lista);
    printf("\n");
    lpar=Destruir(lpar);
    printf("\n");
    limpar=Destruir(limpar);
    return 0;
}