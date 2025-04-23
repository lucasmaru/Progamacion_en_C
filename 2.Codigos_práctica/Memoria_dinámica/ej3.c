/*3. Escriba la función duplicar que reserve memoria dinámicamente para duplicar un
string que se le pasa como argumento. Por ejemplo, la llamada:
p = duplicar (str);
debe reservar memoria para un string de la misma longitud que str, copiar los datos
y retornar un puntero a la nueva cadena de caracteres. Si la reserva de memoria falla,
entonces duplicar debe retornar un puntero nulo.*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
void mostrar (char* str, int a){
    printf("%s",str);
}
char* duplicar (char* str){
    int n;
    char* ptr;
    n=strlen(str);
    ptr=malloc(sizeof(char)*n);
    if(ptr==NULL){
        return ptr;
    }
    else
        strcpy(ptr,str);
        
}

int main (){
    char* pal_2;
    char pal_1 [10]="Lucas";
    pal_2=duplicar(pal_1);
    printf("%s",pal_2);

    
    return 0;
}