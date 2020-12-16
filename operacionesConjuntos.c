//
//  main.c
//  ConjuntosLE
//
//  Created on 28/08/14.
//
// Recibe dos conjutos en forma {a,b,c}
// Evalúa unión, intersección y resta
// Los resultados los ingresa como nodos con apuntadores e imprime

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct nodo{
    int clave;
    struct nodo *sig;
} NODO;

NODO *inicio=NULL;

void alta(int valor){
    NODO *previo,*actual,*nuevo;
    previo=NULL;
    actual=inicio;
    while(actual && actual->clave<valor){
        previo=actual;
        actual=actual->sig;
    }
    if(actual && actual->clave==valor){
        //printf("La clave ya existe\n");
    }
    else{
        nuevo=(NODO *)malloc(sizeof(NODO)); //toma memoria (new en C++)
        nuevo->clave=valor;
        nuevo->sig=actual;
        if(previo){
            previo->sig=nuevo;
        }
        else{
            inicio=nuevo;
        }
    }
}

void libera(){
    NODO *previo;
    while(inicio){
        previo=inicio;
        inicio=inicio->sig;
        free(previo);
    }
}

void reporte(){
    NODO *actual;
    actual=inicio;
    printf("{");
    while(actual){
        printf("%c",actual->clave);
        actual=actual->sig;
        if(actual!=NULL){
            printf(",");
        }
    }
    printf("}\n");
}

int columna(char c){
    if(c=='{'){
        return 0;
    }
    else if(isalpha(c)){
        return 1;
    }
    else if(c==','){
        return 2;
    }
    else if(c=='}'){
        return 3;
    }
    return -1;
}

int entrada(char *s){
    int t[5][4]={{1,-1,-1,-1},{-1,3,-1,2},{-1,-1,-1,-1},{-1,-1,4,2},{-1,3,-1,-1}};
    int e=0,c=0;
    while(*s&&e!=-1){
        c=columna(*s);
        e=t[e][c];
        
        s++;
    }
    if(e!=2){
        printf("Entrada invalida\n");
        return -1;
    }
    return 0;
}

int main(int argc, const char * argv[])
{

    int c1[52] = {0};
    int c2[52] = {0};
    
    char s1[41] = {'\0'},s2[41] = {'\0'};
    
    printf("Ingresar primer conjunto en forma {a,b,c}\n");
    scanf("%40[a-zA-Z{},]s",s1);
    
    getchar();
    
    printf("Ingresar segundo conjunto en forma {a,b,c}\n");
    scanf("%40[a-zA-Z{},]s",s2);
    
    // Tenemos guardadas las cadenas en este punto, ahora las reduciremos
    if(entrada(s1)==-1||entrada(s2)==-1){
        printf("Fin del programa\n");
        return 0;
    }
    
    //Entrada valida
    for(int i = 0; i < 41; i++){
        if( (int)s1[i] >= 65 && (int)s1[i] <= 122){
            c1[(int)s1[i]-65]=1;
        }
    }
    for(int i = 0; i < 41; i++){
        if( (int)s2[i] >= 65 && (int)s2[i] <= 122){
            c2[(int)s2[i]-65]=1;
        }
    }
    
    printf("Interseccion:\n");
    for(int i=0;i<=52;i++){
        if(c1[i]==1&&c2[i]==1){
            alta(i+65);
        }
    }
    reporte();
    libera();
    printf("\nUnion:\n");
    for(int i=0;i<=52;i++){
        if(c1[i]==1||c2[i]==1){
            alta(i+65);
        }
    }
    reporte();
    libera();
    printf("\nResta primer conjunto-segundo conjunto\n");
    for(int i=0;i<=52;i++){
        if((c1[i]==1&&c2[i]!=1)){
            alta(i+65);
        }
    }
    reporte();
    libera();
    printf("\nResta segundo conjunto-primer conjunto\n");
    for(int i=0;i<=52;i++){
        if((c1[i]!=1&&c2[i]==1)){
            alta(i+65);
        }
    }
    
    reporte();
    libera();
    printf("\n");

    
}

