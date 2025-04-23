/*Escribir una función que devuelva un puntero al máximo valor de un vector de
“doubles”. Si el vector está vacío (cant = 0) la función debe retornar NULL.*/
# include <stdio.h>
# include <stdlib.h>
double* max (double *v, int cant){
    int i;
    //double max; inicialmente definí esta variable para acumular el double mayor, luego vi que no es necesaria
    double *p;
    if (cant==0){
        return NULL;
    }
    p=v;//esta linea pone al puntero p apuntando al primer elemento de v
    printf("primer elemento: %.2f \n",*p);//para probar si puede acceder al primer elemento lo imprimo y funciona
    for(i=1;i<cant;i++){ //arranco en i=1  puese p ya está apuntando a v[0]
        if(*(v+i)>*p){   //si no se cumple esta condición para ningún elemento en p esta almacenado v[0]
            p= v+i; //si se cumple guardo en p la dirección de ese elemento y paso p
        }
    }
    return p;
}
int main (){
    double vec [5] = {998.3,600,5.5,289,6};
    double *pa;
    pa=max(vec,5);
    if(pa!=NULL){
    printf("la direccion de pa es %p y su contenido es %.2f \n",pa,*pa);
    }
    else{
        printf("la funcion devolvio NULL para vec");
    }

    return 0;
}

