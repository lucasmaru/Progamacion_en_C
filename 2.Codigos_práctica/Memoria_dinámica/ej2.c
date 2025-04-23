/*2. Escribir un programa para leer el archivo vector .dat del ejercicio anterior y
almacenarlo en un vector. No se conoce la cantidad de elementos y no se puede
limitar*/
# include <stdio.h>
# include <stdlib.h>
void leer (){
    int aux;//valida si pudo o no leer el archivo
    int n=0;//cuenta las veces q entra en el while
    int i;//contador para mostrar los datos leidos
    FILE *f;
    int*datos=NULL;
    f=fopen("vector.dat","rb");
    if (f==NULL) exit(1);
    datos=(int*) malloc(sizeof(int));//reserva memoria para guardar 1 int [1]
    while(fread(&datos[n],sizeof(int),1,f) == 1) {
        n++;
        datos=(int*) realloc(datos, sizeof(int) * (n+1));
    }
    for(i=0;i<n;i++){//muestro lo que leo
        printf("--->datos:%d\n",*(datos+i));
    }
 
    
}
int main (){
    leer();    
    return 0;
}