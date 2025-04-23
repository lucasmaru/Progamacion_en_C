/*Primer parcial*/
# include <stdio.h>
# include <stdlib.h>

typedef struct nodoneu {//Declaro el tipo de esructura nodo
    int neurona;
    struct nodoneu *sig;
}nodoneu;

typedef struct nodoact {//Declaro el tipo de esructura nodo
    double actividad;
    struct nodoact *sig;
}nodoact;

typedef struct doblelista {//Declaro el tipo de esructura nodo
    nodoneu *l1;
    nodoact *l2;
}doblelista;



nodoact* Insertar_LIFOACT(nodoact *l, double d){//Ingresa elementos a la lista
    nodoact *nuevo;
    nuevo=(nodoact*) malloc (sizeof (nodoact));
    if (nuevo==NULL)
    exit (1);
    //nuevo=l;//nuevo a punta al mismo espacio que l, que es el primer elemento de la lista
    nuevo->actividad=d;//Almaceno d en el nuevo nodo
    nuevo->sig =l;//Pongo a el sig del nuevo nodo apuntado a l, pues debe ser primero de la lista
    return nuevo;//devuelvo nuevo, porque es el nuevo primer elemento de la lista
}

nodoneu* Insertar_FIFONEU(nodoneu *l, int d){//Ingresa elementos a la lista
    nodoneu* nuevo;
    nodoneu* aux;//recorrer la lista 
    nuevo=(nodoneu*) malloc (sizeof (nodoneu));//reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (2);//valida la reserva de memoria
    nuevo->neurona=d;//Almaceno d en el nuevo nodo
    nuevo->sig =NULL;//Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)//si no hay nodos
        return nuevo;
    aux=l;//pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;//ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;}//devuelvo l, porque sigue siendo el primer elemento de la lista



/*nodo* leer_archivo(nodo *l){
    FILE *f;
    i=0;//cantidad de datos neurona leidos
    int *auxneu;//almacena datos para la lista de neuronas
    double *auxact;//almacena datos para la lista de actividad
    int i=0;//cuenta los datos que lee
    f=fopen("archivo.dat","rb");//Abro archivo
    if (f==NULL){
        printf("Error al abrir el archivo \n");//Valido la apertura
        exit(1);
    }
    else{//Si puede abrir leo
        auxneu=(int*)malloc(sizeof(int));//Reservo memoria para almacenar un dato entero
        while(fread(&auxneu[i],sizeof(int),1,f)==1){//Mientras pueda leer un dato int sigue en el while
            printf("Dato:%d \n",auxneu[i]);//Cheq1 que esta leyendo
            i++;//almaceno la cantidad de archivos que lee y lleno el vector
            auxneu=(int*)realloc(auxneu,sizeof(int)*(i+1));
        }
        printf("Se leyeron %d datos \n",i);
        auxact=(double*)malloc(sizeof(double));//Reservo memoria para un dato double
        if(fclose(f)!=0){
            printf("Error al cerrar el archivo");
            exit (2);
        }
        return l;
    }
}*/

void Mostrar_lista1(nodoneu *l){//Chequeo que guarda la lista de neuronas
    printf("Lista:");
    while(l!=NULL){
        printf("-->%d",l->neurona);
        l=l->sig;
    }
    printf("\n");
}
void Mostrar_lista2(nodoact *l){//Chequeo que guarda la lista de actividad
    printf("Lista:");
    while(l!=NULL){
        printf("-->%lf",l->actividad);
        l=l->sig;
    }
    printf("\n");
}

doblelista* Pedir_datos(nodoneu *lneu,nodoact *lact, doblelista *dos_listas){
    int tempneu;
    double tempact; 
    printf("Ingrese el numero de neurona (sale con 0):\n");
    scanf("%d",&tempneu);
    if (tempneu!=0){//Si !=0 quiere almacenar una dato de neurona
        while(tempneu!=0){
            lneu=Insertar_FIFONEU(lneu,tempneu);
            printf("Ingrese la actividad neuronal (entre 0 y 1):\n");
            scanf("%lf",&tempact);
            while (tempact>1||tempact<0){
                printf("Valor fuera de rango");
                printf("Ingrese la actividad neuronal (entre 0 y 1):\n");
                scanf("%lf",&tempact);
            }
            lact=Insertar_LIFOACT(lact,tempact);
            dos_listas=(doblelista*)realloc(dos_listas,sizeof(doblelista));//no sale de acá
            dos_listas->l1=lneu;
            dos_listas->l2=lact;
            printf("Ingrese el numero de neurona (sale con 0):\n");
            scanf("%d",&tempneu);
        }
    }
    else 
        printf("Salio\n");
    return dos_listas;
}

void Guardar(doblelista *l){//Recibe las dos listas y las guarda
    FILE *arch;
    int n=0;
    arch=fopen("datos.dat","wb");
    if (arch==NULL){
        printf("Error al abrir el archivo para escritura");
        exit(4);
    }
    else{
        while(fwrite(&(l->l1->neurona),sizeof(l->l1->neurona),1,arch) == 1){
            //printf("guardo: %d\n", l->l1->neurona);//cheq
            l->l1=l->l1->sig;
        }
        while(fwrite(&(l->l2->actividad),sizeof(l->l2->actividad),1,arch)==1){
            //printf("guardo: %lf\n", l->l2->actividad);//cheq
            l->l2=l->l2->sig;
        }
        if(fclose(arch)!=0){
            printf("Error al cerrar el archivo");
            exit(5);
        }
    }
}

void Mejor_act(nodoact *l){
    double mejor=0;
    if (l==NULL)//Sin datos
        printf("Lista vacia\n");
    else if(l!=NULL&&l->sig==NULL){//Solo hay un dato
        mejor=l->actividad;
        printf("El valor de mayor actividad es: %.2lf \n");
    }
    else{
        while(l->sig!=NULL){//Si entro acá hay mas de 1 dato
            if(mejor<=l->actividad)
                mejor=l->actividad;
            l=l->sig;
        }
    printf("El valor de mayor actividad es: %.2lf \n");
    }
}
    
int main (){
    int opcion;
    nodoneu *listaneu=NULL;
    nodoact *listaact=NULL;
    doblelista *doblel=NULL;
    do{
        printf("1_Leer archivo y almacenar archivo\n");
        printf("2_Informar nivel de activacion mas cercano a 1 \n");
        printf("3_Intercambia 1er identificador neuronal por el ultimo\n");
        printf("4_Genera archivo ingresando datos por teclado\n");
        printf("5_Opción a definir \n");
        printf("6_Salir\n");
        printf("Seleccione una opcion del menu ");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1: ;
            break;
        case 2:
            Mostrar_lista2(doblel->l2);//Cheq, que hay en la lista
            Mejor_act(doblel->l2);
            break;
        case 3: ;
            break;
        case 4:
            doblel=Pedir_datos(listaneu,listaact,doblel);
            //Mostrar_lista1(doblel->l1);
            Mostrar_lista2(doblel->l2);
            Guardar(doblel);
            break;
        case 5: ;
            break;
        case 6:  ;
            break;        
        default:printf("Opcion incorrecta\n");
            break;
        }

    } while (opcion!=6);
    return 0;
}