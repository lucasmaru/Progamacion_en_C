/*5. Suponga que se ejecutan las siguientes instrucciones:
struct punto {
int x;
int y;
};
struct rectangulo {
struct punto superior_izq;
struct punto inferior_der;
};
struct rectangulo *p;
Escriba las líneas necesarias para que p apunte a una estructura rectangulo válida que tenga (10,25) como esquina superior izquierda y
(20,15) como esquina inferior derecha.*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct punto {
int x;
int y;
};

struct rectangulo {
struct punto superior_izq;
struct punto inferior_der;
};

int main (){
struct rectangulo *p;
struct punto p1;
struct punto p2;
p=(struct rectangulo*) malloc(sizeof(struct rectangulo));
if(p==NULL){
    printf("Error en la reserva de memoria");
    exit (1);
}
else{
    p1.x=10;
    p1.y=25;
    p2.x=20;
    p2.y=15;
    p->superior_izq=p1;
    p->inferior_der=p2;
}
printf("Sup izq: (%d , %d)\n",p->superior_izq.x,p->superior_izq.y);
printf("Inf der: (%d , %d)",p->inferior_der.x,p->inferior_der.y);
return 0;
}

