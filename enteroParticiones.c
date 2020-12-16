//
//  main.c
//  EnteroParticiones
//  07/12/14
//
// Recibe un número entero de entrada,
// obtiene sus particiones recursivamente 
// y las imprime

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void imprime(int n, int *a){
    int i;
    for(i=0;i<=n;i++){
        printf("%d",a[i]);
        if(i!=n){
            printf("+");
        }
    }
    printf("\n");
}

void particion(int n, int *a, int nivel){
    int prim,i;
    if(n<1)return;
    a[nivel]=n;
    imprime(nivel,a);
    prim=(nivel==0)?1:a[nivel-1];
    for(i=prim;i<=n/2;i++){
        a[nivel]=i;
        particion(n-i,a,nivel+1);
    }
}

int main(int argc, const char * argv[]) {
    int n;
    printf("Numero a particionar: ");
    scanf("%d",&n);
    int * a=(int *) malloc(sizeof(int)*n);
    particion(n,a,0);
    return 0;
}
