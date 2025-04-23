# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct dato{
    char nombre[15];
    int edad;
}nombreyedad;

typedef struct nodo{
    nombreyedad dato;                                  
    struct nodo *ant, *sig;
}nodo;

typedef struct ldoble{
    nodo *prim, *ult;
}lista;

lista Insertar_FIFO_d(lista l, nombreyedad d){
    nodo* nuevo;
    nuevo = (nodo*) malloc(sizeof(nodo));
    if (nuevo == NULL)
        exit(1);
    nuevo->dato = d;
    nuevo->sig = NULL;
    nuevo->ant =l.ult;
    if(l.prim==NULL)          //lista vacia =>l.prim y l.ult apuntan a NULL
        l.prim=nuevo;          
    else
        l.ult->sig = nuevo;
    l.ult = nuevo;
    return l;  
}

void Mostrar_lista_directo(lista l){
    if (l.prim==NULL)
        printf("\n");
    else{
        printf("Lista:\n");
        while(l.prim!=NULL){
            printf("-->(%s",l.prim->dato.nombre);
            printf(",%d)",l.prim->dato.edad);
            l.prim=l.prim->sig;
        }
        printf("\n\n");
    }
}

lista Ingresar_personas(lista l){
    nombreyedad temp;

    printf("\nIngrese edad(finaliza con cero):");
    scanf("%d",&temp.edad);
    while(temp.edad < 0 || temp.edad >150){
        printf("\nDato incorrecto reingrese:");
        scanf("%d",&temp.edad);
    }
    while(temp.edad!=0){ 
        printf("\nIngrese nombre:");
        scanf("%s",temp.nombre);               
        l=Insertar_FIFO_d(l,temp);
        printf("\nIngrese edad(finaliza con cero):");
        scanf("%d",&temp.edad);
    }
    Mostrar_lista_directo(l);

    return l;
}

lista Destruir_lista_anterior(lista l){
    nodo *p, *aux;

    p=l.prim;
    while(p!=NULL){
        aux = p;
        p = p->sig;
        free(aux);
    }
    printf("\nLista anterior destruida\n");
    l.prim = NULL;
    l.ult = NULL;
    return l;
}

lista Destruir_lista_final(lista l){
    nodo *p, *aux;

    p=l.prim;
    while(p!=NULL){
        aux = p;
        p = p->sig;
        free(aux);
    }
    printf("\nLista destruida destruida\n");
    l.prim = NULL;
    l.ult = NULL;
    return l;
}

lista Sublista(lista lmaestra){
    int umbral;
    lista lmayores;
    nodo *aux_maestra=NULL;

    lmayores.prim=NULL;
    lmayores.ult=NULL;

    if(lmaestra.prim==NULL){
        printf("\nLista vacía\n\n");
        return lmayores;
    }
    else{
        printf("Ingrese umbral de edad:\n");
        scanf("%d",&umbral);

        if(lmayores.prim!=NULL){
            printf("entre al if");
            lmayores=Destruir_lista_anterior(lmayores);
        }

        aux_maestra=lmaestra.prim;
        while(aux_maestra != NULL){
            if(aux_maestra->dato.edad > umbral){
                lmayores=Insertar_FIFO_d(lmayores,aux_maestra->dato);
            }
            aux_maestra=aux_maestra->sig;
        }
        return lmayores;
    }
}

void Graba_lista(lista l){
    FILE *f;
    nodo *aux=NULL;

    if(l.prim==NULL){
        printf("\nLista vacía\n\n");
        return;
    }
    f = fopen("mayores.bin","wb");
    if(f==NULL)                         //no puede abrir el archivo
        printf("\nError al abrir el archivo para grabar\n\n");
    else{
        aux=l.prim;
        while(aux!=NULL){
            fwrite(&aux->dato,sizeof(aux->dato),1,f);
            aux = aux->sig;
        }
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo");
        printf("\nDatos grabados\n\n");
    }
}

void Buscar_elemento(lista l){
    nodo *aux;
    char buscar[15];

    if(l.prim==NULL){
        printf("\nLista vacía\n\n");
        return;
    }
    printf("\nIngrese el nombre a buscar:");
    scanf("%s",buscar);
    aux=l.prim;
    while(aux!=NULL && (strcmp(aux->dato.nombre,buscar)!=0))
        aux=aux->sig;
    if (aux!=NULL){
        printf("\nEncontré el nombre buscado %s\n",buscar);
        if(aux->sig!=NULL){
            printf("El siguiente nombre en la lista es %s\n",aux->sig->dato.nombre);
        }
        else
            printf("No hay dato siguiente para mostrar\n");
        if(aux->ant!=NULL){
            printf("El nombre anterior en la lista es %s\n",aux->ant->dato.nombre);
        }
        else
            printf("No hay dato anterior para mostrar\n");
        printf("\n");
    }            
    else
        printf("\nNo existe el dato\n\n");
    return;
}


int main(){
    int opcion;
    lista lmaestra, lmayores;

    lmaestra.prim=NULL;
    lmaestra.ult=NULL;
    lmayores.prim=NULL;
    lmayores.ult=NULL;

    do{
        printf("1__Insertar edad y nombre\n");                
        printf("2__Genera sublista\n");       
        printf("3__Busca clientes\n");
        printf("4__Guardar sublista\n");
        printf("5__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                lmaestra=Ingresar_personas(lmaestra);
                break;
            case 2:
                lmayores=Sublista(lmaestra);
                Mostrar_lista_directo(lmaestra);
                Mostrar_lista_directo(lmayores);
                break;
            case 3:
                Buscar_elemento(lmaestra);
                break;
            case 4:
                Graba_lista(lmayores);
                break;
            case 5:
                printf("Finalizó programa\n");
                break;
            default:
                printf("Opción inválida\n");
        }
    }while (opcion != 5);

    lmaestra=Destruir_lista_final(lmaestra);
    lmayores=Destruir_lista_final(lmaestra);
    return 0;
}
