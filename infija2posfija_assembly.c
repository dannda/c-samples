//
//  main.c
//  ExpresionesParen
//
//  08/12/14
//
// Traduce una expresión de entrada en notación infija a posfija
// La expresión de entrada debe estar escrita con símbolos del alfabeto, no numéricos
// Genera el código en ensamblador que pide el valor de las variables
// Y evalúa la expresión

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

static char resultado[32];

char pila[10]={0},i=0,j=0;
char* aposfija(char *s){
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
    
    printf("Posfija: %s\n\n",aposfija(s));
    
    int c1[52]={0};
    for (int i=0;i<30;i++){
        if((int)s[i]>=65 && (int)s[i]<=122){
            c1[(int)s[i]-65]=1;
        }
    }
    
    FILE *fp;
    fp=fopen("expre.asm","w");
    fprintf(fp,";infija: %s\n",s);
    fprintf(fp,";posfija: %s\n",resultado);
    fprintf(fp,"org 100h\n");
    fprintf(fp,"jmp main\n");
    
    //for variable
    for(int i=0;i<=52;i++){
        if(c1[i]==1){
            fprintf(fp,"%c  dw 0\n",i+65);
        }
    }
    fprintf(fp,"msglec  db 'Da el valor de '\n");
    fprintf(fp,"nomvar  db 0\n");
    fprintf(fp,"    db ':$'\n");
    fprintf(fp,"msgres  db 'El resultado es: $'\n");
    fprintf(fp,"buffer  db 6,0,6 dup(?)\n");
    
    
    fprintf(fp,"main:\n");
    for(int i=0;i<=52;i++){
        if(c1[i]==1){
            fprintf(fp,"    mov nomvar,'%c'\n",i+65);
            fprintf(fp,"    mov dx,offset msglec\n");
            fprintf(fp,"    mov ah,9\n");
            fprintf(fp,"    int 21h\n");
            fprintf(fp,"    call lecdec\n");
            fprintf(fp,"    mov %c,ax\n",i+65);
            fprintf(fp,"    call saltaren\n");
        }
    }
    
    //Operaciones
    for(int i=0;i<32;i++){
        if (isalpha(resultado[i])){
            fprintf(fp,"    push %c\n",resultado[i]);
        }
        if(resultado[i]=='+'){
            fprintf(fp,"    pop bx\n");
            fprintf(fp,"    pop ax\n");
            fprintf(fp,"    add ax,bx\n");
            fprintf(fp,"    push ax\n");
        }
        if(resultado[i]=='-'){
            fprintf(fp,"    pop bx\n");
            fprintf(fp,"    pop ax\n");
            fprintf(fp,"    sub ax,bx\n");
            fprintf(fp,"    push ax\n");
        }
        if(resultado[i]=='*'){
            fprintf(fp,"    pop bx\n");
            fprintf(fp,"    pop ax\n");
            fprintf(fp,"    mul bx\n");
            fprintf(fp,"    push ax\n");
        }
        if(resultado[i]=='/'){
            fprintf(fp,"    pop bx\n");
            fprintf(fp,"    pop ax\n");
            fprintf(fp,"    xor dx,dx\n");
            fprintf(fp,"    div bx\n");
            fprintf(fp,"    push ax\n");
        }
        if(resultado[i]=='%'){
            fprintf(fp,"    pop bx\n");
            fprintf(fp,"    pop ax\n");
            fprintf(fp,"    xor dx,dx\n");
            fprintf(fp,"    div bx\n");
            fprintf(fp,"    push dx\n");
        }
    }
    
    //Resultado
    fprintf(fp,"    mov dx,offset msgres\n");
    fprintf(fp,"    mov ah,9\n");
    fprintf(fp,"    int 21h\n");
    fprintf(fp,"    pop ax\n");
    //fprintf(fp,"    call impdec\n");
    //fprintf(fp,"    call saltaren\n");
    
    fprintf(fp,"impdec  proc near\n");
    fprintf(fp,"    push ax\n");
    fprintf(fp,"    push bx\n");
    fprintf(fp,"    push cx\n");
    fprintf(fp,"    push dx\n");
    fprintf(fp,"    mov bx,10\n");
    fprintf(fp,"    xor cx,cx\n");
    fprintf(fp,"impdec0:\n");
    fprintf(fp,"    xor dx,dx\n");
    fprintf(fp,"    div bx\n");
    fprintf(fp,"    add dl,'0'\n");
    fprintf(fp,"    push dx\n");
    fprintf(fp,"    inc cx\n");
    fprintf(fp,"    and ax,ax\n");
    fprintf(fp,"    jne impdec0\n");
    fprintf(fp,"impdec1:\n");
    fprintf(fp,"    pop dx\n");
    fprintf(fp,"    mov ah,2\n");
    fprintf(fp,"    int 21h\n");
    fprintf(fp,"    loop impdec1\n");
    fprintf(fp,"    pop dx\n");
    fprintf(fp,"    pop cx\n");
    fprintf(fp,"    pop bx\n");
    fprintf(fp,"    pop ax\n");
    fprintf(fp,"    ret\n");
    fprintf(fp,"impdec  endp\n");
    
    fprintf(fp,"saltaren    proc near\n");
    fprintf(fp,"    push ax\n");
    fprintf(fp,"    push dx\n");
    fprintf(fp,"    mov dl,13\n");
    fprintf(fp,"    mov ah,2\n");
    fprintf(fp,"    int 21h\n");
    fprintf(fp,"    mov dl,10\n");
    fprintf(fp,"    mov ah,2\n");
    fprintf(fp,"    int 21h\n");
    fprintf(fp,"    pop dx\n");
    fprintf(fp,"    pop ax\n");
    fprintf(fp,"    ret\n");
    fprintf(fp,"saltaren    endp\n");
    
    
    fprintf(fp,"lecdec  proc near\n");
    fprintf(fp,"    push bx\n");
    fprintf(fp,"    push cx\n");
    fprintf(fp,"    push dx\n");
    fprintf(fp,"    push si\n");
    fprintf(fp,"    mov dx,offset buffer\n");
    fprintf(fp,"    mov ah,0Ah\n");
    fprintf(fp,"    int 21h\n");
    fprintf(fp,"    mov si,offset buffer\n");
    fprintf(fp,"    inc si\n");
    fprintf(fp,"    mov cl,[si]\n");
    fprintf(fp,"    xor ch,ch\n");
    fprintf(fp,"    mov bx,10\n");
    fprintf(fp,"    xor ax,ax\n");
    fprintf(fp,"lecdec0:\n");
    fprintf(fp,"    inc si\n");
    fprintf(fp,"    mul bx\n");
    fprintf(fp,"    mov dl,[si]\n");
    fprintf(fp,"    sub dl,'0'\n");
    fprintf(fp,"    xor dh,dh\n");
    fprintf(fp,"    add ax,dx\n");
    fprintf(fp,"    loop lecdec0\n");
    fprintf(fp,"    pop si\n");
    fprintf(fp,"    pop dx\n");
    fprintf(fp,"    pop cx\n");
    fprintf(fp,"    pop bx\n");
    fprintf(fp,"    ret\n");
    fprintf(fp,"lecdec  endp\n");
    
    
    printf("\nexpre.asm generado\n");
    
    
}

