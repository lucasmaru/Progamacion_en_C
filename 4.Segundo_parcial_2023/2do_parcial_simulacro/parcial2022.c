# include <stdio.h>
# include <stdlib.h>

#define DATOS_SALTEABLES  349
#define CANT_DATOS  64

void lee_archivo_vector(unsigned char *datos){
    FILE* f;
    int i=0;
    unsigned char temp;

    f = fopen("valores.bin","rb");
    if(f==NULL){                         //no puede abrir el archivo
        printf("Error al abrir el archivo\n\n");
        exit(1);
    }
    else{                               //abre el archivo
        while( (fread(&temp,sizeof(temp),1,f) == 1) && i<(DATOS_SALTEABLES + CANT_DATOS)){  //349+64=413
            if(i>DATOS_SALTEABLES){
                datos[i-350]=temp;
            }
            i++;
        }
        if(i!=413){
            printf("%dError al leer el archivo\n\n",i);
            exit (2);
        }        
        if (fclose(f)!=0){
            printf("Error al cerrar el archivo\n\n");
            exit (3);
        }
        printf("Archivo leído correctamente\n\n");
    }
}

void Muestrabin (unsigned char* datos){//Muestra todos los registros en binario
    int i,j;
    unsigned char aux;
    for(i=0;i<14;i++){//Recorre cada registro
        printf("\n%02X:",i);
        for(j=7;j>=0;j--){//Recorre cada bit empezando por el msb "bit más significativo"
            aux=datos[i]>>j;
            if(aux&1 ==1)
                printf("1");
            else
                printf("0");
        }
    }
    printf("\n\n");
}

void Muestra1bin(unsigned char dato){//recibe un byte y lo muestra en binario
    int j;
    unsigned char aux;

    printf("\nREG:");
    for(j=7;j>=0;j--){//Recorre cada bit empezando por el msb "bit más significativo"
        aux=dato>>j;
        if(aux&1 ==1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void Mostrar_14(unsigned char *datos){
    int j;
    printf("REG HEXA");  
    for(j=0;j<14;j++)
        printf("\n%02X: %02X",j,datos[j]);          
    printf("\n\n");
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

void AF (unsigned char* datos){
    unsigned char reg_c;
    reg_c = datos[12];
    if ((reg_c & 0x20) != 0)
        printf("AF activado \n\n");
    else
        printf("AF desactivado\n\n");
}

int main(){
    int opcion,i;
    unsigned char datos [64];
    
    lee_archivo_vector(datos);
    
    do{
        printf("1__Mostrar primeros 14 valores del RTC en hexa y en binario\n");                
        printf("2__Mostrar la hora en formato hh:mi:ss y el año completo en formato aaaa\n");       
        printf("3__Mostra registro B en formato binario e indicar si hay un alarma programada\n");
        printf("4__Salir\n");
        printf("--------------------------\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                Mostrar_14(datos);
                printf("REG BINARIO");
                Muestrabin(datos);
                break;
            case 2:
                Mostrar_hora(datos);
                Mostrar_año(datos);
                break;
            case 3:
                Muestra1bin(datos[11]);
                AF(datos);
                break;           
            case 4:
                printf("Programa terminado\n\n");
                break;
            default:
        }
    }while (opcion != 4);
    return 0;
}