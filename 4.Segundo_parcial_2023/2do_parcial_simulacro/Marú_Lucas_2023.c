/*
ejecicio 1) Una velocidad de clock de 100MHz son 100 millones de instrucciones por segundo. Supongo que el procesador va a iniciar y
terminar una instrucción antes de pasar a la siguiente, por tanto va a necesitar 6x4=24 ciclos para terminar de ejecutarse.
24/ 100.000.000 = 0,00000024.
Va a demorar en ejecutarse 24x10^-8 segundos.
*/

# include <stdio.h>
# include <stdlib.h>

void Mostrar_RTC(unsigned char*datos){
    unsigned char min_actual;
    unsigned char min_alarma;

    min_alarma=datos[3];
    min_actual=datos[2];

    printf("\nMinuto alarma %02x\n",min_alarma);
    printf("\nMinuto hora actual %02x\n\n",min_actual);
}

void PF (unsigned char* datos){
    unsigned char reg_c;
    reg_c = datos[12];
    if ((reg_c & 0x40) != 0)
        printf("PF activado \n\n");
    else
        printf("PF desactivado\n\n");
}

void Graba(unsigned char *datos){
    FILE *f;
    int aux,i;
    unsigned char temp;
    f = fopen("datos.bin","wb");
    if(f==NULL){                         //no puede abrir el archivo
        printf("Error al abrir el archivo\n\n");
        exit(1);
    }
    else{
        for(i=0;i<24;i++){
            if( ( ( datos[i] & 0x1 ) !=0 ) &&( ( datos[i] & 0x2 ) !=0 )){
                aux=fwrite(&datos[i],sizeof(datos[i]),1,f);
                if(aux!=1)
                    printf("Error al grabar archivo");
            }
        }
        if (fclose(f)!=0){
            printf("Error al cerrar el archivo\n\n");
            exit (2);
        }
        printf("Archivo leído correctamente\n\n");
    }
}


void Muestrabin (unsigned char* datos){//Muestra todos los registros en binario
    int i,j;
    unsigned char aux;
    for(i=0;i<24;i++){//Recorre cada registro
        printf("\n\t");
        for(j=7;j>=0;j--){//Recorre cada bit empezando por el msb "bit más significativo"
            aux=datos[i]>>j;
            if(aux&1 ==1)
                printf("1");
            else
                printf("0");
        }
    }
}

int main(){
    int opcion,i,j=0;
    char *datos="QUIERO ganar la tercera.";
    unsigned char *r =(unsigned char*)datos;
        
    do{
        printf("1__Mostrar en binario, hexadecimal y BCD.\n");                
        printf("2__Guardar los datos \n");       
        printf("3__Mostrar minutos hora y alarma\n");
        printf("4__Mostrar si PF está activo\n");
        printf("5__Salir\n");
        printf("--------------------------\n");
        printf("Seleccione una opción del menú: ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
                printf("En binario:");
                Muestrabin(r);
                printf("\nEn hexadecimal:\n");
                for (i=0;i<24;i++)
                    printf("\t%x\n",r[i]);
                printf("\n\n");
                break;
            case 2:
                Graba(r);
                break;
            case 3:
                Mostrar_RTC(r);
                break;
            case 4:
                PF(r);
                break;           
            case 5:
                printf("Programa terminado\n\n");
                break;
            default:
        }
    }while (opcion != 5);
    return 0;
}