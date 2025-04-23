/*La dueña de la pizeria de una ciudad nos pidió un programa de computadora que le permitiera tener un control básico de los 
pedidos, precios y pizzas que se venden en su local, nos aclaró que solo vende 10 tipos de pizza. 
En particular necesita un menú repetitivo que le permita hacer lo siguiente :

1)Cargar los 10 nombres de productos (char 20) y sus precios unitarios (float) contenidos en el archivo preciosproductos.dat.
Aclaración: Usted deberá cargar los datos en una estructura apropiada, la que crea conveniente.
Aclaración sobre el archivo: los datos se guardaron en el archivo en el orden mencionado producto:char[20]->precio:float.

2)Permitir cargar un nuevo pedido a la lista de pedidos, por orden de llegada, con los siguientes datos:
numpedido (int)
numcombo (int del 1 al 10, identifican el tipo de pizza)
cantidad (int)
totalapagar (float)

3)a)Los nombres (char 20) de los 10 tipos de pizza que ofrecen para la venta y su precio unitario (float).
  b)Mostra la lista de pedidos en curso: numpedido, numcombo, cantidad, totalapagar.

4)Permitir ingresar por teclado el nombre de un producto y de encontrarse, permitir actualizar su precio en el vector de 
productos/precios.

5)Recalcular el valor del dato totalapagar de cada pedido que haya en la lista, buscando el nuevo precio cargado luego de ejecutar la
opción del punto 4.

6)Salir del programa*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct producto {//Declaro estrucutura para los productos
    char tipo_pizza [20];
    float precio;
    int num;
}producto;

typedef struct pedido {//Declaro estructura para los pedidos
    int numpedido;
    int numcombo;
    int cantidad;
    float totalapagar;
}pedido;

typedef struct nodo_producto {//Declaro nodo para los productos
    producto prod;
    struct nodo_producto* sig;
}nodo_producto;

typedef struct nodo_pedidos {//Declaro nodo para los pedidos
    pedido ped;
    struct nodo_pedidos* sig;
}nodo_pedidos;

nodo_producto* Insertar_FIFO_producto(nodo_producto *l, producto p){//Ingresa elementos a la lista
    nodo_producto* nuevo;
    nodo_producto* aux;//recorrer la lista 
    nuevo=(nodo_producto*) malloc (sizeof (nodo_producto));//reservo memoria para el nuevo dato
    if (nuevo==NULL)
    exit (1);//valida la reserva de memoria
    nuevo->prod=p;//Almaceno d en el nuevo nodo
    nuevo->sig =NULL;//Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)//si no hay nodos
        return nuevo;
    aux=l;//pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;//ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;}//devuelvo l, porque sigue siendo el primer elemento de la lista

nodo_pedidos* Insertar_FIFO_pedido(nodo_pedidos *l, pedido d){//Ingresa elementos a la lista
    nodo_pedidos* nuevo;
    nodo_pedidos* aux;//recorrer la lista 
    nuevo=(nodo_pedidos*) malloc (sizeof (nodo_pedidos));//reservo memoria para el nuevo dato
    if (nuevo==NULL)
    exit (1);//valida la reserva de memoria
    nuevo->ped=d;//Almaceno d en el nuevo nodo
    nuevo->sig =NULL;//Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)//si no hay nodos
        return nuevo;
    aux=l;//pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;//ahora aux es el último nodo
    aux->sig=nuevo;//guardo el dato en el último nodo
    return l;}//devuelvo l, porque sigue siendo el primer elemento de la lista

nodo_pedidos* Cargar_pedido(nodo_producto* lprod, nodo_pedidos* lped ){//Recibe la lista de precios y pedidos y devuelve act la de pedidos
    int numpedido=1;
    float precio;
    int aux1=1;
    pedido pp;

    if(lprod!=NULL){
        while(aux1==1){
            printf("\nAsigne un numero al pedido: ");
            scanf("%d",&pp.numpedido);   
            printf("\n Ingrese tipo de pizza solicitada(1-10): ");
            scanf("%d",&pp.numcombo);
            while(pp.numcombo<=0 || pp.numcombo>10){//Valido el ingreso
                printf("\nReingrese el dato, deber ser un entero entre 1 y 10: ");
                scanf("%d",&pp.numcombo);
            }
            printf("\nIngrese cantidad solicitada: ");
            scanf("%d",&pp.cantidad);
            printf("\nPara realizar otro pedido presione 1 para terminar presione 0: ");//Varios nodos pueden ser del mismo pedido
            scanf("%d",&aux1);//Si es cero sale del while
            while(lprod->prod.num !=pp.numcombo)//Busco el precio
                lprod=lprod->sig;
            pp.totalapagar=lprod->prod.precio*pp.cantidad;
            lped=Insertar_FIFO_pedido(lped,pp);//Paso el nodo a la lista
        }
        return lped;
    }
    else
        printf("\nNo hay datos de precios\n");
}
    
void Mostrar_listaproductos(nodo_producto *l){//Chequeo que guarda la lista de neuronas
    if(l!=NULL){
        printf("Lista de productos:");
        printf("\n------------------------------------------------");
        while(l!=NULL){
            printf("\n%2d-->",l->prod.num);
            printf("%2s",l->prod.tipo_pizza);
            printf("....................");
            printf("$%0.1f",l->prod.precio);
            l=l->sig;
        }
        printf("\n------------------------------------------------");    
        printf("\n");
    }
    else
        printf("No hay datos");
}


void Mostrar_listapedidos(nodo_pedidos *l){//Chequeo que guarda la lista de neuronas
    if(l!=NULL){
        printf("Lista de pedidos:");
        printf("\n------------------------------------------------");
        while(l!=NULL){
            printf("\nPedido Nro%d-->",l->ped.numpedido);
            printf("Tipo de pizza:%d -->",l->ped.numcombo);
            printf("Cantidad: %d",l->ped.cantidad);
            printf("  $%0.2f",l->ped.totalapagar);
            l=l->sig;
        }
        printf("\n------------------------------------------------");
        printf("\n");
    }
    else
        printf("No hay datos para mostrar");
}

nodo_producto* Modfica(nodo_producto* l){
    float nuevoprecio;
    char acambiar[20];
    int auxcompara;
    nodo_producto* aux;
    aux=l;
    if (aux!=NULL){
        printf("Ingrese el nombre del producto: \n");
        scanf("%s",acambiar);
        while(auxcompara!=0 &&  aux->sig!=NULL){
            auxcompara=strcmp(acambiar,aux->prod.tipo_pizza);
            if(auxcompara!=0)
                aux=aux->sig;
        }
        if(auxcompara!=0){//Salio del while porque llegó al final de la lista
            printf("El registro ingresado no coincide con ningun tipo de producto\n");
            return l;
        }
        else if (auxcompara==0){
            printf("\nREGISTRO ENCONTRADO, ingrese nuevo precio: ");
            scanf("%f",&nuevoprecio);
            aux->prod.precio=nuevoprecio;
            return l;
        }
    }
    else{
        printf("No hay datos para modificar\n");
        return l;
    }
}

nodo_pedidos* Actualiza(nodo_pedidos* lped,nodo_producto* lprod){
    float nuevoprecio;
    nodo_pedidos* auxped;
    nodo_producto* auxprod;
    if(lped!=NULL){
        auxped=lped;
        auxprod=lprod;
        while(auxped->sig!=NULL){
            while(auxped->ped.numcombo != auxprod->prod.num )
                auxprod=auxprod->sig;
            nuevoprecio = auxped->ped.cantidad * auxprod->prod.precio;
            auxped->ped.totalapagar=nuevoprecio;
            auxped=auxped->sig;
        }
        return lped;
    }
    else{
        printf("\nNo hay datos para actualizar\n");
        return lped;
    }
}

int main (){
    char auxtipo_pizza[20];
    float auxprecio;
    int op,op2,i,lecchar,lecfloat,numprod=1;
    producto auxproducto;
    nodo_producto* lista_productos=NULL;
    nodo_pedidos* lista_pedidos=NULL;
    FILE* f;

    do{
        printf("\n1) Cargar los datos de productos desde el archivo.");
        printf("\n2) Cargar pedido");
        printf("\n3) Información sobre precios y lista de pedidos");
        printf("\n4) Modificar el precio de un producto");
        printf("\n5) Actualizar precios de pedidos en curso");
        printf("\n6) Salir");
        printf("\n--------------------------");
        printf("\nIngrese opcion: ");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            if(lista_productos==NULL){
                f=fopen("preciosproductos.dat","rw");//Abre el archivo
                if(f==NULL)
                    printf("No se pudo abrir archivo.");
                else{
                    for(i=0;i<10;i++){
                        lecchar=fread(auxtipo_pizza,sizeof(auxtipo_pizza),1,f);//Si pudo abrirlo lee un dato
                        if (lecchar!=1){
                            printf("Error en la lectura");
                            exit(1);
                        }
                        else{
                            lecfloat=fread(&auxprecio,sizeof(auxprecio),1,f);
                            if (lecfloat!=1){
                            printf("Error en la lectura");
                            exit(2);
                            }
                            else{
                                strcpy(auxproducto.tipo_pizza,auxtipo_pizza);
                                auxproducto.precio=auxprecio;
                                auxproducto.num=numprod;
                                lista_productos=Insertar_FIFO_producto(lista_productos,auxproducto);
                                numprod++;
                            }
                        }
                    }
                    printf("\nPRODUCTOS LEIDOS Y ALMACENADOS\n");
                }
            }else printf("\nLos datos ya fueron cargados\n");
            break;
        case 2:
            lista_pedidos=Cargar_pedido(lista_productos,lista_pedidos);
            
            break;
        case 3:
            printf("\nMotrar lista de productos 1\nMostras lista de pedidos 2\n");
            scanf("%d",&op2);
            if(op2==1)
                Mostrar_listaproductos(lista_productos);
            else if(op2==2)
                Mostrar_listapedidos(lista_pedidos);
            else
                printf("Opción no valida");
            break;
            
        case 4:
            lista_productos=Modfica(lista_productos);            
            break;
        case 5:
            lista_pedidos=Actualiza(lista_pedidos,lista_productos);
            printf("\nLa opción 5 la tenfo que seguir arreglanndo!!!!!!!!! NO ANDA!!!\n");
            break;
        case 6:
            printf("Finalizo programa");
            break;
        default:printf("\nOpcion incorrecta, reingrese: ");
            break;
        }

    } while (op!=6);
}