/*9. Escribir un programa en lenguaje C que permita Ingresar por teclado un
valor…
a. en decimal, sin signo, de 8 bits, y lo muestre en hexadecimal
b. en hexadecimal, sin signo, de 8 bits, y lo muestre en decimal*/

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

unsigned char* dec_a_hexa(int dec){
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
        printf("El decimal %d es el hexadecimal : \n", dec);
        for(j=i;j>=0;j--)
            printf("%X",res[j]);
        printf("\n");
        return (res);
    }
    else if(restemp>=0 && restemp<16){
        printf("El decimal %d es el hexadecimal %X \n",restemp,restemp);
        return (res);//Devuelve NULL, no toca esa variable
    } 
}

int main(){
    unsigned char* hexadecimal=NULL;
    int dec;
        
    printf("Ingrese un numero entero: \n");
    scanf("%d",&dec);
    hexadecimal = dec_a_hexa(dec);
    free(hexadecimal);
    hexadecimal=NULL;
    return 0; 
}