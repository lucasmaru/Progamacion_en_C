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

    int op,i,cont;
    FILE* f;
    unsigned char aux[349];
    unsigned char datos[65];
    unsigned char hora, minutos,segundos,año1,año2;
    unsigned char masc;

    f=fopen("valores.bin","rb");//Abro archivo
    if (f==NULL)
        printf("Error al leer el archivo \n");

    for(i=0;i<349;i++)
        cont=cont+(fread(&aux[i],sizeof(unsigned char),1,f));//Leo los primeros 349 bytes
    if(cont!=349){
        printf("cont:%d \n",cont);
        printf("Error en primer lectura\n");
        exit (1);
    }
    //datos=(unsigned char*)realloc(datos,sizeof(unsigned char)*64);
    //if(datos==NULL){
    //    printf("Error en reserva de memoria");
    //    exit(2);
    //}
    cont=0;//Reinicio aux para no usar otra variable
    for(i=0;i<64;i++){
        cont=cont+(fread(&datos[i],sizeof(unsigned char),1,f));
    }
    if(cont!=64){
        printf("Error en lectura de datos utiles\n");
        exit (1);        
    } 
    do{
        printf("1_Mostrar los primeros 14 valores del RTC que se menciona en el enunciado en formato hexa y binario.\n");
        printf("2_Mostrar la hora en formato hh:mm:ss y el año completo en formato aaaa \n");
        printf("3_Mostrar los datos correspondientes al registro B e indicar si hay una alarma programada\n");
        printf("4_Finalizar el programa\n");
        scanf("%d",&op);
        switch (op)
        {
        case 1:
            //decabin(datos[0]);
            for(i=0;i<14;i++)
                decabin(datos[i]);
            printf("\n");
            for(i=0;i<14;i++)
                dec_a_hexa(datos[i]);
            ;
            break;
        case 2:
            año1=datos[32];
            año2=datos[9];
            hora=datos[4];
            minutos=datos[2];
            segundos=datos[0];
            printf ("Año: %02hhx%02hhx Hora: %02hhx:%02hhx:%02hhx\n",año1,año2, hora, minutos, segundos);//Asumo BCD muestro hexa
            break;
        case 3:
            decabin(datos[11]);
            masc=datos[11]&0x32;
            if (masc!=0)
                printf("Hay alarma programda\n");
            else
                printf("No hay alarma programada\n");
            ;
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

