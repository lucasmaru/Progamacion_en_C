/*Recibe un decimal y lo devuelve binario. Solo decimales menores a 256 porque en 1 byte caben 2^8 posibilidades*/

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

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
        printf("El decimal %d es el binario : \n", dec);
        for(j=i;j>=0;j--)
            printf("%d",res[j]);
        printf("\n");
    }
    else if (restemp==0)
        printf("El decimal %d es el binario 00000000\n",dec);
    else if (restemp==1)
        printf("El decimal %d es el binario: \n00000001\n",dec);
    free(res);//Si tuviera que devolver el dato al main, debería liberar la memoria desde el main
    res=NULL; 
}

int main(){
    unsigned int dec;
        
    printf("Ingrese un numero entero(menor a 256): \n");
    scanf("%d",&dec);
    while(dec>=256){
        printf("Reingrese el entero, debe ser menor a 256: \n");
        scanf("%d",&dec);
    }
    decabin(dec);
    return 0;
}