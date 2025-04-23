/*Recibe un número binario y lo lee de a 4 bit para tratarlo como un BSD luego devuelve el decimal compuesto por los dos binarios */

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>

# define masc1 0xF //00001111
# define masc2 0xF0//11110000

void BCDaDEC(unsigned char nro){
unsigned char decena;
unsigned char unidad;
unsigned char decimal;

printf("recibió:%X \n",nro);
unidad= nro&masc1;
printf("%X \n",unidad);
decena=(nro&masc2)>>4;
printf("%X \n",decena);
decimal=(decena*10)+(unidad*1);
printf("En BCD %d y en decimal %d \n",nro,decimal);

}

int main (){
    unsigned int dato;

    printf("Ingrese el numero en hexadecimal que representa al BCD: \n");
    scanf("%x",&dato);
    BCDaDEC(dato);

    return 0;
}