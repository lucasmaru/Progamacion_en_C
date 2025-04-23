/*9. Escribir un programa en lenguaje C que permita Ingresar por teclado un
valor…
b. en hexadecimal, sin signo, de 8 bits, y lo muestre en decimal*/

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

unsigned char hexa_a_dec(unsigned char* hexa){
    int i,j=0,largo;
    int suma=0;

    printf("recibe %s \n",hexa);// chequeo si recibio correctamente
    largo=strlen(hexa);
    //printf("El largo de la cadena es:%d \n",largo);
    for(i=largo-1;i>=0;i--){
        if(hexa[i]>='0'&& hexa[i]<='9'){
            suma=suma+(hexa[i]-48)*pow(16,j);
            j++;
        }
        else if (hexa[i]>='A' && hexa[i]<='F'){
            suma=suma+(hexa[i]-55)*pow(16,j);
            j++;
        }
        //printf("suma parcial: %d \n",suma);
    }

    printf("El valor en decimal de %s es : %d\n",hexa,suma);
    return(suma);
}

int main(){
    unsigned char* hexa=NULL;
    int dec,i;

    hexa=(unsigned char*) realloc(hexa,sizeof(unsigned char)*5);//Reservo espacio en memoria para 5 bytes exageradamente
    if (hexa!=NULL){
        printf("Ingrese un hexadecimal de hasta 7 cifras(use mayúsculas): \n");
        scanf("%s",hexa);
        dec=hexa_a_dec(hexa);
    }
    else{
        printf("Error en la reserva de memoria");
        exit (1);
    } 
    return 0; 
}