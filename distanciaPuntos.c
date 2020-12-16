//
//  main.c
//  DistanciaEntrePuntos
//  02/09/14
//
// Obtiene de entrada dos puntos en forma (x,y)
// Calcula la distancia entre los dos puntos

#include <stdio.h>
#include <math.h>

int acum,eant,cont=0,x1,x2,ye1,y2;
typedef enum{false,true} bool;
bool coma=false;
bool neg=false;

int columna(char c){
    if(c=='('){
        return 0;
    }
    if(c=='-'){
        return 1;
    }
    if(c>='0'&&c<='9'){
        return 2;
    }
    if(c==','){
        return 3;
    }
    if(c==')'){
        return 4;
    }
    return -1;
}

int entrada(char *s){
    int t[7][5]={{1,-1,-1,-1,-1},{-1,2,3,-1,-1},{-1,-1,3,-1,-1},{-1,-1,3,4,-1},{-1,5,6,-1,-1},{-1,-1,6,-1,-1},{-1,-1,6,-1,7}};
    int e=0,c=0;
    while(*s &&e!=-1){
        c=columna(*s);
        if(c==-1){
            e=-1;
            printf("Expresión no válida\n");
            return 0;
        }
        else{
            eant=e;
            e=t[e][c];
            
            if(e==2||e==5){
                neg=true;
            }
            if((eant==2||eant==1)&&e==3){
                acum=*s-'0';
            }
            if((eant==5||eant==4)&&e==6){
                acum=*s-'0';
            }
            if((eant==3&&e==3)||(eant==6&&e==6)){
                acum=(acum*10)+*s-'0';
            }
            if(e==4){
                if(neg==true){
                    acum=acum*-1;
                    neg=false;
                }
                if(cont==0){
                    x1=acum;
                }
                else{
                    x2=acum;
                }
            }
            if(e==7){
                if(neg==true){
                    acum=acum*-1;
                    neg=false;
                }
                if(cont==0){
                    ye1=acum;
                }
                else{
                    y2=acum;
                }
            }
            s++;
        }
    }
    if(e!=7){
        printf("Entrada inválida\n");
        return -1;
    }
    return 0;
}

double distancia(int x1,int x2,int y1, int y2){
    return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}

int main(int argc, const char * argv[])
{
    char s[30];
    printf("Ingresa primer punto en forma (x,y)\n");
    scanf("%s",s);
    entrada(s);
    
    cont++;
    
    printf("Ingresa segundo punto en forma (x,y)\n");
    scanf("%s",s);
    entrada(s);
    
    printf("x1: %d\ty1: %d\n",x1,ye1);
    printf("x2: %d\ty2: %d\n",x2,y2);
    
    printf("Distancia: %f\n",distancia(x1,x2,ye1,y2));
    
    
}

