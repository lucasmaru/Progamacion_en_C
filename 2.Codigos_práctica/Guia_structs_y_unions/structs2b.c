//Leer el archivo estudiantes.dat y mostrar el estudiante con el mayor promedio.
#include <stdio.h>
#include <stdlib.h>
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


int lee_archivo (struct estudiante v[MAX]){
    FILE *f;
    int res, elem_leidos=0;//elem_leidos tiene que ser cero porque el último while que no lea nada, también lo va a incrementar
    f=fopen("estudiantes.dat","rb");
    if (f==NULL){
        printf("error al abrir el archivo");
        exit (1);
    }
    else{   
            do{
                res=fread(v,sizeof(v[0]),1,f);
                if (res==1){
                    elem_leidos++;
                }
            printf("vez numero %d res= %d \n",elem_leidos,res);// acá res=1
            /*if (res!=1){
                printf("Error al leer el archivo");
                exit (2);
            }*/
        }while(res==1);
    }
        res=fclose(f);
        if(res!=0){//si devuelve algo distinto de 0 hay un error
            printf("error al cerrar el archivo");
            exit (3);
        }
    return (elem_leidos);
}
int main (){
    struct estudiante v[MAX]; //La función me lee basura y solo el último de los valores que cargo en structs 1
    int elem_leidos;
    elem_leidos=lee_archivo(v);
    printf("elementos leidos :%d \n",elem_leidos);
    muestra_vector(v,elem_leidos);
return 0;
}