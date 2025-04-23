#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    unsigned char reg;
    struct nodo *sig;
}nodo;

nodo *insertar_fifo(nodo *l, unsigned char d){
    nodo *nuevo, *aux;
   
    nuevo = (nodo *) malloc(sizeof(nodo));
    nuevo->reg   = d;

    nuevo->sig = NULL; // PONER A NULL
   
    if(l==NULL) return nuevo;
   
    aux = l; // ESTA LÍNEA ES CLAVE
    while(aux->sig != NULL)
        aux = aux->sig;
    aux->sig = nuevo;
   
    return l;
}

nodo *leer_archivo (nodo *l){
  int r, i=0, j=0;
  unsigned char d;
  FILE *f;

  f = fopen ("valores.bin" , "rb");
  if (f==NULL){
    printf ("\nNo se puedo abrir el archivo");
    exit (1);
  }
  else{
    r = fread (&d, sizeof(d),1,f);
    while (r!=0){
        if(i > 349 && i < 414){ // 348 + 64 = 412
            l = insertar_fifo (l,d);
            j++;
        }
        r = fread (&d, sizeof(d),1,f);
        i++;
        if(i==350)
            printf("%d !!!",d);
    }
    printf("%d",l->reg);
    printf("\nTamanio de archivo: %dB", i);
    printf("\nCant de REGs (1Byte cada uno): %dB", j);
  }
  if (fclose(f)!=0){
    printf ("\nNo se pudo cerrar el archivo!!!");
    exit (2);
  }
  return l;
}

//Mostrar lista

void mostrar(nodo *l){
nodo *aux=l;
    int i=0;
printf("\nLISTA\n-----\n");
while(aux!=NULL){
printf("\n%d --> %02x", i,aux->reg);
printf ("\n----------------------------------------------\n");
aux=aux->sig; //para avanzar sin cambiar el puntero l.
        i++;
}
}

void mostrar_registros(nodo *l){ // Muestra REGS 0 a D
nodo *aux=l;
    int i;

printf("\n\nRegistros:\n---------\n");

for(i=0 ; i < 14 ; i++){
printf("\n\t REG%02X: %02X", i,aux->reg);
        printf("\n--------------------\n");
        aux=aux->sig; //para avanzar sin cambiar el puntero l.
    }
    printf ("\n");
}

void mostrar_registros_binario(nodo *l){
    int j, k, i;

    printf("\n\t--------BIN--------\n");
    for(i=0 ; i < 14 ; i++){
       
        printf("\n\t REG%02X: ", i);
        //printf("%d", l->reg);
        //printf("\n");
        for(j=7; j>=0; j--){ //esto es clave porque si no imprime al revés
            k = l->reg >> j; //shifteo para dividir por dos en cada paso
            if(k & 1){ //si este AND BIT es verdadero => k=1
                printf("1");
            }
            else{
                printf("0");
            }
        }
        l = l->sig; //avanza la listaaaaaaaaaaa
        printf("\n\t--------------------\n");
    }
}

nodo *destruir_lista(nodo *l){
    nodo *aux; //sin un auxiliar se pierde la referencia
   
    while(l != NULL){
        aux = l; // guardo a lo que apunta l
        l = l->sig; //avanzo la lista sin perder ref
        free(aux); //borro nodo
    }
    printf("Lista destruída, reeeeeey\n");
    return NULL; //CLAVE
}


void dec2bin(int dec){
    int j, k;
    for (j = 7; j >= 0; j--){   // esto es clave porque si no imprime al revés
        k = dec >> j; // shifteo para dividir por dos en cada paso
        if (k & 1)
        { // si este AND BIT es verdadero => k=1
        printf("1");
        }
        else
        {
        printf("0");
        }
    }
    return;
}

void  mostrar_hora_anio(nodo *l){
nodo *aux=l;
    int i;
    int hora_anio[51];

for(i=0 ; i < 51 ; i++){
        hora_anio[i] = aux->reg;
aux=aux->sig;
}
    printf("\nHORA: %02x:%02x:%02x", hora_anio[4], hora_anio[2], hora_anio[0]);
    printf("\nANIO: %02x%02x", hora_anio[50], hora_anio[9]);
    printf("\n");
}

void mostrar_binario(nodo *l){
    int j, k;
    while(l != NULL){
        printf("%d", l->reg);
        printf("\n");
        for(j=7; j>=0; j--){ //esto es clave porque si no imprime al revés
            k = l->reg >> j; //shifteo para dividir por dos en cada paso
            if(k & 1){ //si este AND BIT es verdadero => k=1
                printf("1");
            }
            else{
                printf("0");
            }
        }
        l = l->sig; //avanza la listaaaaaaaaaaa
        printf("\n--------\n");
    }
}

void  mostrar_regb(nodo *l){
nodo *aux=l;
    int i;
    int regs[12];

for(i=0 ; i < 11 ; i++){
        //regs[i] = aux->reg;
aux=aux->sig; //para avanzar sin cambiar el puntero l.
}
    //printf("%d\n", i);
    regs[i] = aux->reg;
    printf("\nEl REG_B en BIN es: ");
    dec2bin(regs[i]);
    printf("\n");

    if(regs[i] & 0x20) printf("Alarma Activada\n");
}

int main () {
       
    nodo *lista=NULL;
    int op;

    //lista = NULL;
    lista = leer_archivo(lista);
   
    do {
        printf ("\n1) Mostar el contenido de los registros (0 al D):");
        printf ("\n2) Mostrar hora y año:");
        printf ("\n3) Mostrar REG_B:");
        printf ("\n4) Salir (0):");
        printf ("\n-----------------------");
        printf ("\nIngrese opcion: ");

        scanf ("%d", &op);
       
        switch (op) {
            case 0: //Opcion 0: Sale del menu
                printf ("Fin del programa!!!\n\n");
            break;
            case 1: //Opcion 1: Muestra los registros
               
                mostrar_registros(lista);
                mostrar_registros_binario(lista);            
            break;
        case 2: //Opcion 2: Configuracion de alarma
            //mostrar(lista); //NO ME DA UN ANIO LÓGICO
            mostrar_hora_anio(lista);
            break;
        case 3: // Mostrar REG_B y flag AIE
            mostrar_regb(lista);
            break;
        case 4: //Finalizar Programa

            break;
        default: //Otras opciones
            printf ("Opcion invalida, ingrese nuevamente!\n");
        } //Fin switch (opc)
    } while (op != 0); //Fin de do while

    destruir_lista(lista);
   
    return 0;
}

/*El Microprocesador es la unidad de prosamento (CPU) y un MC es el MP junto con los periféricos, RAM, etc.*/ 