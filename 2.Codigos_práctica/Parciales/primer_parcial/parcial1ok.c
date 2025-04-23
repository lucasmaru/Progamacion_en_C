/*
Programacion UNSAM
Resolucion de parcial
Sugerencia: lea todos los puntos y las notas antes de empezar a trabajar.

Un labo de ing. Biomédica usa un archivo binario para almacenar datos de mediciones neuronales de un paciente en estudio. Cada medición está almacenada como una estructura contiendo dos valores en el siguiente orden:
    Identificador de neurona: valor entero positivo
    Nivel de activación: valor real doble precisión entre cero (0%) y 1 (100%)

Se pide hacer un programa que presente un menú con las siguientes opciones, las cuales deben poder operarse en cualquier orden y cantidad de veces sin generar errores de sistema (crashes) ni manejos incorrectos:

1-	Leer el archivo y por cada medición almacenar el identif. de neurona en una lista simple de forma que queden en el mismo orden que en el archivo. En cambio, los niveles de activación se deben almacenar en una segunda lista simple, pero en orden inverso.
2-	Informar cuál es el nivel de activación más cercano a 1.
3-	En la lista de identificadores, intercambiar el primero por el último.
4-	Generar el archivo ingresando las mediciones por teclado (use %lf para el scanf con el double).
5-	Puede usar esta opción para mostrar alguna info útil para usted. No sumará ni restará puntaje.
6-	Salir del programa.

Notas
1)	Se sugiere usar funciones cuando sea conveniente, para simplificar el código.
2)	El código entregado debe estar correctamente indentado y ser prolijo
3)	Si el código no compila, no aprueba el examen.
*/
# include <stdio.h>
# include <stdlib.h>

typedef struct medicion{
    int id;
    double act;
}medicion;

typedef struct nodo_identificador {//Declaro nodo para los identificadores
    int id;
    struct nodo_identificador* sig;
}nodo_identificador;

typedef struct nodo_actividad {//Declaro nodo para la actividad
    double act;
    struct nodo_actividad* sig;
}nodo_actividad;

nodo_identificador* Insertar_FIFO_id(nodo_identificador*l, int dato){//Ingresa elementos a la lista
    nodo_identificador* nuevo=NULL;
    nodo_identificador* aux=NULL;//recorrer la lista 
    nuevo=(nodo_identificador*) malloc (sizeof (nodo_identificador));//reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);//valida la reserva de memoria
    nuevo->id=dato;//Almaceno d en el nuevo nodo
    nuevo->sig =NULL;//Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)//si no hay nodos
        return nuevo;
    aux=l;//pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;//ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;
    }//devuelvo l, porque sigue siendo el primer elemento de la lista

void Mostrar_lista_act(nodo_actividad *l){//Chequeo que guarda la lista de neuronas
    if(l!=NULL){
        printf("Lista de actividad:");
        printf("\n------------------------------------------------\n");
        while(l!=NULL){
            printf("%lf-->",l->act);
            l=l->sig;
        }
        printf("fin de lista");
        printf("\n------------------------------------------------");    
        printf("\n");
    }
    else
        printf("NO HAY ACTIVIDADES PARA MOSTRAR\n");
}

void Mostrar_lista_id(nodo_identificador *l){//Chequeo que guarda la lista de neuronas
    if(l!=NULL){
        printf("Lista de identificadores:");
        printf("\n------------------------------------------------\n");
        while(l!=NULL){
            printf("%d-->",l->id);
            l=l->sig;
        }
        printf("fin de lista");
        printf("\n------------------------------------------------");    
        printf("\n");
    }
    else
        printf("\nNO HAY IDs PARA MOSTRAR\n");
}

nodo_actividad* Insertar_LIFO_act(nodo_actividad *l, double d){//Ingresa elementos a la lista
nodo_actividad *nuevo;
nuevo=(nodo_actividad*) malloc (sizeof (nodo_actividad));
if (nuevo==NULL)
    exit (1);
nuevo->act=d;//Almaceno d en el nuevo nodo
nuevo->sig =l;//Pongo a el sig del nuevo nodo apuntado a l, pues debe ser primero de la lista
return nuevo;//devuelvo nuevo, porque es el nuevo primer elemento de la lista
}

void mejor_act (nodo_actividad* l){
    double mejor;
    nodo_actividad* aux;
    if(l!=NULL){
        aux=l;
        mejor=aux->act;
        while(aux->sig!=NULL){
            if(aux->act >= mejor)
                mejor=aux->act;
            aux=aux->sig;
        }
        printf("\nEL MAYOR NIVEL DE ACTIVACIÓN ES %lf\n",mejor);
    }
    else
        printf("\nNO HAY DATOS PARA COMPARAR\n");
}

nodo_identificador* cambia_orden(nodo_identificador* l){
    nodo_identificador* aux;
    int prim, ult;
    if(l!=NULL&&l->sig!=NULL){//hay dos valores
        prim=l->id;//Almaceno primer dato
        aux=l;
        while(aux->sig!=NULL)
            aux=aux->sig;
        ult=aux->id;
        aux->id=prim;
        l->id=ult;
        return l;
    }
    else if(l!=NULL && l->sig==NULL){
        printf("\nSOLO HAY UN VALOR, NO ES POSIBLE INTERCAMBIAR\n");
        return l;
    }
    else{
        printf("\nNO HAY DATOS\n");
        return l;
    }
}

void genera_arch(){
    int auxciclo=1,auxgraba;
    medicion auxmed;
    FILE* f;
    f=fopen("datos.dat","wb");
    if(f==NULL){
        printf("\nError al abrir el archivo para escritura\n");
        exit(1);
    }
    else{
        while(auxciclo==1){
            printf("\nIngrese id de la neurona(entero positivo): \n");
            scanf("%d",&auxmed.id);
            while(auxmed.id<0){
                printf("\nDato fuera de rango, reingrese: \n");
                scanf("%d",&auxmed.id);
            }
            printf("\nIngrese actividad de la neurona(entre 0 y 1): \n");
            scanf("%lf",&auxmed.act);
            while(auxmed.act<0||auxmed.act>1){
                printf("\nDato fuera de rango, reingrese: \n");
                scanf("%lf",&auxmed.act);
            }
            auxgraba=fwrite(&auxmed,sizeof(auxmed),1,f);
            if(auxgraba==1){
                printf("\nElemento guardado.\n");
                printf("Ingresa otro con 1 o sale con 0: \n");
                scanf("%d",&auxciclo);
                while(auxciclo!=0 && auxciclo!=1){
                    printf("\nDato fuera de rango, reingrese: \n");
                    scanf("%d",&auxciclo);
                }
            }
            else
                printf("\n Error al guardar elemento\n");            
        }
        if (fclose(f) != 0)
            printf("\nError al cerrar");
    }
}

int main(){
    int op,auxlectura=1;
    medicion auxmed;
    FILE* f;
    nodo_actividad* lista_act=NULL;
    nodo_identificador* lista_id=NULL;
    do{
        printf("\n1) Leer el archivo.");
        printf("\n2) Mayor nivel de activación");
        printf("\n3) Intercambiar primer identificador por último");
        printf("\n4) Generar archivo por teclado");
        printf("\n5) Mostra lista de identificadores y nodos");
        printf("\n6) Salir");
        printf("\n--------------------------");
        printf("\nIngrese opcion: ");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
                f=fopen("datos.dat","rb");//Abre el archivo
                if(f==NULL)
                    printf("\nNo se pudo abrir archivo\n");
                else{
                    while(auxlectura==1){
                        auxlectura=fread(&auxmed,sizeof(auxmed),1,f);
                        if(auxlectura==1){
                            lista_id=Insertar_FIFO_id(lista_id,auxmed.id);
                            lista_act=Insertar_LIFO_act(lista_act,auxmed.act);
                        }
                        else
                            printf("\nDATOS LEÍDOS\n");
                    }
                    if (fclose(f) != 0)
                   printf("\nError al cerrar");
                }
                break;
        case 2:
                mejor_act(lista_act);
            break;
        case 3:
                lista_id= cambia_orden(lista_id);
            break;        
        case 4:
            genera_arch();
            break;
        case 5:
                Mostrar_lista_id(lista_id);
                Mostrar_lista_act(lista_act);
            break;
        case 6:
                printf("Finalizo programa");
            break;
        default:printf("\nOpcion incorrecta, reingrese: ");
            break;
        }

    } while (op!=6);

    return 0;
}