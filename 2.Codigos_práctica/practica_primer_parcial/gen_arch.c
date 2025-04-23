/*Genera archivo*/
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct precios{
    char alias[20];
    float precio;
}precios;

int main (){
    FILE* f;
    int i=0;
    int j=0;
    precios vector_precios[10];
    /*for(i=0;i<10;i++){
        printf("\n%d",i);
        printf("\nIngrese variedad:");
        scanf("%s",vector_precios[i].alias);
        printf("\nIngrese precio:");
        scanf("%f",&vector_precios[i].precio);
    }*/

    strcpy(vector_precios[0].alias,"Muzzarella");  //1
    strcpy(vector_precios[1].alias,"Fugazzeta");
    strcpy(vector_precios[2].alias,"Provolone");
    strcpy(vector_precios[3].alias,"Fugazetta_rellena");
    strcpy(vector_precios[4].alias,"Jamon");  //5
    strcpy(vector_precios[5].alias,"Morron");
    strcpy(vector_precios[6].alias,"Jamon_y_morron");
    strcpy(vector_precios[7].alias,"Salchicha");
    strcpy(vector_precios[8].alias,"Papa_frita");
    strcpy(vector_precios[9].alias,"Anana");  //10
    vector_precios[0].precio=1500;
    vector_precios[1].precio=1700;
    vector_precios[2].precio=1800;
    vector_precios[3].precio=2000;
    vector_precios[4].precio=1600;
    vector_precios[5].precio=1600;
    vector_precios[6].precio=1700;
    vector_precios[7].precio=1750;
    vector_precios[8].precio=1750;
    vector_precios[9].precio=2000;    
    f=fopen("preciosproductos.dat","wb");
    if(f==NULL){
        printf("Error al abrir el archivo\n\n");
        exit(1);
    }
    else{
        for(i=0;i<10;i++){
            fwrite(&vector_precios[i],sizeof(vector_precios[i]),10,f);
            j++;
        }
        printf("Se guardaron %d precios",j);
        if (fclose(f)!=0)
            printf("Error al cerrar el archivo");
    }
    return 0;
}
