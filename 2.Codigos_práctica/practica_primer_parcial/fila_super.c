# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct turno{
    char alias[10];
    int numero;
}turno;

typedef struct nodo{
    turno dato; 
    struct nodo* sig; 
}nodo;

nodo* Insertar_FIFO(nodo *l, turno d){      //Ingresa elementos a la lista
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
        printf("Lista:\n");
        while(l!=NULL){
            printf("-->%s",l->dato.alias);
            printf("-%d",l->dato.numero);
            l=l->sig;
        }
        printf("\n");
    }
}

nodo* Eliminar_primer_nodo (nodo*l){
    nodo *ret =l, *aux=NULL;
    if(l==NULL)                        //lista nula
        printf("\nLista vacía\n");
    else{                              //lista no nula
        ret = l->sig;                  //guardo el inicio de la lista
        free(l);                       //elimino la variable a eliminar 
    }
    return ret;
}


nodo* Cargar_turno(nodo*l){
    turno turno_a_cargar;
    nodo* aux =NULL;
    int repetido=0;

    printf("\nIngrese su alias:");
    scanf("%s",turno_a_cargar.alias);
    while (repetido == 0){
        printf("\nIngrese un número entero de 3 dígitos:");
        scanf("%d",&turno_a_cargar.numero);
        if(l==NULL){                                        //caso lista vacia
            l=Insertar_FIFO(l,turno_a_cargar);
            repetido = 1;
        }
        else{                                                    //caso en el que hay nodos en lista
            if(l->dato.numero == turno_a_cargar.numero)          //caso donde el que coincide es el primer dato de la lista
                printf("\n numero ingresado está asignado a %s, por favor ingrese otro:\n",l->dato.alias);
            else{                                                //caso donde la coincidencia se da con el segundo u otro nodo mas adelante
                aux=l;
                while(aux->sig!=NULL && aux->sig->dato.numero != turno_a_cargar.numero)
                    aux=aux->sig;
            /*salio del while porque o llegó al final de la lista o encontró una conicidencia*/
                if(aux->sig == NULL){                          //si llegó al final de la lista lo carga
                    l=Insertar_FIFO(l,turno_a_cargar);
                    repetido = 1;
                }
                else                                           //si no llegó pide otro
                    printf("\n numero ingresado está asignado a %s, por favor ingrese otro:\n",aux->sig->dato.alias);
            }    
        }
    }
    return l;
}

nodo* Atender_turno(nodo* l){
    if(l!=NULL){   
        printf("\nDatos primera posición: %s-%d \n",l->dato.alias,l->dato.numero);
        l = Eliminar_primer_nodo(l);
        Mostrar_lista(l);
    }
    else
        printf("\n No hay turnos para atender \n\n");
    return l;

}

void Mi_lugar(nodo* l){
    int numero,i=0;
    nodo* aux;

    if (l==NULL)
        printf("No hay datos en la lista\n\n");
    else{
        printf("\nIngrese el número de su turno\n");
        scanf("%d",&numero);
        if (l->dato.numero == numero)
            printf("Usted es el siguiente en la lista\n\n");
        else{
            aux=l;
            while( aux->sig!=NULL && aux->sig->dato.numero!=numero){
                aux = aux->sig;
                i++;
            }
            if(aux->sig==NULL)
                printf("El número ingresado no está en la fila\n\n");
            else
                printf("Usted esta en la posición %d\n\n",i+2);
        }
    }
}

void Guardar_lista(nodo* l){
    FILE* f;
    nodo* aux;
    if (l==NULL)                                                     //caso lista NULL
        printf("Lista vacia\n\n");
    else{                                                            //caso lista NO NULL
        f=fopen("turnos.dat","wb");
        if(f==NULL){
            printf("Error al abrir el archivo\n\n");
            exit(2);
        }
        else{
            if(l->sig == NULL){                                      //lista con un solo nodo
                if(fwrite(&l->dato,sizeof(l->dato),1,f) == 1){
                    printf("Archivo guardado correctamente, solo un turno encontrado\n\n");
                }
                else
                    printf("No se pudo guardar el archivo");  
            }
            else{
                aux = l;                                             //lista con mas nodos
                if(fwrite(&l->dato,sizeof(l->dato),1,f)!=1)          //leo el primero separado
                    printf("Error al leer el primer archivo");
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

nodo* Lee_archivo(){
    FILE* f;
    nodo* l = NULL;
    turno turno_leido;
    int i=0;
    
    f = fopen("turnos.dat","rb");
    if(f==NULL)                         //no puede abrir el archivo
        printf("Error al abrir el archivo, verifique que ya lo haya creado\n\n");
    else{                               //abre el archivo
        while( fread(&turno_leido,sizeof(turno_leido),1,f) == 1){
            l = Insertar_FIFO(l,turno_leido);
            printf("Econtre %s-%d\n",turno_leido.alias,turno_leido.numero);
            i++;
        }
        printf("Se encontraron %d turnos en el archivo\n",i);
        Mostrar_lista(l);
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo\n\n");
    }
    return l;
}

nodo* Destruir_lista(nodo* l){
    nodo* aux;
    if (l==NULL)
        printf("Lista vacía\n");
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
    nodo *lista=NULL;
    nodo *lista_leida = NULL;
       
    do{
        printf("1__Cargar nuevo turno\n");                
        printf("2__Atender turno\n");       
        printf("3__Mi lugar en la lista\n");
        printf("4__Mostrar fila\n");
        printf("5__Guardar lista\n");
        printf("6__Leer lista\n");
        printf("7__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                lista=Cargar_turno(lista);
                Mostrar_lista(lista);
                break;
            case 2:
                lista = Atender_turno(lista);
                break;
            case 3:
                Mi_lugar(lista);
                break;
            case 4:
                Mostrar_lista(lista);
                break;
            case 5:
                Guardar_lista(lista);
                break;
            case 6:
                lista_leida = Lee_archivo();
                break;
            case 7:
                printf("Finalizó programa\n");
                break;                
        }
    }while (opcion != 7);
    return 0;
}
