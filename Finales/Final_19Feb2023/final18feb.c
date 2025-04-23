#include <stdio.h>
#include <stdlib.h>

//LISTA SIMPLE
typedef struct nodo{
  unsigned char dato;
  int pos;
  struct nodo *sig;
}nodo;


//LIFO --> LAST IN FIRST OUT, EL ULTIMO QUE ENTRA ES EL ULTIMO QUE SALE
//O SEA ESTAMOS INSERTANDO NODOS AL PRINCIPIO
//COMO SE VA A LEER DESDE EL REGISTRO 63 AL 0 DEBIDO A QUE ASI ESTA GRABADO EL ARCHIVO
//CON LIFO SE VAN A INSERTAR LOS ULTIMOS DATOS PRIMEROS, Y JUSTO EL ULTIMO ES EL REG 0X00 QUE VA A IR PRIMERO EN LA LISTA
nodo *insertar_lifo(nodo *l, unsigned char d, int pos){ //SE RECIBE EL INICIO DEL NODO, EL DATO DE 1 BYTE Y LA POSICION
    nodo *nuevo; //DECLARO UN NODO NUEVO PARA GUARDAR LOS DATOS

    nuevo = (nodo *) malloc(sizeof(nodo)); //GENERO ESPACIO EN MEMORIA
    nuevo->dato = d; //EN EL CAMPO REG DEL NODO SE ASIGNA EL DATO
    nuevo->pos = pos; //EN EL CAMPO POS SE ASIGNA LA POS
    nuevo->sig = l; // EL SIG DEL NUEVO NODO VA A APUNTAR AL QUE ERA EL PRIMER NODO


    return nuevo; //como es LIFO, tengo que retornar el puntero nuevo que es "nuevo" primer valor
}


nodo *leer_archivo (){
  int r, i=63,j=0;
  unsigned char datoaux;
  nodo *l=NULL;
  FILE *f;

  f = fopen ("datos.bin" , "rb"); //ABRIMOS EL ARCHIVO BINARIO CON RB
  if (f==NULL){
    printf ("\nNo se puedo abrir el archivo");
    exit (1);
  }

  //SI SE ABRIO:
  else{
     r = fread(&datoaux, sizeof(unsigned char), 1, f); //LEO DESDE EL ARCHIVO F 1 ELEMENTO DE TAMAÑO UNSIGNED CHAR Q ES 1 BYTE Y LO GUARDO EN DATOAUX

       while (r!=0){ //MIENTRAS SEA LEA UN DATO, O SEA r DISTINTO DE 0:

          if(j>32 && i>= 0){ //SI J ES MAYOR A 32 (O SEA J EMPIEZA A LLENAR LA LISTA EN 32 Y QUE I SEA MAYOR A 0 SIENDO QUE VA A IR DESCENDIENDO DE 63 A 0

            l = insertar_lifo(l, datoaux, i); //SE INSERTA LIFO, O SEA EL ULTIMO EN ENTRAR ES EL PRIMERO EN EL NODO.
            i--; //EL PRIMER VALOR ES 63 .... DISMINUYE HASTA 0
            //O SEA EN LA PRIMERA VUELTA QUEDA QUE EL NODO TIENE POSICION 63... PERO COMO ES LIFO, AL PRINCPIO QUEDA EL ULTIMO QUE SE RECIBE QUE ES POS 0
            }

          j++;
          r = fread(&datoaux,sizeof(unsigned char),1,f);
        }

      }


  if (fclose(f)!=0){
    printf ("\nNo se pudo cerrar el archivo!!!");
    exit (2);
  }
  return l;
}



void mostrar_registros(nodo *l){ // Muestra REGS 0 a 63
	nodo *aux=l;
    int i;


	printf("\n\nRegistros:\n---------\n");

	while(aux != NULL){

        printf("\n\t 0d%02d - 0x%02X", aux->pos, aux->dato);
        //printf("\n\t -----------\n");
        aux=aux->sig; //para avanzar sin cambiar el puntero l.
    }
}


// Si la lista ya existe porque ya se había ejecutado esta opción, se
// deberá vaciar previamente --> lo hago con destruir_nodo
nodo *destruir_lista(nodo *l){
    nodo *aux; //sin un auxiliar se pierde la referencia

    while(l != NULL){
        aux = l; // guardo a lo que apunta l
        l = l->sig; //avanzo la lista sin perder ref
        free(aux); //borro nodo
    }
    printf("\n*........Lista destruida.........*\n\n");
    return NULL; //CLAVE
}


//MOSTRAR LOS DATOS QUE TENGAN UN 1 EN EL SEGUNDO BIT MAS SIGNIFICATIVO Y UN 0 EN EL MENOS SIGNIFICATIVO
void mostrar(nodo *l){
	nodo *aux=l;
    int k=0;

	printf("\nLISTA DE DATOS CON UN 1 EN EL 2DO MAS SIGNIFICATIVO \n Y UN 0 EN EL MENOS SIGNIFICATIVO\n---------\n");
    printf("Posicion  -  Valor (Hexa) - Valor (Decimal)");

	while(aux!=NULL){ //MIENTRAS LA LISTA NO ESTE NULA:
        if(aux->dato & 0x40 && ((aux->dato & 0x01) != 1)){ //MASCARA DEL REGISTRO CON 0100 0000 Y 0000 0001 --> BIT MAS Y MENOS SIGNIFICATIVO
		   //IMPRIMO LOS DATOS DEL NODO:
		    printf("\n0d%02d \t\t  0x%02X \t\t  0d%02d",aux->pos, aux->dato, aux->dato);
            k++;
        }


        aux=aux->sig; //para avanzar sin cambiar el puntero l.
	}
    printf("\n --> %d es la cantidad de registros que cumplen la condicion\n", k);
}



int main () {

    nodo *lista;
    unsigned char d, aux;
    int op, res, n=0;
    FILE *f;

    lista = NULL;

    do {
        printf ("\n-------------------------------------------------------------------------------");
        printf ("\n1)   Mostar lista RTC:");
        printf ("\n2)   Mostrar valores de la lista que tengan un 1 en el 2do bit mas significativo \n   y un 0 en el menos significativo:");
        printf ("\n3)   Salir:");
        printf ("\n-------------------------------------------------------------------------------");
        printf ("\nIngrese opcion: ");

        scanf ("%d", &op);

        switch (op) {
            case 1: //Opcion 1: Muestra los registros
                lista = NULL;
                lista = leer_archivo(lista);
                mostrar_registros(lista);
                destruir_lista(lista);

            break;

        case 2: //Opcion 2:
                lista = NULL;
                lista = leer_archivo(lista);
                mostrar(lista);
                destruir_lista(lista);
            break;

        case 3: //Finalizar Programa
            printf ("Fin del programa!!!\n\n");
            break;

        default: //Otras opciones
            printf ("Opcion invalida, ingrese nuevamente!\n");
        } //Fin switch (opc)
    } while (op != 3); //Fin de do while

    //destruir_lista(lista);

    return 0;
}

//RTA:
//la señal de clock sirve para sincronizar todos los componentes

//La diferencia entre microcontrolador y microprocesador es que el primero  es un chip que integra tanto al microprocesador como a la memoria y los
//periféricos. El microprocesador va a ser el que permita ejecutar programas, o sea el software mediante la realizacion de operaciones logicas y aritmeticas
