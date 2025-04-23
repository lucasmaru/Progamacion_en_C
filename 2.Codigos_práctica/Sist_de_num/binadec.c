/*Recibe un binario y lo pasa a decimal*/

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

unsigned char binadec(unsigned char* bin){
    int i,j=0,largo;
    int suma=0;

    //printf("recibe %s \n",bin);// chequeo si recibio correctamente
    largo=strlen(bin);
    //printf("El largo de la cadena es:%d \n",largo);
    for(i=largo-1;i>=0;i--){
        if(bin[i]=='1')
            suma=suma+(bin[i]-48)*pow(2,j);
        j++;
        //printf("suma parcial: %d \n",suma);
        //printf("j parcial: %d \n",j);
    }

    printf("El valor en decimal de %s es : %d\n",bin,suma);
    return(suma);
}

int main(){
    unsigned char* bin=NULL;
    int dec,i,aux,digitos;

    bin=(unsigned char*) realloc(bin,sizeof(unsigned char)*4);//Reservo espacio en memoria para 4 bytes exageradamente
    if (bin!=NULL){
        printf("Ingrese un nro binario(solo 1 o 0): \n");
        scanf("%s",bin);
        do{
            digitos=strlen(bin);
            aux=0;
            for(i=0;i<digitos;i++){
                //printf("caracter %c",bin[i]);
                if(bin[i]!='0' && bin[i]!='1')
                    aux++;
            }
            if(aux!=0){
                printf("Reingrese el binario: \n");
                scanf("%s",bin);
            }
        }while(aux!=0);
        dec=binadec(bin);
    }
    else{
        printf("Error en la reserva de memoria");
        exit (1);
    }
    free(bin);
    bin=NULL; 
    return 0; 
}