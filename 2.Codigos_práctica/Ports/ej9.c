/*9. Suponga que el archivo rtc.bin es un archivo binario de tamaño desconocido pero
menor a 1kB (1024 bytes). Suponga que los primeros 64 bytes del archivo
corresponden a los registros/memoria del RTC de una PC.
Se pide escribir un programa en C que lea el archivo y muestre un menú repetitivo
que en base a su contenido permita las siguientes opciones:
9.1. Informar el tamaño del archivo
9.2. Mostrar la hora en formato hh:mi:ss
9.3. Mostrar el año completo en formato aaaa, es decir, si fuera 2022 debería
mostrar "2022"
9.4. Informar si el bit AIE está activo (si/no)
9.5. Salir
Nota: para probar puede usar cualquier archivo de tamaño adecuado, aunque no
sabrá qué valores contiene.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

struct rtc{
    unsigned char seg;
    unsigned char seg_alarm;
    unsigned char min;
    unsigned char min_alarm;
    unsigned char hora;
    unsigned char hora_alarm;
    unsigned char dia_sem;
    unsigned char dia_mes;
    unsigned char mes;
    unsigned char anio2;
    unsigned char regA;
    unsigned char regB;
    unsigned char regC;
    unsigned char regD;
};

int main(){
    struct rtc v[10];//cada struct son 14 bytes, total reservado 140 bytes
    FILE *arch;
    int i=0, op, tam;

    arch = fopen("rtc.bin", "rb");
    if(arch == NULL){
        printf("Error al leer el archivo. \n");
        exit(1);
    }

    while( 1 == fread(&v[i], sizeof(struct rtc), 1, arch) )
        i++;

    if(fclose(arch) != 0)
    {
        printf("Error al cerrar archivo. \n");
        exit(1);
    }

    printf("Elija una opcion: \n");
    printf("1-Informar tamanio del archivo. \n");
    printf("2-Mostrar hora. \n");
    printf("3-Mostrar anio. \n");
    printf("4-Informar AIE. \n");
    printf("5-Salir \n");
    scanf("%d", &op);

    while(op != 5)
    {
        switch(op)
        {
            case 1: tam = (i-1) * 64;
                    printf("El tamanio del archivo es de %d bytes. \n", tam);
                    break;
            case 2: printf("Hora: %02x:%02x:%02x. \n", v[1].hora, v[1].min, v[1].seg);
                    break;
            case 3: printf("Anio: 20%02x. \n", v[1].anio2);
                    break;
            case 4: if((v[1].regB & 0x20) != 0) printf("El bit AIE esta en 1. \n");
                    else printf("El bit AIE esta en 0. \n");
                    break;
            default:    printf("Por favor, elija una opcion valida. \n");
                        break;
        }
        printf("Elija una opcion: \n");
        printf("1-Informar tamanio del archivo. \n");
        printf("2-Mostrar hora. \n");
        printf("3-Mostrar anio. \n");
        printf("4-Informar AIE. \n");
        printf("5-Salir \n");
        scanf("%d", &op);
    }

    return 0;
}
