//
//  main.c
//  LineasRectas
//
//  Created by Dann on 19/08/14.
//
// Encuentra la intersección entre dos líneas rectas
// dadas como entrada de la forma "ax+by+c=0"

#include <stdio.h>

int cont=1,x1,x2,ye1,y2,c1,c2,acum,eant;
typedef enum { false, true } bool;
bool neg=false;
bool cor=true;

int columna(char c){
    if(c=='+'||c=='-'){
        if(c=='-'){
            neg=true;
        }
        return 0;
    }
    if(c=='0'){
        return 5;
    }
    if(c>='0'&&c<='9'){
        return 1;
    }
    if(c=='x'){
        return 2;
    }
    if(c=='y'){
        return 3;
    }
    if(c=='='){
        return 4;
    }
    return -1;
}

int rectaOK(char *s){
    int t[7][6]={{1,2,3,4,-1,2},{-1,2,3,4,-1,2},{1,2,3,4,5,2},{1,-1,-1,-1,5,-1},{1,-1,-1,-1,5,-1},{-1,-1,-1,-1,-1,6},{-1,-1,-1,-1,-1,-1}};
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
            
            if((eant==0||eant==1)&&e==2){
                acum=*s-'0';
                if(neg==true){
                    acum=acum*-1;
                    neg=false;
                }
            }
            if(eant==2&&e==2){
                acum=(acum*10)+*s-'0';
            }
            if((eant==1&&(e==3||e==4))||(eant==0&&(e==3||e==4))){
                if(neg==true){
                    acum=-1;
                    neg=false;
                }
                else{
                    acum=1;
                }
            }
            if(e==3){
                if(cont==1){
                    x1+=acum;
                }
                else{
                    x2+=acum;
                }
            }
            if(e==4){
                if(cont==1){
                    ye1+=acum;
                }
                else{
                    y2+=acum;
                }
            }
            if(eant==2&&(e==1||e==5)){
                if(cont==1){
                    c1+=acum;
                }
                else{
                    c2+=acum;
                }
            }
            
            s++;
        }
    }
    if(e!=6){
        cor=false;
    }
    return e==6;
};

int main(int argc, const char * argv[])
{
    char s[30];
    printf("Ingresar recta 1 (ax+by+c=0)\n");
    scanf("%s",s);
    rectaOK(s);
    
    cont++;
    
    printf("Ingresar recta 2 (ax+by+c=0)\n");
    scanf("%s",s);
    rectaOK(s);
    
    printf("x1: %d\ty1: %d\tc1: %d\n",x1,ye1,c1);
    
    printf("x2: %d\ty2: %d\tc2: %d\n",x2,y2,c2);
    
    if(cor==true){
    
        double x=(((-1*c1*y2)-(-1*c2*ye1))/((x1*y2)-(x2*ye1)));
        double y=(((x1*-1*c2)-(x2*-1*c1))/((x1*y2)-(x2*ye1)));
    
        printf("Intersección: P(%f,%f)",x,y);
        
    }
    else{
        printf("Expresión invalida\n");
    }
    
    
}

