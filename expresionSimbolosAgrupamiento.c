//
//  main.c
//  ParentesisLlavesCorchetes
//  12/09/14
//
// Recibe de entrada una expresión con agrupamiento por
// paréntesis, llaves o corchetes
// y evalúa si la expresión está balanceada
// (abre y cierra correctamente los símbolos)

#include <stdio.h>
#include <stdlib.h>

int pila[10]={0};
int i=9;
//1 parentesis, 2 llave, 3 corchete

int entrada(char *s){
    while(*s){
        if(*s=='('){
            pila[i]=1;
            i--;
        }
        if(*s=='{'){
            pila[i]=2;
            i--;
        }
        if(*s=='['){
            pila[i]=3;
            i--;
        }
        
        if(*s==')'||*s=='}'||*s==']'){
            int j=0;
            while(pila[j]==0){
                j++;
            }
            if(*s==')'){
                if(pila[j]==1){
                    pila[j]=0;
                }
                else{
                    return -1;
                }
            }
            if(*s=='}'){
                if(pila[j]==2){
                    pila[j]=0;
                }
                else{
                    return -1;
                }
            }
            if(*s==']'){
                if(pila[j]==3){
                    pila[j]=0;
                }
                else{
                    return -1;
                }
            }
        }
        s++;
    }
    i=0;
    for(int j=0;j<10;j++){
        if(pila[j]!=0){
            i=1;
        }
    }
    if(i==0){
        return 0;
    }
    else{
        return -1;
    }
}

int main(int argc, const char * argv[])
{

    char s[30];
    printf("Ingresar cadena: ");
    scanf("%s",s);
    printf("\n");
    
    if(entrada(s)==-1){
        printf("Expresión no balanceada\n");
        return 0;
    }
    else{
        printf("Expresión balanceada\n");
    }
    
}

