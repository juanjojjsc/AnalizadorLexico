//
//  main.c
//  AnalizadorLexicoJ
//
//  Created by JJ Santos on 21/10/19.
//  Copyright © 2019 JJ Santos. All rights reserved.
//

#include "lexico.h"

//Estructura para cada elemento de la Lista Ligada
struct TablaSimbolos
{
    char type[20];
    char symbol[20];
    char value[20];
    int* addr;
    //Apuntador al siguiente elemento de la Lista Ligada
    struct TablaSimbolos *next;
};

//Apuntadores a primer y ultimo nodo de la Lista Ligada
struct TablaSimbolos *first,*last;
int size = 0;


int main(int argc, char **argv) {

    // Checar que si se haya pasado el argumento
    if (argc < 2) 
    {
        printf("\tFavor de pasar el nombre del programa a analizar como argumento.\n");
        printf("\tEjemplo: ./analizador programa.txt\n");
        exit(EXIT_FAILURE);
    }

    //Variables
    char ch; 
    char buffer[15];
    int j=0;
    int caracterSencilloFlag = 0;
    
    FILE *archivo;
    
    //Abrir Archivo
    archivo = fopen(argv[1],"r");
    if(archivo == NULL){
        printf("Error al abrir el programa.\n");
        exit(0);
    } else {
        printf("Abriendo el programa: %s\n\n",argv[1]);
    }
    
    
    //Leer todos los caracteres del archivo
    while((ch = fgetc(archivo)) != EOF){

        #ifdef DEBUG
            printf("Leyendo: %c\n",ch); 
        #endif


//////////////////////////////////////// CHECAR LOS TOKENS DE UN SOLO CARACTER, SIN CENTINELAS

        caracterSencilloFlag = esParentesis(ch);
        caracterSencilloFlag = esCorchete(ch);
        caracterSencilloFlag = esLlave(ch);
        caracterSencilloFlag = esBooleano(ch);




/////////////////////////////////////// CHECAR TOKENS ALFANUMERICOS CON SENTINELA

        //Mientras siga habiendo un caracter, seguir metiendo en el buffer

        //Exepciones Alfanumericas que podrian conformar Tokens de mas de un caracter
        if((isalnum(ch) || 
            ch == '=' || 
            ch == '<' || 
            ch == '>' || 
            ch == '+' || 
            ch == '-' || 
            ch == '*' ||
            ch == '.' || 
            ch == '/' ) && !caracterSencilloFlag){
            
            #ifdef DEBUG
                printf("Entro.  %c si fue alfanum, seguimos checando...\n",ch); 
            #endif
            //METEMOS LA BUFFER EL CARACTER QUE SIGUE, PARA VER SI YA ACABO CON UN ESPACIO
            //SEGUIMOS METIENDO HASTA ENCONTRAR UN ESPACIO
            buffer[j++] = ch;
            #ifdef DEBUG
                printf("Avanzamos el buffer, ahora Buffer tiene: %c\n",ch);
            #endif
            
        }
        //Cuando encuentra un espacio o terminador, terminar e identificar que fue el buffer
        else if((ch == ' ' || ch == '\n' || ch == ';') && (j != 0) && !caracterSencilloFlag){
            
            #ifdef DEBUG
                printf("Entro. Espacio Encontrado, determinar que fue\n");
            #endif

            //Le mete al buffer un EOL para indicar que ya encontro un espacio o terminador
            buffer[j] = '\0';
            j = 0;

            //HASTA QUE ENCUENTRA UN ESPACIO, ENTONCES SE ATREVE A DECIR QUE FUE LO QUE TERMINO SIENDO
            
            
            #ifdef DEBUG
                printf("Evaluando buffer: %s\n",buffer);
            #endif

            //Identificar el buffer utilizando funciones de evaluacion

            if(esPalabraReservada(buffer) == 1) 
                imprimirToken(buffer,"Palabra Reservada");
            else if (esRelacional(buffer)==1){
                //Que tipo de Operador Relacional es usando un automata de estados
                const char* token = automataOpRelacionales(buffer);
                //Imprimir el Token
                printf("<OP Relacional, %s>\n",token);
            }
            else if (esAritmetico(buffer)==1){
            
                imprimirToken(buffer,"Operador Aritmetico");
            }
            else if (esComentario(buffer)==1)
                imprimirToken(buffer,"Comentario");
            else if (!strcmp(buffer,"="))
                imprimirToken(buffer,"Asignacion");
            else if (esNumero(buffer)==1){
                const char* token = automataNumeros(buffer);
                //Imprimir el Token
                printf("<Tipo, %s>\n",token);
            }
            else {
                imprimirToken(buffer,"Identificador");
                insertarRegistro(buffer,"Identificador");
                imprimirTabla();
            } 
        
        }
        //Terminar la iteracion
        caracterSencilloFlag = 0;
        
    }
    //Cerrar Archivo
    fclose(archivo);
    
    return 0;
}

void insertarRegistro(char symbol[], char type[]){
    int n;
    //char l[20];
    // printf("\n\tEnter the symbol : ");
    // scanf("%s",l);
    n = buscaRegistro(symbol);
    if(n==1)
        printf("\n\tERROR: REGISTRO DUPLICADO\n");
    else
    {
        
        struct TablaSimbolos *p;

        p=malloc(sizeof(struct TablaSimbolos));
        strcpy(p->symbol,symbol);
        // printf("\n\tEnter the type : ");
        // scanf("%s",p->type);
        strcpy(p->type,type);
        // printf("\n\tEnter the value : ");
        // scanf("%s",p->value);
        // printf("\n\tEnter the address : ");
        // scanf("%d",&p->addr);
        //strcpy(p->addr,&p);
        // p->addr = &p;


        p->next=NULL;
        if(size==0)
        {
            first=p;
            last=p;
        }
        else
        {
            last->next=p;
            last=p;
        }

        size++;
    }
    #ifdef DDEBUG
        printf("\nINSERTADO\n");
    #endif
}

void imprimirTabla()
{
    int i;
    struct TablaSimbolos *p;
    p=first;
    #ifdef DDEBUG
        printf("Current Address: %p\n",&p);
    #endif
    // printf("\n\tTYPE\t\tSYMBOL\t\tADDRESS\t\t\tVALUE\n");
    printf("\n\tTYPE\t\t\tSYMBOL\t\t\tADDRESS\n");
    for(i=0;i<size;i++)
    {
        printf("\t%s\t\t%s\t\t%p\n",p->type,p->symbol,&p->next);
        p=p->next;
    }
}


int buscaRegistro(char symbol[])
{
    int i,flag=0;
    struct TablaSimbolos *p;
    p=first;
    for(i=0;i<size;i++)
    {
        if(strcmp(p->symbol,symbol)==0)
            flag=1;
        p=p->next;
    }
    return flag;
}
