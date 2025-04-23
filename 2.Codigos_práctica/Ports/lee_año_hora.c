/*
Este programa lee el anio y la hora, minutos y segundos del RTC
Programacion UNSAM
Autor: David Lopez
Año: 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>


#define P 0x70 //Primer puerto de RTC

/* Esta funcion lee un byte del registro del RTC cuyo nro se recibe como argumento */ 
unsigned char in (unsigned char reg){
  //Con outb pongo el valor reg en el puerto de direc, con esto hago que el puerto de datos se conecte con la direc de memoria reg
  //Maneja el"switch" para conectar al puerto 71 con la dirección de memoria que paso en reg
  outb (reg, P);
  /*Leo y retorno el registro 71 que va a estar apuntando a la dirección de memoria que elegí con el outb anterior */
  return inb(P + 1);
  }
  
int main(){
  unsigned char a, seg, min, hora, an1, an2;

  /* Dar permisos a los ports 70 y 71 */
  if (ioperm(P, 2, 1)) {//if abreviado, if(algo) = if (algo!=0)
    //Paso el puerto a habilitar, cuantos habilito desde ahí, los pongo en 1 que es habilitado
    perror("ioperm"); //Muestra "ioperm" + el mensaje de error 
    exit(1);
  }
  
  /*Leer reg A para saber si el reloj se esta actualizando o no, y si puedo trabaja con el*/
  a = in (0x0A);//LLamo a mi función in y le paso el registro que necesito que me lea, luego lo almaceno en a
  if ((a & 0x80) != 0) //Verif. bit 7 (UIP). Ojo prioridades operadores
    usleep (1984); //Esperar lo que dura la actualiz. en el peor caso (1984us)

  /*Leer segundos. Para demostrar lo hago sin usar la funcion in() definida arriba*/
  outb(0x00, P);
  seg = inb(P + 1);

  /*Leer minutos*/
  min = in(0x02);

  /*Leer hora*/
  hora = in(0x04);

  /*Leer anio primeros digitos*/
  an1 = in(0x32);

  /*Leer anio ultimos digitos*/
  an2 = in(0x09);

  /*Retirar permisos */
  if (ioperm(P, 2, 0)) {
    perror("ioperm");
    exit(1);
  }

  printf ("Año: %02x%02x Hora: %02x:%02x:%02x\n", an1, an2, hora, min, seg);

  return 0;
}