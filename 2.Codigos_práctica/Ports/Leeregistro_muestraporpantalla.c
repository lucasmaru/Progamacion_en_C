/*1. Escribir una función en lenguaje C que reciba como argumento un nro de
registro (0-13), lea el valor de ese registro del RTC y lo imprima por pantalla
como hexadecimal.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>

void Lee_reg_muestra_pantalla(unsigned char reg){
    unsigned char P=0x70,a,b;

    //Pido los permisos y los valido
    if(ioperm(P,2,1)!=0){
        perror("ioperm"); //Muestra "ioperm" + el mensaje de error 
        exit(1);
    }
    //Leo registro A, para saber cuando puedo hacer la lectura
    outb(0x0A,P);//Pongo a P apuntado a el registro A
    a=inb(P+1);//Leo el registro
    if(a & 0x80!=0)//Mascara que me da el MSB
        usleep(1984);//Espero 1984 micro segundos
    //Leo el registro que me llegó por argumento
    outb(reg,P);
    b=inb(P+1);
    //Anulo los permisos
    if(ioperm(P,2,0)!=0){
        perror("ioperm");
        exit(2);
    }
    //Imprimo el dato
    printf("El dato en decimal del registro es: %X \n",b);//Me devuelve el nro en decimal porque esta guardado en BSD
    printf("b impreso con formato decimal: %d\n",b);
    dec_a_hexa(b);
}

int main(){
    Lee_reg_muestra_pantalla(0x00);
    return 0;
}