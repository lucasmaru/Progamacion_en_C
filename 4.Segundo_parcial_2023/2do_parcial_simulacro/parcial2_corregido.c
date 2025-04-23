/*2do parcial*/

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

void dec_a_hexa(int dec){
    int i=0,j=0;
    unsigned char* res=NULL;//Va a ser el hexa, por eso es unsigned char
    int restemp;

    restemp=dec;//Para no perder el decimal
    if(restemp>=16){
        while (restemp >=16){//Si se cumple la condicion puedo dividir
            res=(unsigned char*) realloc(res,sizeof (unsigned char)*(i+1));//Reservo un espacio de memoria
            if (res!=NULL){ //Si lo puedo reservar entro
                res[i]= restemp%16;//Almaceno el resto de la división
                restemp= restemp/16;//Divido para tener el cociente
                i++;//avanza en res, aumenta malloc y cuenta las veces que entro al while
                if (restemp<16){
                    res=(unsigned char*) realloc(res,sizeof(unsigned char)*(i+1));
                    res[i]=restemp;
                }    
            }
            else{//Si no puedo reservar cierro el programa
                printf("Problema con memoria\n");
                exit (1);
            }
        }
        printf("El decimal %d es el hexadecimal : ", dec);
        for(j=i;j>=0;j--)
            printf("%X",res[j]);
        printf("\n");
    }
    else if(restemp>=0 && restemp<16){
        printf("El decimal %d es el hexadecimal %X \n",restemp,restemp);
    } 
}

void Muestrabin (unsigned char* datos){//Muestra todos los registros en binario
    int i,j;
    unsigned char aux;
    for(i=0;i<14;i++){//Recorre cada registro
        printf("\n\tREG%02X:",i);
        for(j=7;j>=0;j--){//Recorre cada bit empezando por el msb "bit más significativo"
            aux=datos[i]>>j;
            if(aux&1 ==1)
                printf("1");
            else
                printf("0");
        }
    }
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

void decabin (unsigned char dec){
    int i=0,j=0;
    unsigned char* res=NULL;//Va a ser el binario, por eso es unsigned char
    int restemp;

    restemp=dec;//Para no perder el decimal
    if(restemp>=2){
        while (restemp >=2){//Si se cumple la condicion puedo dividir
            res=(unsigned char*) realloc(res,sizeof (unsigned char)*(i+1));//Reservo un espacio de memoria
            if (res!=NULL){ //Si lo puedo reservar entro
                res[i]= restemp%2;//Almaceno el resto de la división
                restemp= restemp/2;//actualizo restemp con el cociente
                i++;//avanza en res, aumenta malloc y cuenta las veces que entro al while
                if (restemp<2){//Entra cuando el resto es menor que 2 y lo almacena
                    res=(unsigned char*) realloc(res,sizeof(unsigned char)*(i+1));
                    res[i]=restemp;
                }    
            }
            else{//Si no puedo reservar cierro el programa
                printf("Problema con memoria\n");
                exit (1);
            }
        }
        printf("El decimal %d es el binario : ", dec);
        for(j=i;j>=0;j--)
            printf("%d",res[j]);
        printf("\n");
    }
    else if (restemp==0)
        printf("El decimal %d es el binario 0\n",dec);
    else if (restemp==1)
        printf("El decimal %d es el binario 1\n",dec);
    free(res);//Si tuviera que devolver el dato al main, debería liberar la memoria desde el main
    res=NULL; 
}



int main(){

    int op,i,j=0,cont=0;
    FILE* f;
    unsigned char aux;
    unsigned char datos[64];
    unsigned char hora, minutos,segundos,año1,año2;
    unsigned char masc;

    f=fopen("valores.bin","rb");//Abro archivo
    if (f==NULL)
        printf("Error al leer el archivo \n");
    
    for(i=0;i<413;i++){
        cont=cont+fread(&aux,sizeof(unsigned char),1,f);
        if(i>349 && i<413){//349+64=413
            datos[j]=aux;
            j++;
        }
    }
    if(cont!=413){
        printf("Error al leer el archivo");
        exit(1);
    }

    do{
        printf("\n1) Mostrar los primeros 14 valores del RTC que se menciona en el enunciado en formato hexa y binario.");
        printf("\n2) Mostrar la hora en formato hh:mm:ss y el año completo en formato aaaa");
        printf("\n3) Mostrar los datos correspondientes al registro B e indicar si hay una alarma programada");
        printf("\n4) Finalizar el programa");
        printf("\n--------------------------");
        printf("\nIngrese opcion: ");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            printf("\nREGISTROS BIN");
            Muestrabin(datos);
            printf("\nREGISTROS HEXA");
            for(i=0;i<14;i++)
                printf("\n\tREG%02X: %02X",i,datos[i]);
            ;
            break;
        case 2:
            año1=datos[50];
            año2=datos[9];
            hora=datos[4];
            minutos=datos[2];
            segundos=datos[0];
            printf ("Año: %02hhx%02hhx Hora: %02hhx:%02hhx:%02hhx\n",año1,año2, hora, minutos, segundos);//Asumo BCD muestro hexa
            break;
        case 3:
            Muestra1bin(datos[11]);
            masc= datos[11] & 0x20;
            if (masc!=0)
                printf("Hay alarma programda\n");
            else
                printf("No hay alarma programada\n");
            printf("\n");
            break;
        case 4:
            printf("Finalizo el programa");
            break;
        default:printf("Opcion incorrecta\n");
            break;
        }

    } while (op!=4);

    

    return 0;
}