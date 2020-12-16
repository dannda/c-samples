//
//  main.c
//  PuntoFlotante
//
// Evalúa si una entrada es una expresión correcta de un número de punto flotante

#include <stdio.h>

typedef enum{false,true} bool;
bool neg=false;
bool negf=false;


int columna(char c){
    if(c=='-'){
        return 0;
    }
    if(c>='0'&&c<='9'){
        return 1;
    }
    if(c=='.'){
        return 2;
    }
    if(c=='e'||c=='E'){
        return 3;
    }
    return -1;
}

float acum1,acum2;

int entrada(char *s){
    int t[8][4]={{1,2,3,-1},{-1,2,3,-1},{-1,2,3,5},{-1,4,-1,-1},{-1,4,-1,5},{6,7,-1,-1},{-1,7,-1,-1},{-1,7,-1,-1}};
    int e=0,c=0,eant;
    while(*s&&e!=-1){
        c=columna(*s);
        if(c==-1){
            e=-1;
            break;
        }
        else{
            eant=e;
            e=t[e][c];
            
            if(e==1){
                neg=true;
            }
            if(e==6){
                negf=true;
            }
            
            if((eant==0||eant==1)&&e==2){
                acum1=*s-'0';
            }
            if(eant==2&&e==2){
                acum1=(acum1*10)+*s-'0';
            }
            
            if(eant==3&&e==4){
                acum2=*s-'0';
            }
            if(eant==4&&e==4){
                acum2=(acum2*10)+*s-'0';
            }
            
            s++;
        }
    }
    if(e==-1&&e!=2&&e!=4&&e!=7){
        //printf("%d",e);
        printf("Expresión no válida\n");
    }
    else{
        printf("Expresión válida\n");
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    char s[30];
    printf("Ingresa número de punto flotante\n");
    scanf("%s",s);
    entrada(s);
    
    printf("%.f.%.f",acum1,acum2);
    
    
    
}

