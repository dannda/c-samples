//
//  main.c
//  ExpresionesParen
//  17/09/2014

// Obtiene una expresión de entrada en notación infija
// y la traduce a posfija
// símbolos de entrada del alfabeto, no numéricos

#include <stdio.h>
#include <ctype.h>

int contp=0;

int columna(char c){
    if(isalpha(c)){
        return 0;
    }
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='%'){
        return 1;
    }
    if(c=='('){
        contp++;
        return 2;
    }
    if(c==')'){
        contp--;
        return 3;
    }
    return -1;
}

int entrada(char *s){
    int t[2][4]={{1,-1,0,-1},{-1,0,-1,1}};
    int e=0,c=0;
    while(*s&&e!=-1){
        c=columna(*s);
        if(c==-1){
            return -1;
        }
        else{
            e=t[e][c];
            s++;
        }
    }
    if(e!=1||contp!=0){
        return -1;
    }
    return 0;
}

int fila(char c){
    if(c=='('){
        return 0;
    }
    if(c=='*'||c=='/'||c=='%'){
        return 1;
    }
    if(c=='+'||c=='-'){
        return 2;
    }
    if(c==')'){
        return 3;
    }
    return -1;
}

char pila[10]={0},i=0,j=0;
char* aposfija(char *s){
    static char resultado[32];
    int trad[3][2]={{3,0},{2,2},{1,1}};
    
    while(*s){
        
        if(isalpha(*s)){
            resultado[j]=*s;
            j++;
        }
        else if(*s!=')'){
            if(i==0){
                pila[i]=*s;
                i++;
            }
            else{
                
                while(i>0&&((trad[fila(pila[i-1])][1])>=trad[fila(*s)][0])){
                    resultado[j]=pila[i-1];
                    j++;
                    pila[i-1]=0;
                    i--;
                }
                //PRIORIDAD DE SALIDA DEL TOPE DE LA PILA ES MENOR A LA PRIORIDAD DE ENTRADA DEL OPERADOR
                pila[i]=*s;
                i++;
            }
        }
        else if(*s==')'){
            while(pila[i-1]!='('){
                resultado[j]=pila[i-1];
                j++;
                pila[i-1]=0;
                i--;
            }
            pila[i-1]=0;
            if(i>0){
                i--;}
        }
        s++;
    }
    for(i=10;i>=0;i--){
        if(pila[i]!=0&&pila[i]!='\n'&&pila[i]!='\r'){
            resultado[j]=pila[i];
            j++;
        }
    }
    
    return resultado;
}

int main(int argc, const char * argv[])
{
    char s[30];
    printf("Ingresar expresion: ");
    scanf("%s",s);
    printf("\n");
    
    if(entrada(s)==-1){
        printf("Expresión inválida\n");
        return 0;
    }
    else{
        printf("Expresión válida\n");
    }
    
    printf("Posfija: %s\n",aposfija(s));
    
    
}

