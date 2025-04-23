/**/

# include <stdio.h>
# include <stdlib.h>

typedef struct turno{//Declaro estructura para los nodos
    char nombre[10];
    int numero;
}turno;

typedef struct nodo_turno {//Declaro nodo para los turnos
    turno tur;
    struct nodo_turno* sig;
}nodo_turno;

nodo_turno* Insertar_FIFO_turno(nodo_turno*l, turno dato){//Ingresa elementos a la lista
    nodo_turno* nuevo=NULL;
    nodo_turno* aux=NULL;//recorrer la lista 
    nuevo=(nodo_turno*) realloc (nuevo,sizeof (nodo_turno));//reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);//valida la reserva de memoria
    nuevo->tur=dato;//Almaceno d en el nuevo nodo
    nuevo->sig =NULL;//Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)//si no hay nodos
        return nuevo;
    aux=l;//pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;//ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;
    }//devuelvo l, porque sigue siendo el primer elemento de la lista

nodo_turno* Carga_turno(nodo_turno* l){
    turno turno;
    nodo_turno* aux=NULL;//Recorre el nodo
    int repetido=1,coincidencia;
    while(repetido==1){
        coincidencia=0;
        printf("\nIngrese numero de tres dígitos: \n");
        scanf("%d",&turno.numero);
        aux=l;
        while(aux!=NULL){
            if(aux->tur.numero ==turno.numero)
                coincidencia=1;//flag
            aux=aux->sig;
        }
        //printf("coincidencia=%d",coincidencia);//cheq
        if(coincidencia==1)//hubo coincidencia vuelvo entrea en linea 41
            printf("\nNumero %d ya está en la fila, ingrese otro \n",turno.numero);  

        if(coincidencia==0){//No hubo coincidencia, completo datos y pido siguiente turno
            printf("\nIngrese nombre: \n");
            scanf("%s",turno.nombre);
            l=Insertar_FIFO_turno(l,turno);
            repetido=0;
            return l;
        }
    }
}
        

void Mostrar_lista(nodo_turno* l){//Chequeo que guarda la lista de neuronas
    if(l!=NULL){
        printf("Lista de turnos:");
        printf("\n------------------------------------------------\n");
        while(l!=NULL){
            printf("%s-%d-->",l->tur.nombre,l->tur.numero);
            l=l->sig;
        }
        printf("NULL");
        printf("\n------------------------------------------------");    
        printf("\n");
    }
    else
        printf("NO HAY TURNOS PARA MOSTRAR\n");
}

void Guardar (nodo_turno* l){
    FILE* f;
    int auxnombre=0, auxnum=0;
    nodo_turno* aux_turno=NULL;
    
    if(l!=NULL){
        f=fopen("fila.dat","wb");
        aux_turno=l;
        printf("Recibi lista\n");//cheq
        if(f==NULL){
            printf("\nError al abrir el archivo para escritura\n");
            exit(1);
        }
        else{
            auxnombre=fwrite(aux_turno->tur.nombre,sizeof(char[10]),1,f);
            auxnum=fwrite(&aux_turno->tur.numero,sizeof(int),1,f);
            while(auxnombre==1 && auxnum==1 && aux_turno!=NULL){
                aux_turno=aux_turno->sig;
                auxnombre=fwrite(aux_turno->tur.nombre,sizeof(char[10]),1,f);
                auxnum=fwrite(&aux_turno->tur.numero,sizeof(int),1,f);
                printf("Guarde 2\n");//cheq
            }
            printf("\nArchivo guardado\n");
            if (fclose(f) != 0)
                printf("\nError al cerrar\n");        
        }
    }
    else{
        printf("\nNo hay datos para generar archivo\n");
    }
}

void Mi_lugar(nodo_turno* l){
    nodo_turno* aux;
    int num, existe=0,i=0;

    if(l==NULL)
        printf("\nNo hay datos para mostrar\n");
    else{
        aux=l;
        printf("\nIngrese en numero a consultar: \n");
        scanf("%d",&num);
        while(aux!=NULL){
            if(aux->tur.numero ==num)
                existe=1;//flag
            aux=aux->sig;
        }
        if(existe==1){
            aux=l;
            while(aux!=NULL && aux->tur.numero!=num){
                i++;
                aux=aux->sig;            
            }
            printf("\nTiene %d turnos delante\n",i);
        }
        else
            printf("\nEl numero ingresado no está en la lista\n");
    }
}

int main(){
    int op;
    nodo_turno* lista=NULL;
    do{
        printf("\n1)Cargar nuevo turno ");
        printf("\n2)Atender turno ");
        printf("\n3)Mi lugar en la lista ");
        printf("\n4)Mostrar fila ");
        printf("\n5)Guardar lista ");
        printf("\n6) Salir");
        printf("\n--------------------------");
        printf("\nIngrese opcion: ");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
                lista=Carga_turno(lista);//Funcion carga
                Mostrar_lista(lista);
            break;
        case 2:
            
            break;
        case 3:
                Mi_lugar(lista);
            break;
            
        case 4:
                Mostrar_lista(lista);
            break;
        case 5:
                Guardar(lista);
            break;
        case 6:
            printf("Finalizo programa");
            break;
        default:printf("\nOpcion incorrecta, reingrese: ");
            break;
        }

    } while (op!=6);
}
