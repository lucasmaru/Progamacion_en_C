/*Genera archivo*/
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct mediciones{
    int ppm;
    float temp;
}mediciones;

int main (){
    FILE* f;
    int i=0,j=0;
    int aux_graba;
    int ppm[10]={130,45,44,67,55,29,99,345,39,22};
    float temp[10]={32.3,28.5,18.3,22.1,17.9,33.3,15,16.5,35,15};

    f=fopen("mediciones.dat","wb");
    if(f==NULL){
        printf("Error al abrir el archivo\n\n");
        exit(1);
    }
    else{
        for(i=0;i<10;i++){
            aux_graba=fwrite(&ppm[i],sizeof(ppm[i]),1,f);
            if(aux_graba==1)
                aux_graba=fwrite(&temp[i],sizeof(temp[i]),1,f);
            if(aux_graba==1){
                printf("\nArchivo grabado correctamente\n");
                j++;
            }
            else{
                printf("\nError al grabrar\n\n");
                exit(2);
            }
        }
        printf("Se guardaron %d mediciones\n",j);
        if (fclose(f)!=0){
            printf("Error al cerrar el archivo");
            exit(3);
        }
    }
    return 0;
}
