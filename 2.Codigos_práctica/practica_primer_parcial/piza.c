/*
Prog 2022_1c_parcial_1
Escriba un programa en C para resolver el enunciado descrito a continuación:

La dueña de una pizzería de la ciudad nos pidió un programa de computadora para tener un control básico de los pedidos, precios y pizzas que se venden en su local. Nos aclaró que vende solamente 10 variedades de pizzas.

En particular, lo que necesita es un programa que le permita, mediante un menú repetitivo de opciones, hacer lo siguiente:
1.	Cargar los 10 nombres de productos (char 20) y su precios unitarios (float), contenidos en el archivo "precioproductos.dat". 
Aclaración: Usted deberá cargarlos en una estructura de datos apropiada, la que usted crea conveniente. 
Aclaración sobre el archivo: Los datos se guardaron en el archivo en el orden mencionado: producto: char [20], precio: float.
2.	Permitir cargar un nuevo pedido a la lista de pedidos, por orden de llegada, con los siguientes datos:
o	numpedido (valor entero)
o	numcombo (valor entero, del 1 al 10) -> los números del 1 al 10 identificarán los distintos tipos de pizzas.
o	cantidad (valor entero)
o	totalapagar (valor decimal, calculado a partir de los precios que tendrá la lista o vector de productos/precios)
3.	Mostrar:
a) Los nombres (char 20) de los 10 tipos de pizzas que ofrecen para la venta y su precio unitario (float).
b) Mostrar la lista de pedidos en curso: numpedido, numcombo, cantidad, totalapagar.
4.	Permitir ingresar por teclado el nombre de un producto y de encontrarse, permitir actualizar su precio en el vector de productos/precios.
5.	Recalcular el valor del dato totalapagar de cada pedido que haya en la lista, buscando el nuevo precio cargado luego de ejecutar la opción del punto 4.
6.	Salir del programa.

•	El código deberá ser correcto y deberá compilar sin advertencias. De lo contrario, probablemente no se corrija. 
•	El código fuente deberá estar correctamente indentado.
•	Para el manejo del archivo, deberá hacer las validaciones necesarias para asegurar que no hubo errores.
*//*
Prog 2022_1c_parcial_1
Escriba un programa en C para resolver el enunciado descrito a continuación:

La dueña de una pizzería de la ciudad nos pidió un programa de computadora para tener un control básico de los pedidos, precios y pizzas que se venden en su local. Nos aclaró que vende solamente 10 variedades de pizzas.

En particular, lo que necesita es un programa que le permita, mediante un menú repetitivo de opciones, hacer lo siguiente:
1.	Cargar los 10 nombres de productos (char 20) y su precios unitarios (float), contenidos en el archivo "precioproductos.dat". 
Aclaración: Usted deberá cargarlos en una estructura de datos apropiada, la que usted crea conveniente. 
Aclaración sobre el archivo: Los datos se guardaron en el archivo en el orden mencionado: producto: char [20], precio: float.
2.	Permitir cargar un nuevo pedido a la lista de pedidos, por orden de llegada, con los siguientes datos:
o	numpedido (valor entero)
o	numcombo (valor entero, del 1 al 10) -> los números del 1 al 10 identificarán los distintos tipos de pizzas.
o	cantidad (valor entero)
o	totalapagar (valor decimal, calculado a partir de los precios que tendrá la lista o vector de productos/precios)
3.	Mostrar:
a) Los nombres (char 20) de los 10 tipos de pizzas que ofrecen para la venta y su precio unitario (float).
b) Mostrar la lista de pedidos en curso: numpedido, numcombo, cantidad, totalapagar.
4.	Permitir ingresar por teclado el nombre de un producto y de encontrarse, permitir actualizar su precio en el vector de productos/precios.
5.	Recalcular el valor del dato totalapagar de cada pedido que haya en la lista, buscando el nuevo precio cargado luego de ejecutar la opción del punto 4.
6.	Salir del programa.

•	El código deberá ser correcto y deberá compilar sin advertencias. De lo contrario, probablemente no se corrija. 
•	El código fuente deberá estar correctamente indentado.
•	Para el manejo del archivo, deberá hacer las validaciones necesarias para asegurar que no hubo errores.
*/
/*Practica 1er parcial pizerria*/
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct precios{                 //estructura para leer datos del archivo
    char alias[20];
    float precio;
}precios;

typedef struct pedido{                 //estructura para almacenar pedidos
    int num_pedido;
    int num_combo;
    int cantidad;
    float total_a_pagar;
}pedido;

typedef struct nodo{                   //nodo para la lista de pedidos
    pedido dato; 
    struct nodo* sig; 
}nodo;

nodo* Insertar_FIFO_pedido(nodo* l, pedido d){      //Ingresa elementos a la lista
    nodo* nuevo;
    nodo* aux;                                      //recorrer la lista 
    nuevo=(nodo*) malloc (sizeof (nodo));           //reservo memoria para el nuevo dato
    if (nuevo==NULL)
        exit (1);                                   //valida la reserva de memoria
    nuevo->dato=d;                                  //Almaceno d en el nuevo nodo
    nuevo->sig =NULL;                               //Pongo a el sig del nuevo nodo apuntado a NULL, pues debe ser el último de la lista
    if(l==NULL)                                     //si no hay nodos
        return nuevo;
    aux=l;                                          //pongo a aux apuntado al mimo espacio de memoria que l
    while(aux->sig!=NULL)
        aux=aux->sig;                               //ahora aux es el último nodo
    aux->sig=nuevo;                                 //guardo el dato en el último nodo
    return l;                                       //devuelvo l, porque sigue siendo el primer elemento de la lista
}

nodo* Destruir_lista(nodo* l){
    nodo* aux;
    if (l==NULL)
        printf("\nNo hay lista para destruir\n");
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

void Lee_archivo(precios vec[]){
    /*¿Porque la función no retorna el valor leido al main? Por que si quisiera hacerlo no puedo retornar
    todo un vector en el return. Para solucionar eso LE PASO EL ARGUMENTO POR REFERENCIA, es decir la
    función recibe del main una copia de vector_precios[] que es vec[] pero tanto vec[] como 
    vector_precios[] son punteros que almacenan la dirección de memoria a donde van los datos de los 
    precios, es decir a la memoria que reservó el main cuando lo declaré.
    Por eso en el primer argumento del fread cuando le digo que 
    almacene lo leido en vec, le estoy dando la dirección de memoria donde se almacenan los datos de los
    precios en memoria. */
    FILE* f;
    int n=0;
    
    f = fopen("preciosproductos.dat","rb");
    if(f==NULL){                        
        printf("\nError al abrir el archivo\n\n");
        return;
    } //Si no entró en el if de arriba abrió el archivo
    n=fread(vec,sizeof(vec[0]),10,f);
    if (n!=10){
        printf("\nError al leer el archivo\n\n");
        return;
    }//Si no entró al if de arriba leyó bien el archivo
    if(fclose(f)!=0){
        printf("\nError al cerrar el archivo\n\n");
        return;
    }//Si no entró al if de arriba cerró bien el archivo
    printf("\nArchivo leido correctamente\n\n");//Informo que todo salio bien
}

void Mostrar_lista_pedidos(nodo* l){
    if(l==NULL)
        printf("\nNo hay pedidos para despachar\n\n");
    else{
        printf("Lista:\n");
        while(l!=NULL){
            printf(" numpedido-->%d| ",l->dato.num_pedido);
            printf("numcombo-->%d| ",l->dato.num_combo);
            printf("cantidad-->%d| ",l->dato.cantidad);
            printf("totalapagar-->%8.2f|\n ",l->dato.total_a_pagar);
            l=l->sig;
        }
    }
}

nodo* Nuevo_pedido(nodo* l,precios vec[]){
    int numcombo,cant,numpedido=0;
    pedido p;
    if(strcmp(vec[0].alias,"Muza")!=0){
        printf("\nPrimero debe cargar la lista de precios\n\n");
        return l;
    }
    printf("\nNúmero de pedido:");
    scanf("%d",&p.num_pedido);
    printf("\nNúmero de combo(entero del 1 al 10):");
    scanf("%d",&p.num_combo);
    if (p.num_combo<0 || p.num_combo>10){
        printf("Nro de combo fuera de rango\n\n");
        return l;
    }
    printf("Cantidad:");
    scanf("%d",&p.cantidad);
    p.total_a_pagar = vec[p.num_combo-1].precio * p.cantidad;
    l = Insertar_FIFO_pedido(l,p);
    printf("Pedido agregado\n\n");
    return l ;
}

void Actualiza (precios vec[]){
    char str_a_buscar [20];
    int i;

    if(strcmp(vec[0].alias,"Muza")!=0){
        printf("\nPrimero debe cargar la lista de precios\n\n");
        return;
    }
    printf("\nIngrese la variedad a actualizar:");
    scanf("%s",str_a_buscar);
    for (i=0;i<10;i++){
        if(strcmp(vec[i].alias,str_a_buscar)==0){
            printf("\nVariedad encontrada, ingrese nuevo precio:");
            scanf("%f",&vec[i].precio);
            printf("\nPrecio actualizado\n\n");
            return;
        } 
    }
    printf("\nVariedad no encontrada\n\n");
    return;     
}

nodo* Recalcular(nodo* l, precios vec[]){
    nodo* aux;

    if(l==NULL){
        printf("\nNo hay pedidos para actualizar\n\n");
        return l;
    }
    if(l->sig==NULL){
        l->dato.total_a_pagar = vec[l->dato.num_combo-1].precio * l->dato.cantidad;
        printf("\nSe actualizó la lista de pedidos\n\n");        
        return l;
    }
    aux=l;
    while(aux->sig!=NULL){
        aux->dato.total_a_pagar= vec[aux->dato.num_combo-1].precio *aux->dato.cantidad;
        aux=aux->sig;
    }
    printf("\nSe actualizó la lista de pedidos\n\n");
    return l;
}

int main (){
    int opcion;
    nodo* l_pedido=NULL;
    precios precios[10];
    int i;    
    do{
        printf("1__Cargar datos del archivo\n");                
        printf("2__Nuevo pedido\n");       
        printf("3__Mostrar listas\n");
        printf("4__Actualizar precio\n");
        printf("5__Recalcular precio de los pedidos\n");
        printf("6__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                Lee_archivo(precios);
                break;
            case 2:
                l_pedido = Nuevo_pedido(l_pedido,precios);
                break;
            case 3:
                printf("\nPEDIDOS\n");
                Mostrar_lista_pedidos(l_pedido);
                printf("LISTA DE PRECIOS\n");
                for(i=0;i<10;i++){
                    printf("%-16s--->",precios[i].alias);
                    printf("Precio: %8.2f\n",precios[i].precio);
                }
                printf("\n");                
                break;
            case 4:
                Actualiza(precios);
                break;
            case 5:
                Recalcular(l_pedido,precios);
                break;
            case 6:
                printf("Salir del programa\n");
                break;
            default:
                printf("Opción inválida");             
        }
    }while (opcion != 6);

    l_pedido = Destruir_lista(l_pedido);

    return 0;
}