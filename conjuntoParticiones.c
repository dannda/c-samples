//
//  main.c
//  ParticionesConjunto
//
//  Created by Dann on 13/10/14.
//
// Recibe de entrada la cantidad de elementos de un conjunto
// y calcula recursivamente las particiones del conjunto

#include <stdio.h>

int a[10],c=0,n,k=0;

void impresion(){
    int i,j;
    k++;
    for(i=0;i<n;i++){
        if(a[i]==i){
            printf("{");
            for( j=i;j<n;j++){
                if(a[j]==i)printf("%d",j+1);
            }
            printf("}");
        }
    }
    printf("\n");

}

void particion(){
    int i;
    for(i=0;i<=c;i++){
        if(a[i]==i||i==c){
            a[c++]=i;
            if(c==n) impresion();else particion();
            c--;
        }
    }
}

int main(){
    printf("n: ");
    scanf("%d",&n);
    particion();
    printf("Particiones de %d elementos: %d\n",n,k);
}
