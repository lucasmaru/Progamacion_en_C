/*Recibe un binario y lo pasa a hexadecimal*/

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

unsigned char* binahexa(unsigned char* bin, int digitos){
    int i,j=0,cont=0,suma=0,dighexa=0;
    unsigned char* hexa=NULL;

    hexa=(unsigned char*) realloc(hexa,sizeof(unsigned char)*5);//Reservo espacio en memoria para 4 bytes exageradamente
    if (hexa!=NULL){
        i=digitos-1;
        printf("digitos %d \n",digitos);        
        while(cont<4 &&  i>=0){
            if(bin[i]=='1'){
                switch(cont){
                    case 0:
                        suma=suma+1;
                        break;
                    case 1:
                        suma=suma+2;
                        break;
                    case 2:
                        suma=suma+4;
                        break;
                    case 3:
                        suma=suma+8;
                        break;        
                }
            }
            cont++;
            i--;
        }       
        dighexa++;
        if (suma<=9)
            hexa[j]=suma;
        if(suma>9){
            switch(suma){
                case 10:
                    hexa[j]='A';
                    break;
                case 11:
                    hexa[j]='B';
                    break;
                case 12:
                    hexa[j]='C';
                    break;
                case 13:
                    hexa[j]='D';
                    break;
                case 14:
                    hexa[j]='E';
                    break;
                case 15:
                    hexa[j]='F';
                    break;
            }
        }   
    }
    else{
        printf("Error en la reserva de memoria");
        exit (1);
    }
    printf("El hexadecimal es: \n");
    for(i=dighexa-1;i>=0;i--){
        printf("%c",hexa[j]);
    }
    printf("\n");
    return hexa;
}

int main(){
    unsigned char* bin=NULL; 
    unsigned char* hexa=NULL;
    int i,aux,digitos;

    bin=(unsigned char*) realloc(bin,sizeof(unsigned char)*5);//Reservo espacio en memoria para 5 bytes exageradamente
    if (bin!=NULL){
        printf("Ingrese un nro binario(solo 1 o 0): \n");
        scanf("%s",bin);
        do{
            digitos=strlen(bin);
            aux=0;
            for(i=0;i<digitos;i++){
                if(bin[i]!='0' && bin[i]!='1')
                    aux++;
            }
            if(aux!=0){
                printf("Reingrese el binario: \n");
                scanf("%s",bin);
            }
        }while(aux!=0);
        hexa=binahexa(bin,digitos);
    }
    else{
        printf("Error en la reserva de memoria");
        exit (1);
    }
    free(bin);
    bin=NULL;
    free(hexa);
    hexa=NULL; 
    return 0;
}
