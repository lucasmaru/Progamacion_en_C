/*Suponga que primero, ultimo y medio son punteros del mismo tipo y
primero y ultimo apuntan al primer y último elemento de un vector. Si quiere
que medio apunte al elemento que está en la mitad del vector ¿por qué la siguiente
instrucción es inválida y cómo se podría solucionar?
medio = (primero + ultimo) / 2  */
# include <stdio.h>
# include <stdlib.h>
# define tam 5
int main (){
    int v[tam]={10,20,30,40,50};
    int *p, *u, *m;
    int h;
    p=v;
    u=(v+(tam-1));
    printf("p vale:%p y apunta a:%d \n",p,*p);
    printf("u vale:%p y apunta a:%d \n",u,*u);
    h=(u-p)+1;
    printf("h vale:%d \n",h);
    m=&h;
    printf("m vale:%p y apunta a:%d \n",m,*m);
    return  0;
}