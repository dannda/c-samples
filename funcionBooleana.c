//
//  main.c
//  comb
//  10/10/14
//
// Recibe una expresión de una función booleana en notación infija
// La traduce a posfija
// E imprime la tabla de verdad para dicha función

#include <stdio.h>
#include <ctype.h>
#include <math.h>
// ¬ -> -
// ^ -> *
// v -> +
// => -> >
int contp=0;

int columna(char c){
    if(isalpha(c)){
        return 0;
    }
    if(c=='+'||c=='-'||c=='*'||c=='>'||c=='='){
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
    int t[2][4]={{1,0,0,-1},{-1,0,-1,1}};
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
    if(c=='-'){
        return 1;
    }
    if(c=='*'){
        return 2;
    }
    if(c=='+'){
        return 3;
    }
    if(c=='>'){
        return 4;
    }
    if(c=='='){
        return 5;
    }
    if(c==')'){
        return 6;
    }
    return -1;
}

static char resultado[32];
char pila[10]={0},i=0,j=0;
char* aposfija(char *s){
    int trad[6][2]={{7,0},{6,5},{4,4},{3,3},{2,2},{1,1}};
    
    while(*s){
        if(isalpha(*s)){
            resultado[j]=*s;
            j++;
        }
        else if(*s!=')'){
            if (i==0){
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

int comb(int a,int b,char c){
    if(c=='*'){
        if(a==1&&b==1){
            return 1;
        }
        return 0;
    }
    if(c=='+'){
        if(a==1||b==1){
            return 1;
        }
        return 0;
    }
    if(c=='>'){
        if(a==b||a<b){
            return 1;
        }
        return 0;
    }
    if(c=='='){
        if(a==b){
            return 1;
        }
        return 0;
    }
    return -1;
}

int main(int argc, const char * argv[]) {
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
    
    printf("Posfija: %s\n\n",aposfija(s));
    
    char h[30];
    int e=0,k=0,contv=0;
    for(i=0;i<30;i++){
        if(isalpha(s[i])){
            for(int j=0;j<30;j++){
                if(s[i]==h[j]){
                    e=1;
                }
            }
            if(e==0){
                h[k]=s[i];
                k++;
                contv++;
            }
        }
    }
    
    int col=pow(2,contv);
    printf("variables: %d \n",contv);
    
    int m[col][contv+1];
    
    int bin[10];
    int n;
    
    for(i=0;i<col;i++){
        n=i;
        for(j=9;j>=0;j--){
            bin[j]=(n%2);
            n=n/2;
        }
        for(int k=0;k<10;k++){
        }
        for(j=0;j<contv;j++){
            m[i][j]=bin[9-(contv-1-j)];
        }
    }
    
    int v1=-1,v2=-1,r=-1,fila=0;
    
    while(fila<col){
        
    for(i=0;resultado[i];i++){
        if(isalpha(resultado[i])){
            for(j=0;j<30;j++){
                if(h[j]==resultado[i]){
                    if(v1==-1){
                        v1=m[fila][j];
                    }
                    else{
                        v2=m[fila][j];
                    }
                }
            }
        }
        else if(resultado[i]!='-'){
            if(v1!=-1&&v2==-1){
                v2=r;
            }
            r=comb(v1,v2,resultado[i]);
            v1=-1;
            v2=-1;
            
        }
        else if(resultado[i]=='-'){
            if(v2==-1&&v1!=-1){
                if(v1==1){
                    v1=0;
                }
                else{
                    v1=1;
                }
            }
            else if(v1!=-1&&v2!=-1){
                if(v2==1){
                    v2=0;
                }
                else{
                    v2=1;
                }
            }
            else{
                if(r==1){
                    r=0;
                }
                else{
                    r=1;
                }
            }
        }
    }
        m[fila][contv]=r;
        fila++;
    }
    
    for(i=0;i<30;i++){
        if(isalpha(h[i])){
            printf("%c ",h[i]);}
    }
    printf("R\n");
    for(i=0;i<col;i++){
        for(j=0;j<contv+1;j++){
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
}