/*Ejemplo de estructuras:
Este programa permite ingresar por teclado los datos (codigo, nombre, precio y stock)
de una cant. indefinida de productos finalizando cuando el codigo ingresado es cero. 
Los productos se almacenan en un vector que luego se recorre y se muestra por pantalla.
*/
# include <stdio.h>
# define MAX 1000 
struct catalogo {
    int codigo;
    char nombre[15];
    float precio;
    long stock;
};
//Muesta los datos almacenados en la variable p de tipo strucproducto que definí antes
void muestra_datos (struct catalogo p) {  
    printf ("Codigo: %d - Nombre: %s - Precio: %.2f - Stock: %ld\n", p.codigo, p.nombre, p.precio, p.stock);
}

void  muestra_vector (struct catalogo v[],int cant){
    int i;
    for(i=0;i<cant;i++){
        muestra_datos (v[i]);
    }
}

int main(){
    int cod, i=0;
    struct catalogo vp[MAX];//defino el vector vp de tipo de dato struc catalogo de MAX cant de elementos
    printf("Ingrese codigo del producto o cero si desea salir: ");
    scanf("%d",&cod);
    while (cod!=0){
        vp[i].codigo=cod;//paso el numero de codigo de cod al vector de estructura
        printf("Ingrese el nombre del producto de codigo %d: ",cod);
        scanf("%s",vp[i].nombre);//sin & porque nombre es un string
        printf("Ingrese el precio: ");
        scanf("%f",&vp[i].precio);//con & porque precio es un float
        printf("Ingrese la cantidad: ");
        scanf("%ld",&vp[i].stock);//con & porque precio es un long
        muestra_datos(vp[i]);
        i++; // incremento el contador por si se ejecuta otro ciclo
        printf("Ingrese el siguiente codigo o cero si desea salir:");
        scanf("%d",&cod);
    }
    muestra_vector(vp,i);//Pasó el vector sin []
    return 0;
}