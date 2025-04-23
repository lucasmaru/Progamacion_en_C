/*Practica 1er parcial*/
# include <stdlib.h>
# include <stdio.h>

typedef struct medicion{
    int id;
    double act;
}medicion;

typedef struct nodo_id{
    int id;
    struct nodo_id* sig;
}nodo_id;

typedef struct nodo_actividad{
    double actividad;
    struct nodo_actividad* sig;
}nodo_actividad;

typedef struct almacena_listas{
    nodo_id* lista_id;
    nodo_actividad* lista_act; 
}almacena_listas;

nodo_id* Insertar_FIFO_id(nodo_id *l, int d){    //Ingresa elementos a la lista
    nodo_id* nuevo;
    nodo_id* aux;                                //recorre la lista 
    nuevo=(nodo_id*) malloc (sizeof (nodo_id));  //reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);                                    //valida la reserva de memoria
    nuevo->id=d;                               //Almaceno d en el nuevo nodo
    nuevo->sig =NULL;                            //Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)                                  //si recibe un puntero que no apunta nada, es decir no hay nodos en la lista devuelve a nuevo como el primer nodo
        return nuevo;                               
    aux=l;                                       //si hay otros nodos,pongo a aux apuntado al mismo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;                            //ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;}//devuelvo l, porque sigue siendo el primer elemento de la lista

nodo_actividad* Insertar_LIFO_act(nodo_actividad *l, double d){
    nodo_actividad *nuevo;
    nuevo=(nodo_actividad*) malloc (sizeof (nodo_actividad));
    if (nuevo==NULL)
        exit (1);
    nuevo->actividad=d;//Almaceno d en el nuevo nodo
    nuevo->sig =l;//Pongo a el sig del nuevo nodo apuntado a l
    return nuevo;//devuelvo nuevo, porque es el nuevo primer elemento de la lista
}

void Ingresa_datos(){
    FILE* f;                         //puntero al archivo
    int aux_graba,cant_mediciones=0; //aux graba para controlar el fwrite
    medicion aux_medicion;           //almacena los datos que pido

    aux_medicion.id=1;    
    f = fopen("mediciones.dat","wb");
    if(f==NULL){
        printf("Error al abrir el archivo para escritura");
        exit(2);
    }
    else{
        while(aux_medicion.id != 0){
            printf("Ingrese identificador de neurona (entero positivo),sale con 0: \n");  //pido id_neurona
            scanf("%d",&aux_medicion.id);
            if(aux_medicion.id!=0){                                                       //valido dato
                while(aux_medicion.id<0){
                    printf("Valor ingresado no válido, reingrese.\n");
                    printf("Ingrese identificador de neurona (entero positivo),sale con 0: \n");
                    scanf("%d",&aux_medicion.id);
                }                                                                         //acá el id ya está validado
                printf("Ingrese el nivel de activación de la neurona:");                  //pido act_neuronal
                scanf("%lf",&aux_medicion.act);
                while(aux_medicion.act<0 || aux_medicion.act>1){                        //valido act_neuronal
                    printf("Valor ingresado no válido, reingrese.\n");
                    printf("Ingrese el nivel de activación de la neurona (número entre 0 y 1): \n");
                    scanf("%lf",&aux_medicion.act);
                }                                                                         //acá ya tengo toda la medición validada  
                aux_graba = fwrite(&aux_medicion,sizeof(aux_medicion),1,f);               //graba el archivo
                if(aux_graba!=1){                                                         //valida la grabación  
                    printf("Error al grabar el arhivo\n");
                    exit(3);
                }
                else
                    printf("Medición guardada\n");
            }
            cant_mediciones++;
        }
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo");
        printf("Se guardaron %d mediciones en el archivo\n\n",(cant_mediciones-1));          //imprimo el resultado, restando el último ingreso al ciclo que no graba nada realmente
    }
}

almacena_listas Leer_y_almacenar(){
    FILE* f;                          //para abrir el archivo
    medicion aux_medicion;            //para almacenar el dato leído del archivo
    int i=0;                          //cuenta los datos leídos
    nodo_id* lista_id = NULL;         //nodos de la lista de id 
    nodo_actividad* lista_act = NULL; //nodos de la lista act
    almacena_listas contenedor;       //estructura que almacena los dos punteros y los retorna al main 

    contenedor.lista_id = NULL;       //Inicializo los punteros del contendor
    contenedor.lista_act = NULL;
    
    f=fopen("mediciones.dat","rb");
    if (f==NULL){
        printf("\nError al abrir el archivo, verifique que el archivo haya sido generado\n\n");
    }
    else{      
        while((fread(&aux_medicion,sizeof(aux_medicion),1,f)) == 1){         //leo un elemento
            printf("id: %d\n",aux_medicion.id);
            printf("actividad: %lf\n",aux_medicion.act);
            lista_id=Insertar_FIFO_id(lista_id,aux_medicion.id);
            lista_act=Insertar_LIFO_act(lista_act,aux_medicion.act);
            i++;
        }
        contenedor.lista_id = lista_id;
        contenedor.lista_act = lista_act;
        return contenedor;
    }
    return contenedor;
}

void Mayor_activacion(nodo_actividad* l){
    double mayor;
    nodo_actividad* aux;
    if(l==NULL)
        printf("\nLista vacía, lea los datos y reintente\n\n");
    else{
        aux = l;
        mayor = aux->actividad;
        while(aux != NULL){            
            if(aux->actividad >= mayor)
                mayor = aux->actividad;
            aux=aux->sig;
        }
        printf("\nEl activación mas cercana a 1 es: %lf \n\n",mayor);

    }
}

void Mostrar_lista_id(nodo_id *l){
    if(l==NULL)
        printf("\nLista vacía\n");
    else{
        printf("Lista:");
        while(l!=NULL){
            printf("-->%d",l->id);
            l=l->sig;
        }
        printf("\n");
    }
}

void Mostrar_lista_act(nodo_actividad *l){
    if(l==NULL)
        printf("\nLista vacía\n");
    else{
        printf("Lista:");
        while(l!=NULL){
            printf("-->%lf",l->actividad);
            l=l->sig;
        }
        printf("\n");
    }
}


nodo_id* Intercambia_primero_por_ultimo(nodo_id* l){
    nodo_id* aux = NULL;
    int primero, ultimo;
    if (l == NULL){
        printf("\nLista vacía\n\n");
        return l;
    }
    else{
        aux=l;
        while(aux->sig!=NULL){
            aux=aux->sig;
        }
        ultimo = aux->id;
        primero = l->id;

        l->id = ultimo;
        aux->id = primero;
        return l;
    }
}

int main(){
    int opcion;
    almacena_listas contenedor;
    contenedor.lista_act = NULL;
    contenedor.lista_id = NULL;
    do{
        printf("1__Leer archivo y almacenar datos\n");            //lo hace en dos listas, una para identificadores y otra para niveles de activación, pero la última de atras para delante    
        printf("2__Informar mayor nivel de activación\n");       //más cercano a 1
        printf("3__Intercambia primer valor de lista de activadores por el último\n");
        printf("4__Genera archivo ingresando las mediciones por teclado\n");
        printf("5__Mostrar listas\n");
        printf("6__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                contenedor=Leer_y_almacenar();
                break;
            case 2:
                Mayor_activacion(contenedor.lista_act);
                break;
            case 3:
            contenedor.lista_id=Intercambia_primero_por_ultimo(contenedor.lista_id);
                break;
            case 4:
                Ingresa_datos();
                break;
            case 5:
                Mostrar_lista_id(contenedor.lista_id);
                Mostrar_lista_act(contenedor.lista_act);
                break;
            case 6:
                printf("Finalizó programa\n");
                break;
        }
    }while (opcion != 6);
    return 0;
}
