//Leer el archivo estudiantes.dat y mostrar el estudiante con el mayor promedio.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define MAX 100

struct estudiante {
    int legajo;
    char nombre[30];
    float promedio;
};

void muestra_datos (struct estudiante e){
    printf ("Legajo: %d - Nombre: %s - Promedio: %.2f \n", e.legajo, e.nombre, e.promedio);
}

void muestra_vector (struct estudiante v[MAX],int j){
    int i;
    for(i=0;i<j;i++){
        muestra_datos (v[i]);
    }
}

void mejor_prom (struct estudiante v[MAX],int j){
    int i,rep=0;
    float mejor;
    char alumno [30];
    for(i=1;i<j;i++){//Almaceno en mejor el mejor promedio de todos
        if (v[0].promedio<=v[i].promedio){
            mejor=v[i].promedio;
            /*strcpy(alumno,v[i].nombre);
            if(v[0].promedio=v[i].promedio){
                rep++;
            }*/
        }
    }
    printf("El/los mejores promedios fueron de: \n");
    for(i=0;i<j;i++){//comparo mejor con todos los promedios, si es igual lo muestro
        if(mejor==v[i].promedio){
            muestra_datos(v[i]);
        }   
    }
}

int lee_archivo (struct estudiante v[MAX]){
    FILE *f;
    int res, i=1, elem_leidos=1;
    f=fopen("estudiantes.dat","rb");
    if (f==NULL){
        printf("error al abrir el archivo");
        exit (1);
    }
    else{
        res=fread(v,sizeof(v[0]),1,f);
        //printf("Antes del while %d \n",res);// acá res=1
        if (res!=1){
            printf("Error al leer el archivo");
            exit (2);
        }
        while (res==1){ //mientras pueda leer un elemento va a seguir en el while
            res=fread(&v[i],sizeof(v[0]),1,f);
            i++;
            if(res==1){       
                elem_leidos++;
                //printf(" dentro del while %d \n",res);
                }
            }
        }
        res=fclose(f);
        if(res!=0){//si devuelve algo distinto de 0 hay un error
            printf("error al cerrar el archivo");
            exit (3);
        }
    return (elem_leidos);
}

int main (){
    struct estudiante v[MAX]; 
    int elem_leidos;
    elem_leidos=lee_archivo(v);
    printf("elementos leidos :%d \n",elem_leidos);
    muestra_vector(v,elem_leidos);
    mejor_prom(v,elem_leidos);
return 0;
}