/*9. Implemente la siguiente función para calcular el producto escalar de dos vectores:
double prod_esc (const double *a, const double *b, int n);
Donde a y b apuntan a vectores de longitud n.
La función debe retornar a[0]*b[0]+a[1]*b[1]+ … + a[n-1]*b[n-1]
Usar notación aritmética de punteros (no subíndices []) para recorrer los vectores.*/
# include <stdio.h>
# include <stdlib.h>

double prod_esc (const double *a, const double *b, int n){
    double prod [n];
    double res;
    int i;
    for(i=0;i<n;i++){
        *(prod+i)=*(a+i) * *(b+i);
    }
    for(i=0;i<n;i++){
    printf("%.2f -->",*(prod+i));
    }
    printf("\n");
    for(i=0;i<n;i++){
        res+=*(prod+i);
    }
    return res;
}
int main (){
    double resultado;
    const double vec1 []={2.5,3,5.5};
    const double vec2 []={6.5,9.9,10.5};
    resultado=prod_esc(vec1,vec2,3);
    printf("El producto escalar es: %.2f",resultado);
    return 0;
}
