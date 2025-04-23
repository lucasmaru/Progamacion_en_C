/*Leer por teclado los detalles (legajo, nombre, promedio) de n estudiantes (n <
100) y almacenarlo en el archivo estudiantes.dat.*/
# include <stdio.h>
# include <stdlib.h>
# define MAX 100
struct estudiante {
    int legajo;
    char nombre[30];
    float promedio;
};

void muestra_vector (struct estudiante e){
    printf ("Legajo: %d - Nombre: %s - Promedio: %.2f \n", e.legajo, e.nombre, e.promedio);
}

void graba_archivo (struct estudiante v[MAX],int i){
    FILE *f;
    int res;
    f=fopen("estudiantes.dat","wb");
    if (f==NULL){
        printf("error al abrir el archivo");
        exit (1);
    }
    else{
        res=fwrite(v,sizeof(v[0]),i,f);
        if (res!=i){
            printf("Error al grabar el archivo");
            exit (2);
        }
        res=fclose(f);
        if(res!=0){
            printf("error al cerrar el archivo");
            exit (3);
        }
    }
}

int main (){
    struct estudiante v[MAX];
    int legajo, i=0;
    printf("Ingrese legajo del estudiante o cero si desea salir: ");
    scanf("%d",&legajo);
    while (legajo!=0){
        v[i].legajo=legajo;// pasó la info del legajo al primer lugar del vector tipo struct estudiante   
        printf("Ingrese nombre del estudiante: ");
        scanf("%s",v[i].nombre);// sin & porque es string
        printf("Ingrese el promedio: ");
        scanf("%f",&v[i].promedio);// con & porque es float
        muestra_vector(v[i]);
        i++;
        printf("Ingrese legajo del estudiante o cero si desea salir: ");
        scanf("%d",&legajo);
    }
    graba_archivo(v,i);
    return 0;
}