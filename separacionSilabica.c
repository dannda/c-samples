//
//  main.c
//  separacionSilabica
//
//  Audio por sílaba
// TODO: terminar esCV es VC
// Recibe una palabra de entrada y la separa por sílabas

#include <stdio.h>

int esVocal(char c){
    if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'){
        return 1;
    }
    return 0;
}

int esDi(char c,char c2){
    if(c=='i'||c=='u'){
        if(c2=='a'||c2=='e'||c2=='o'){
            return 1;
        }
    }
    return 0;
}

int esCD(char c,char c2){
    if((c=='t'||c=='b'||c=='c')&&(c2=='r'||c2=='l')){
        return 1;
    }
    return 0;
}

int consD(char c,char c2,char c3,char c4){
    if((c=='t'||c=='b'||c=='c')&&(c2=='r'||c2=='l')){
        if(esDi(c3,c4)){
            return 1;
        }
        else if(esVocal(c2)){
            return 1;
        }
    }
    return 0;
}

int esCVC(char c,char c2,char c3,char c4,char c5,char c6){
    if(esCD(c, c2)){
        if(esDi(c3, c4)){
            if(!esCD(c5, c6)){
                if(!esVocal(c5)&&!esVocal(c6)){
                    return 1;
                }
            }
        }
        if(esVocal(c3)){
            if(!esCD(c4, c5)){
                if(!esVocal(c4)&&!esVocal(c5)){
                    return 1;
                }
            }
        }
    }
    if(!esVocal(c)){
        if(esDi(c2, c3)){
            if(!esCD(c4,c5)){
                if(!esVocal(c4)&&!esVocal(c5)){
                    return 1;
                }
            }
        }
        if(esVocal(c2)){
            if(!esCD(c3, c4)){
                if(!esVocal(c3)&&!esVocal(c4)){
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

//TODO
int esCV(){
    return 0;
}

//TODO
int esVC(){
    return 0;
}

int main(int argc, const char * argv[]) {
    char palabra[30]={0};
    char silaba[10]={0};
    printf("Palabra: ");
    scanf("%[^(0-9\n)]s",palabra);
    //printf("%s\n",palabra);
    
    int j=0;
    for(int i=0;palabra[i];i++){
        if(i==0&&esVocal(palabra[i])&&!esVocal(palabra[i+1])&&(!palabra[i+2]||(!esVocal(palabra[i+2])&&!esVocal(palabra[i+3])))){
            silaba[j]=palabra[i];
            j++;
            silaba[j]=palabra[i+1];
            i++;
            printf("%s ",silaba);
            j=0;
        }
        else if(i==0&&esVocal(palabra[i])&&!esVocal(palabra[i+1])){
            silaba[j]=palabra[i];
            printf("%s ",silaba);
            j=0;
        }
        else if(!esVocal(palabra[i])){
            if(esVocal(palabra[i+1])&&!esVocal(palabra[i+2])&&esVocal(palabra[i+3])){
                silaba[j]=palabra[i];
                j++;
                silaba[j]=palabra[i+1];
                i++;
                printf("%s ",silaba);
                j=0;
            }
            else if(esVocal(palabra[i+1])&&!esVocal(palabra[i+2])&&(!palabra[i+3]||(!esVocal(palabra[i+3])))){
                silaba[j]=palabra[i];
                j++;
                silaba[j]=palabra[i+1];
                j++;
                silaba[j]=palabra[i+2];
                i++;
                i++;
                printf("%s ",silaba);
                j=0;
            }
            else if(!esVocal(palabra[i+1])&&esVocal(palabra[i+2])){
                silaba[j]=palabra[i];
                j++;
                silaba[j]=palabra[i+1];
                j++;
                silaba[j]=palabra[i+2];
                i++;
                i++;
                printf("%s ",silaba);
                j=0;
            }
        }
    }
}
