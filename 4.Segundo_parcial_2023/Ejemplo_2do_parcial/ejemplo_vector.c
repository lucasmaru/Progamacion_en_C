/*Ejemplo de ejercicio tomado en segundo en 2do parcial

El archivo rtc.bin es un archivo binario de tamaño desconocido pero menor a 256 bytes.
Los primeros 64 bytes del archivo corresponden a los registros/memoria del RTC de una PC.
Se pide escribir un programa en C que lea el archivo y muestre un menú repetitivo que en base a su contenido permita las
siguientes opciones

1) Informar el tamaño del archivo
2) Mostrar la hora en formato hh:mi:ss
3) Mostrar el año completo en formato aaaa, es decir, si fuera 2022 debería mostrar "2022"
4) Informar si el bit AIE está activo (si/no)
5) Salir


Ejemplos de preguntas teóricas:

¿Cúal es la diferencia entre un Microprocesador y un Microcontrolador?
Un microprocesador es un componente que esta optimizado para procesar instrucciones lógicas y aritméticas, se utiliza en computadoras
personales, consolas, servidores, celulares y no tiene periféricos integrados.
En cambio el microcontrolador es un circuito integrado que combina procesador, memoria y periféricos, estan optimizados para trabajos
específicos y en tiempo real. Tiene una alta aplicación ya que se utiliza sobre todo para sistemas embebidos (autos, cafeteras, maquinas
industriales)

¿Cúales son las 3 etapas del Pipeline de un Cortex M3 y cúal es su ventaja?
Fetch, decode y execute. Al seccionar la ejecución de instrucciones, en un mismo momento se puede estar realizando el fetch de una 
instruccione, el decode de otra y el execute de otra. Esto me permite ejecutar más instrucciones en una misma cantidad de tiempo */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int lee_archivo_vector(unsigned char* datos){
    FILE* f;
    int i=0,aux=0;
    unsigned char temp;
    f = fopen("rtc.bin","rb");
    if(f==NULL){                         //no puede abrir el archivo
        printf("Error al abrir el archivo\n\n");
        exit(1);
    }
    else{                               //abre el archivo
        while(fread(&temp,sizeof(temp),1,f) ==1){
            if(i<64){
                datos[i]=temp;
            }
            i++;
        }        
        if (fclose(f)!=0){
            printf("Error al cerrar el archivo\n\n");
            exit (2);
        }
        printf("Archivo leído correctamente\n\n");
    }
    return i;
}

void Mostrar_hora(unsigned char*datos){
    unsigned char hora;
    unsigned char min;
    unsigned char seg;

    seg=datos[0];
    min=datos[2];
    hora=datos[4];
    printf("\nLa hora es %02x:%02x:%02x\n\n",hora,min,seg);
}

void Mostrar_año(unsigned char* datos){
    unsigned año1, año2;
    
    año2 = datos[9];
    año1 = datos[50];
    printf("El año es %02x%02x \n\n",año1,año2);
}

void AIE (unsigned char* datos){
    unsigned char reg_b;
    reg_b = datos[11];
    if ((reg_b & 0x20) != 0)
        printf("AIE activado \n\n");
    else
        printf("AIE desactivado");
}

int main(){
    int opcion,cant_bytes;
    unsigned char datos [64];

    cant_bytes=lee_archivo_vector(datos);

    do{
        printf("1__Informar el tamaño del archivo\n");                
        printf("2__Mostrar la hora en formato hh:mi:ss\n");       
        printf("3__Mostrar el año completo en formato aaaa\n");
        printf("4__Informar si el bit AIE está activo (si/no)\n");
        printf("5__Salir\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                printf("El archivo tiene %d bytes\n\n",cant_bytes);
                break;
            case 2:
                Mostrar_hora(datos);
                break;
            case 3:
                Mostrar_año(datos);
                break;
            case 4:
                AIE(datos);
                break;                
            case 5:
                printf("Programa terminado\n\n");
                break;
            default:
        }
    }while (opcion != 5);
    return 0;
}
