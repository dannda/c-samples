//
//  main.c
//  PolinomiosX
//
// El programa recibe dos polinomios de X
// en forma axb+cxd+...
// ej. x+3x2-5x3
// Y calcula la derivada e integral de cada uno
// Y la suma y multiplicación de ambos

#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true} bool;
bool x=false;
bool neg=false;

typedef struct nodo{
    int clave;
    int coeficiente;
    struct nodo *sig;
} NODO;

NODO *inicio1=NULL,*inicio2=NULL,*inicio3=NULL,*inicio4=NULL;

int columna(char c){
    if(c=='+'||c=='-'){
        return 0;
    }
    if(c>='0'&&c<='9'){
        return 1;
    }
    if(c=='x'){
        return 2;
    }
    return -1;
}

int entrada(char *s){
    int t[5][3]={{1,2,3},{-1,2,3},{1,2,3},{1,4,-1},{1,4,-1}};
    int e=0,c=0;
    while(*s&&e!=-1){
        c=columna(*s);
        if(c==-1){
            e=-1;
            printf("Expresión inválida\n");
            return 0;
        }
        else{
            e=t[e][c];
            //printf("%d\n",e);
            s++;
        }
    }
    if(e!=2&&e!=3&&e!=4){
        return -1;
    }
    return 0;
}

int cont=0;

void alta(int clave,int coeficiente,struct nodo *inicio){
    NODO *previo,*actual,*nuevo;
    previo=NULL;
    actual=inicio;
    while(actual && actual->clave!=clave){
        previo=actual;
        actual=actual->sig;
    }
    if(actual && actual->clave==clave){
        actual->coeficiente+=coeficiente;
    }
    else{
        nuevo=(NODO *)malloc(sizeof(NODO));
        nuevo->clave=clave;
        nuevo->coeficiente=coeficiente;
        //nuevo->sig=actual;
        actual=nuevo;
        
        if(previo){
            previo->sig=nuevo;
        }
        else{
            inicio=nuevo;
            if(cont==0){
                inicio1=inicio;
            }
            else if(cont==1){
                inicio2=inicio;
            }
            else if(cont==2){
                inicio3=inicio;
            }
            else if(cont==3){
                inicio4=inicio;
            }
        }
    }
}

void libera(){
    NODO *previo;
    while(inicio1){
        previo=inicio1;
        inicio1=inicio1->sig;
        free(previo);
    }
    while(inicio2){
        previo=inicio2;
        inicio2=inicio2->sig;
        free(previo);
    }
    while(inicio3){
        previo=inicio3;
        inicio3=inicio3->sig;
        free(previo);
    }
    while(inicio4){
        previo=inicio4;
        inicio4=inicio4->sig;
        free(previo);
    }
}

void derivada(){
    NODO *actual;
    actual=inicio1;
    printf("Derivada primer polinomio:\n");
    while(actual&&actual->coeficiente!=0){
        if(actual!=inicio1&&(actual->coeficiente*actual->clave)>=0){
            printf("+");
        }
        if(actual->clave!=0){
            printf("%d",(actual->clave*actual->coeficiente));
            if((actual->clave-1)>0){
                if((actual->clave-1)==1){
                    printf("x");
                }
                else{
                    printf("x%d",actual->clave-1);}
            }
        }
        else{
            printf("0");
        }
        actual=actual->sig;
    }
    printf("\n");
    
    actual=inicio2;
    printf("Derivada segundo polinomio:\n");
    while(actual&&actual->coeficiente!=0){
        if(actual!=inicio2&&(actual->coeficiente*actual->clave)>=0){
            printf("+");
        }
        if(actual->clave!=0){
            printf("%d",(actual->clave*actual->coeficiente));
            if((actual->clave-1)>0){
                if((actual->clave-1)==1){
                    printf("x");
                }
                else{
                    printf("x%d",actual->clave-1);}
            }
        }
        else{
            printf("0");
        }
        actual=actual->sig;
    }
    printf("\n");
    
}

void integral(){
    NODO *actual;
    actual=inicio1;
    printf("Integral primer polinomio:\n");
    while(actual){
        if(actual->coeficiente!=0){
        if(actual!=inicio1&&actual->coeficiente>=0){
            printf("+");
        }
        if(actual->coeficiente%(actual->clave+1)==0){
            if((actual->coeficiente/(actual->clave+1))!=1){
                printf("%d",actual->coeficiente/(actual->clave+1));
            }
        }
        else{
            printf("%d/%d",actual->coeficiente,actual->clave+1);
        }
        if(actual->clave+1!=1){
            printf("x%d",actual->clave+1);}
        else{
            printf("x");
            }
        }
        actual=actual->sig;
    }
    printf("\n");
    
    
    actual=inicio2;
    printf("Integral segundo polinomio:\n");
    while(actual){
        if(actual->coeficiente!=0){
            if(actual!=inicio2&&actual->coeficiente>=0){
                printf("+");
            }
            if(actual->coeficiente%(actual->clave+1)==0){
                if((actual->coeficiente/(actual->clave+1))!=1){
                    printf("%d",actual->coeficiente/(actual->clave+1));
                }
            }
            else{
                printf("%d/%d",actual->coeficiente,actual->clave+1);
            }
            if(actual->clave+1!=1){
                printf("x%d",actual->clave+1);}
            else{
                printf("x");
            }
        }
        actual=actual->sig;
    }
    printf("\n");
}


void suma(){
    NODO *actual;
    actual=inicio1;
    cont++;
    while(actual&&actual->coeficiente!=0){
        alta(actual->clave,actual->coeficiente,inicio3);
        actual=actual->sig;
    }
    
    actual=inicio2;
    while(actual&&actual->coeficiente!=0){
        alta(actual->clave,actual->coeficiente,inicio3);
        actual=actual->sig;
    }
    
}


void multiplicacion(){
    NODO *actual,*actual2;
    actual=inicio1;
    cont++;
    while(actual&&actual->coeficiente!=0){
        actual2=inicio2;
        while(actual2&&actual2->coeficiente!=0){
            alta(((actual->clave)+(actual2->clave)),((actual->coeficiente)*(actual2->coeficiente)),inicio4);
            actual2=actual2->sig;
        }
        actual=actual->sig;
    }
}


void reporte(){
    NODO *actual;
    actual=inicio1;
    printf("Primer polinomio:\n");
    while(actual&&actual->coeficiente!=0){
        if(actual!=inicio1&&actual->coeficiente>0){
            printf("+");
        }
        printf("%dx",actual->coeficiente);
        printf("%d",actual->clave);
        actual=actual->sig;
    }
    
    printf("\n");
    
    actual=inicio2;
    printf("Segundo polinomio:\n");
    while(actual){
        if(actual!=inicio2&&actual->coeficiente>0){
            printf("+");
        }
        printf("%dx",actual->coeficiente);
        printf("%d",actual->clave);
        actual=actual->sig;
    }
    printf("\n");
}

void reportesuma(){
    NODO *actual;
    actual=inicio3;
    printf("Suma de polinomios:\n");
    while(actual&&actual->coeficiente!=0){
        if(actual!=inicio3&&actual->coeficiente>0){
            printf("+");
        }
        printf("%d",actual->coeficiente);
        if(actual->clave>1){
            printf("x%d",actual->clave);
        }
        else if(actual->clave==1){
            printf("x");
        }
        actual=actual->sig;
    }
}

void reportemul(){
    NODO *actual;
    actual=inicio4;
    printf("Multiplicación de polinomios:\n");
    while(actual&&actual->coeficiente!=0){
        if(actual!=inicio4&&actual->coeficiente>0){
            printf("+");
        }
        printf("%d",actual->coeficiente);
        if(actual->clave>1){
            printf("x%d",actual->clave);
        }
        else if(actual->clave==1){
            printf("x");
        }
        actual=actual->sig;
    }
}

int main(int argc, const char * argv[])
{
    printf("Polinomios de x\n");

    char s[30],s2[30];
    printf("Ingresa primer polinomio en forma axb+cxd+...\n");
    scanf("%s",s);
    if(entrada(s)==-1){
        printf("Expresión inválida\n");
        return 0;
    }
    printf("Ingresa segundo polinomio en forma axb+cxd+...\n");
    scanf("%s",s2);
    if(entrada(s2)==-1){
        printf("Expresión inválida\n");
        return 0;
    }
    
    int acum=0,potencia=0;
    for(int i=0;i<30;i++){
        if(s[i] && s[i]!='\377'){
            if(s[i]=='-'){
                neg=true;
            }
            if(s[i]>='0'&&s[i]<='9'){
                if(x==false){
                    if(s[i-1]&&s[i-1]>='0'&&s[i-1]<='9'){
                        acum=acum*10+(s[i]-'0');
                    }
                    else{acum+=s[i]-'0';}
                }
                else{
                    if(s[i-1]&&s[i-1]>='0'&&s[i-1]<='9'){
                        potencia=potencia*10+(s[i]-'0');
                    }
                    else{potencia+=s[i]-'0';}
                }
                    
            }
            if(s[i]=='x'){
                x=true;
            }
            if(s[i+1]=='+'||s[i+1]=='-'||!s[i+1]||s[i+1]=='\377'){
                if(x==true&&acum==0){
                    acum=1;
                    if(neg==true){
                        acum=acum*-1;
                        neg=false;
                    }
                }
                if(neg==true){
                    acum=acum*-1;
                    neg=false;
                }
                if(x==true&&potencia==0){
                   potencia=1;
                }
                
                alta(potencia,acum,inicio1);
                x=false;
                acum=0;
                potencia=0;
            }
        }
    }
    acum=0;
    potencia=0;
    x=false;
    cont++;
    for(int i=0;i<30;i++){
        if(s2[i] && s2[i]!='\377'){
            if(s2[i]=='-'){
                neg=true;
            }
            if(s2[i]>='0'&&s2[i]<='9'){
                if(x==false){
                    if(s2[i-1]&&s2[i-1]>='0'&&s2[i-1]<='9'){
                        acum=acum*10+(s2[i]-'0');
                    }
                    else{acum+=s2[i]-'0';}
                }
                else{
                    if(s2[i-1]&&s2[i-1]>='0'&&s2[i-1]<='9'){
                        potencia=potencia*10+(s2[i]-'0');
                    }
                    else{potencia+=s2[i]-'0';}
                }
                
            }
            if(s2[i]=='x'){
                x=true;
            }
            if(s2[i+1]=='+'||s2[i+1]=='-'||!s2[i+1]||s2[i+1]=='\377'){
                if(x==true&&acum==0){
                    acum=1;
                    if(neg==true){
                        acum=acum*-1;
                        neg=false;
                    }
                }
                if(neg==true){
                    acum=acum*-1;
                    neg=false;
                }
                if(x==true&&potencia==0){
                    potencia=1;
                }
                
                if(acum!=0){
                    alta(potencia,acum,inicio2);}
                x=false;
                acum=0;
                potencia=0;
            }
        }
    }
    
    printf("\n");
    reporte();
    printf("\n");
    derivada();
    printf("\n");
    integral();
    printf("\n");
    suma();
    reportesuma();
    printf("\n");
    printf("\n");
    multiplicacion();
    reportemul();
    printf("\n");
    libera();
    
}
