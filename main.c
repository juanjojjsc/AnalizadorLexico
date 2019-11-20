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
    int addr;
    //Apuntador al siguiente elemento de la Lista Ligada
    struct TablaSimbolos *next;
};

struct Entrada 
{
    int token;
    char* valor;
    char simbolo;
};


struct Entrada daToken();


int fileIndex = 0;

//Apuntadores a primer y ultimo nodo de la Lista Ligada
struct TablaSimbolos *first,*last;
int size = 0;

//Variables
char ch;
int next = 0;
char input[15]; 
char buffer[15];
char data[255];
int j=0;
int caracterSencilloFlag = 0;
int idNumero = 1;
int fileLenght = 0;
int bufferSize = 0;

struct Entrada miToken;


char tokens[8][20] = {
                        "PalabraReservada",
                        "Tipo",
                        "Funcion",
                        "Identificador",
                        "OperadorAritmetico",
                        "OperadorRelacional",
                        "OperadorAsignacion",
                        "Simbolo"
                    };
    


int main(int argc, char **argv) {

    // Checar que si se haya pasado el argumento
    if (argc < 2) 
    {
        printf("\tFavor de pasar el nombre del programa a analizar como argumento.\n");
        printf("\tEjemplo: ./analizador programa.txt\n");
        exit(EXIT_FAILURE);
    }

    
    
    FILE *archivo;
    
    //Abrir Archivo
    archivo = fopen(argv[1],"r");
    if(archivo == NULL){
        printf("Error al abrir el programa.\n");
        exit(0);
    } else {
        printf("Abriendo el programa: %s\n\n",argv[1]);
    }

    // for (int i = 0; i < 50; i++)
    // {
    //     // if(data[i] == '')
    //     fscanf(archivo, "%c", &data[i]);
    // }

    // for (int i = 0; i < 50; i++)
    // {
    //     printf("data: %c\n", data[i]);
    // }

    
    
    while((fscanf(archivo, "%c", &data[fileLenght])) != EOF) {
        printf("Data[%d]: %c\n",fileLenght,data[fileLenght]);
        fileLenght++;
    }

    data[fileLenght] = EOF;

    for (int i=0; i<fileLenght+1; i++)
        printf("%c",data[i]);

    //Cerrar Archivo
    fclose(archivo);



    printf("File Lenght: %d\n",fileLenght);
    
    // //Leer todos los caracteres del archivo
    // while((ch = fgetc(archivo)) != EOF){


        
        
    // }


    
    // for (int i=0; i<fileLenght; i++) {
    //     miToken = daToken();
    //     printf("\tTOKEN: %d\n\tVALOR: %c\n",miToken.token,miToken.simbolo);
    // }

    
    

    miToken = daToken();
    printf("\tTOKEN: %d\n\tVALOR: %s\n\tSIMBOLO: %c\n",miToken.token,miToken.valor,miToken.simbolo);

    miToken = daToken();
    printf("\tTOKEN: %d\n\tVALOR: %s\n\tSIMBOLO: %c\n",miToken.token,miToken.valor,miToken.simbolo);

    miToken = daToken();
    printf("\tTOKEN: %d\n\tVALOR: %s\n\tSIMBOLO: %c\n",miToken.token,miToken.valor,miToken.simbolo);

    
    
    return 0;
}






struct Entrada daToken() {

    #ifdef DEBUG
            printf("Leyendo: %c\n",ch); 
        #endif

    struct Entrada e;

        

        //Si es un punto y coma
        if ( data[fileIndex] == ';') {
            printf("Encontramos punto y coma\n");
            fileIndex++;
        }

        //Si es un espacio
        if ( data[fileIndex] == ' ') {
            printf("Encontramos espacio\n");
            fileIndex++;
        }

        //Si es una NUEVA LINEA
        if ( data[fileIndex] == '\n') {
            printf("Encontramos nueva linea\n");
            fileIndex++;
        }

        // Si ya se acabo el file
        if (data[fileIndex] == EOF) {
            printf("\n\tEOF\n");
            struct Entrada failed;
            failed.token = -1;
            return failed;
        }
        

        printf("Entrando a daToken con indice: %d\n", fileIndex);
        printf("Vamos a checar: %c\n", data[fileIndex]);


//////////////////////////////////////// CHECAR LOS TOKENS DE UN SOLO CARACTER, SIN CENTINELAS

        caracterSencilloFlag = 0;
        caracterSencilloFlag = esSimbolo(data[fileIndex]);
        if (caracterSencilloFlag) {
            printf("Caracter Sencillo encontrado\n");

            


            printf("Vamos a guardar: %c\n", data[fileIndex]);
            
            //convert the char to string
            //char simbol = data[fileIndex];
            
            // char str[1];
            // str[0] = simbol;
            //strcpy(str,data[fileIndex]);

            //printf("converted: %c\n",str[0]);
            // LOAD DATA
            //token num 8 es Simbolos 
            e.token = 8;
            // strcpy(e.valor,str);
            e.simbolo = data[fileIndex];
            e.valor = "-";


            printf("Guardamos token: %d\n", e.token);
            printf("Guardamos simbolo: %c\n", e.simbolo);
           
            //Incrementar el indice en cada pasada
            fileIndex++;
            
            return e;
        }



    /////////////////////////////////////// CHECAR TOKENS ALFANUMERICOS CON SENTINELA

    while(fileIndex < fileLenght) {

        if(data[fileIndex] == EOF)
            break;

        //Exepciones Alfanumericas que podrian conformar Tokens de mas de un caracter
        if((isalnum(data[fileIndex]) || 
            data[fileIndex] == '=' || 
            data[fileIndex] == '<' || 
            data[fileIndex] == '>' || 
            data[fileIndex] == '+' || 
            data[fileIndex] == '-' || 
            data[fileIndex] == '*' ||
            data[fileIndex] == '.' || 
            data[fileIndex] == '/' ) && !caracterSencilloFlag){
            
            //#ifdef DEBUG
                printf("Entro.  %c si fue alfanum, seguimos checando...\n",data[fileIndex]); 
            //#endif
            //METEMOS LA BUFFER EL CARACTER QUE SIGUE, PARA VER SI YA ACABO CON UN ESPACIO
            //SEGUIMOS METIENDO HASTA ENCONTRAR UN ESPACIO
            buffer[j++] = data[fileIndex];
            bufferSize++;
            //#ifdef DEBUG
                printf("Avanzamos el buffer, ahora Buffer tiene: %c\n",data[fileIndex]);
            //#endif


            //Incrementar indice
            fileIndex++;
            
        }
        //Cuando encuentra un espacio o terminador, terminar e identificar que fue el buffer
        else if((data[fileIndex] == ' ' || data[fileIndex] == '\n' || data[fileIndex] == ';') && (j != 0) && !caracterSencilloFlag){
            
            //#ifdef DEBUG
                printf("Entro. Espacio Encontrado, determinar que fue\n");
            //#endif

            //Le mete al buffer un EOL para indicar que ya encontro un espacio o terminador
            buffer[j] = '\0';
            j = 0;

            //HASTA QUE ENCUENTRA UN ESPACIO, ENTONCES SE ATREVE A DECIR QUE FUE LO QUE TERMINO SIENDO

            //Imprimir buffer
            printf("BUFFER: %s\n",buffer);

            //Identificar el buffer utilizando funciones de evaluacion

            if(esPalabraReservada(buffer) == 1) {
                imprimirToken(buffer,"Palabra Reservada");
                e.token = 1;
                e.valor = buffer;
                e.simbolo = '-';
                printf("Buffer size: %d\n",bufferSize);
                // fileIndex += bufferSize;
                return e;
            } else if (esRelacional(buffer)==1) {
                //Que tipo de Operador Relacional es usando un automata de estados
                const char* token = automataOpRelacionales(buffer);
                //Imprimir el Token
                printf("<OP Relacional, %s>\n",token);
                e.token = 6;
                e.valor = buffer;
                e.simbolo = '-';
                printf("Buffer size: %d\n",bufferSize);
                // fileIndex += bufferSize;
                return e;
            } else if (esAritmetico(buffer)==1) {
                imprimirToken(buffer,"Operador Aritmetico");
                e.token = 5;
                e.valor = buffer;
                e.simbolo = '-';
                printf("Buffer size: %d\n",bufferSize);
                // fileIndex += bufferSize;
                return e;
            } else if (esComentario(buffer)==1) {
                imprimirToken(buffer,"Comentario");
                e.token = 8;
                e.valor = buffer;
                e.simbolo = '-';
                printf("Buffer size: %d\n",bufferSize);
                // fileIndex += bufferSize;
                return e;
            } else if (!strcmp(buffer,"=")) {
                imprimirToken(buffer,"Asignacion");
                e.token = 7;
                e.valor = buffer;
                e.simbolo = '-';
                printf("Buffer size: %d\n",bufferSize);
                // fileIndex += bufferSize;
                return e;
            } else if (esNumero(buffer)==1) {
                const char* token = automataNumeros(buffer);
                //Imprimir el Token
                printf("<Tipo, %s>\n",token);
                e.token = 2;
                e.valor = buffer;
                e.simbolo = '-';
                printf("Buffer size: %d\n",bufferSize);
                // fileIndex += bufferSize;
                return e;
            } else {
                printf("<Identificador, %d>\n",idNumero);
                insertarRegistro(buffer,"Identificador",idNumero);
                imprimirListaLigada();
                printf("\n");
                idNumero++;
                e.token = 3;
                e.valor = buffer;
                e.simbolo = '-';
                printf("Buffer size: %d\n",bufferSize);
                // fileIndex += bufferSize;
                return e;
            } 
        
        }
        //Terminar la iteracion
        caracterSencilloFlag = 0;
        
    
    }

}
    




    // //Mientras siga habiendo un caracter, seguir metiendo en el buffer

    //     //Exepciones Alfanumericas que podrian conformar Tokens de mas de un caracter
    //     if((isalnum(data[fileIndex]) || 
    //         data[fileIndex] == '=' || 
    //         data[fileIndex] == '<' || 
    //         data[fileIndex] == '>' || 
    //         data[fileIndex] == '+' || 
    //         data[fileIndex] == '-' || 
    //         data[fileIndex] == '*' ||
    //         data[fileIndex] == '.' || 
    //         data[fileIndex] == '/' ) && !caracterSencilloFlag){
            
    //         //#ifdef DEBUG
    //             printf("Entro.  %c si fue alfanum, seguimos checando...\n",data[fileIndex]); 
    //         //#endif
    //         //METEMOS LA BUFFER EL CARACTER QUE SIGUE, PARA VER SI YA ACABO CON UN ESPACIO
    //         //SEGUIMOS METIENDO HASTA ENCONTRAR UN ESPACIO
    //         buffer[j++] = data[fileIndex];
    //         //#ifdef DEBUG
    //             printf("Avanzamos el buffer, ahora Buffer tiene: %c\n",ch);
    //         //#endif


    //         //Incrementar indice
    //         fileIndex++;
            
    //     }
    //     //Cuando encuentra un espacio o terminador, terminar e identificar que fue el buffer
    //     else if((data[fileIndex] == ' ' || data[fileIndex] == '\n' || data[fileIndex] == ';') && (j != 0) && !caracterSencilloFlag){
            
    //         //#ifdef DEBUG
    //             printf("Entro. Espacio Encontrado, determinar que fue\n");
    //         //#endif

    //         //Le mete al buffer un EOL para indicar que ya encontro un espacio o terminador
    //         buffer[j] = '\0';
    //         j = 0;

    //         //HASTA QUE ENCUENTRA UN ESPACIO, ENTONCES SE ATREVE A DECIR QUE FUE LO QUE TERMINO SIENDO







    //     }



        
//}

        // caracterSencilloFlag = esCorchete(data[fileIndex]);
        // if (caracterSencilloFlag) {
        //     printf("Caracter Sencillo encontrado\n");
        //     return data[fileIndex];
        // }
        // caracterSencilloFlag = esLlave(data[fileIndex]);
        // if (caracterSencilloFlag) {
        //     printf("Caracter Sencillo encontrado\n");
        //     return data[fileIndex];
        // }
        // caracterSencilloFlag = esBooleano(data[fileIndex]);
        // if (caracterSencilloFlag) {
        //     printf("Caracter Sencillo encontrado\n");
        //     return data[fileIndex];
        // }

        //printf("Final del chequeo sencillo\n");
        // printf("Bandera: %d\n",caracterSencilloFlag);

        // if (caracterSencilloFlag) {
        //     scanf("%d",&next);
            
        //     fileIndex++;

        //     printf("Indice incrementado a: %d\n",fileIndex);
        // }



/////////////////////////////////////// CHECAR TOKENS ALFANUMERICOS CON SENTINELA

        //Mientras siga habiendo un caracter, seguir metiendo en el buffer

        //Exepciones Alfanumericas que podrian conformar Tokens de mas de un caracter
        // if((isalnum(ch) || 
        //     ch == '=' || 
        //     ch == '<' || 
        //     ch == '>' || 
        //     ch == '+' || 
        //     ch == '-' || 
        //     ch == '*' ||
        //     ch == '.' || 
        //     ch == '/' ) && !caracterSencilloFlag){
            
        //     #ifdef DEBUG
        //         printf("Entro.  %c si fue alfanum, seguimos checando...\n",ch); 
        //     #endif
        //     //METEMOS LA BUFFER EL CARACTER QUE SIGUE, PARA VER SI YA ACABO CON UN ESPACIO
        //     //SEGUIMOS METIENDO HASTA ENCONTRAR UN ESPACIO
        //     buffer[j++] = ch;
        //     #ifdef DEBUG
        //         printf("Avanzamos el buffer, ahora Buffer tiene: %c\n",ch);
        //     #endif
            
        // }
        // //Cuando encuentra un espacio o terminador, terminar e identificar que fue el buffer
        // else if((ch == ' ' || ch == '\n' || ch == ';') && (j != 0) && !caracterSencilloFlag){
            
        //     #ifdef DEBUG
        //         printf("Entro. Espacio Encontrado, determinar que fue\n");
        //     #endif

        //     //Le mete al buffer un EOL para indicar que ya encontro un espacio o terminador
        //     buffer[j] = '\0';
        //     j = 0;

        //     //HASTA QUE ENCUENTRA UN ESPACIO, ENTONCES SE ATREVE A DECIR QUE FUE LO QUE TERMINO SIENDO
            
            
        //     #ifdef DEBUG
        //         printf("Evaluando buffer: %s\n",buffer);
        //     #endif

        //     //Identificar el buffer utilizando funciones de evaluacion

        //     if(esPalabraReservada(buffer) == 1) {
        //         imprimirToken(buffer,"Palabra Reservada");
        //         scanf("%d",&next);

        //     } else if (esRelacional(buffer)==1) {
        //         //Que tipo de Operador Relacional es usando un automata de estados
        //         const char* token = automataOpRelacionales(buffer);
        //         //Imprimir el Token
        //         printf("<OP Relacional, %s>\n",token);
        //         scanf("%d",&next);
        //     } else if (esAritmetico(buffer)==1) {
        //         imprimirToken(buffer,"Operador Aritmetico");
        //         scanf("%d",&next);
        //     } else if (esComentario(buffer)==1) {
        //         imprimirToken(buffer,"Comentario");
        //         scanf("%d",&next);
        //     } else if (!strcmp(buffer,"=")) {
        //         imprimirToken(buffer,"Asignacion");
        //         scanf("%d",&next);
        //     } else if (esNumero(buffer)==1) {
        //         const char* token = automataNumeros(buffer);
        //         //Imprimir el Token
        //         printf("<Tipo, %s>\n",token);
        //         scanf("%d",&next);
        //     } else {
        //         printf("<Identificador, %d>\n",idNumero);
        //         insertarRegistro(buffer,"Identificador",idNumero);
        //         imprimirListaLigada();
        //         printf("\n");
        //         idNumero++;
        //         scanf("%d",&next);
        //     } 
        
        // }
        //Terminar la iteracion
        //caracterSencilloFlag = 0;

//}




//-------------------------------- Funciones de la Tabla de Simbolos ---------------


// Funcion para insertar un nuevo registro en la Tabla de Simbolos
void insertarRegistro(char symbol[], char type[], int addr){
    
    //Llamar funcion buscaRegistro para asegurar que no haya repeticion
    int n;
    n = buscaRegistro(symbol);
    if(n==1)
        printf("\n\tERROR: REGISTRO DUPLICADO\n");
    else
    {
        
        //Instanciar Tabla
        struct TablaSimbolos *p;
        //Reservar memoria
        p=malloc(sizeof(struct TablaSimbolos));

        //Cargar datos a la estructura
        strcpy(p->symbol,symbol);
        strcpy(p->type,type);
        p->addr = addr;
    
        //Ajustar los apuntadores de la Lista Ligada
        p->next=NULL;
        //Si la lista esta vacia
        if(size==0)
        {
            first=p;
            last=p;
        }
        //Si la lista no esta vacia, reajustar los apuntadores para incrementar
        else
        {
            last->next=p;
            last=p;
        }

        size++;
    }
    #ifdef DDEBUG
        printf("\n REGISTRO INSERTADO\n");
    #endif
}

// Funcion para mostrar todos los registros de la Tabla de Simbolos
void imprimirListaLigada()
{
    int i;
    struct TablaSimbolos *p;
    p=first;
    #ifdef DDEBUG
        printf("Current Address: %p\n",&p);
    #endif
    printf("\n\tADDRESS\t\tSYMBOL\t\tTYPE\n");
    //Recorrer cada elemento de la lista ligada e imprimir sus atributos
    for(i=0;i<size;i++)
    {
        printf("\t%d\t\t%s\t\t%s\n",p->addr,p->symbol,p->type);
        p=p->next;
    }
}

// Funcion de busqueda de registros de la Tabla de Simbolos
int buscaRegistro(char symbol[])
{
    int i,flag=0;
    struct TablaSimbolos *p;
    p=first;
    //Iterar cada elemento de la lista ligada y compara el parametro ingresado con el atributo deseado
    for(i=0;i<size;i++)
    {
        if(strcmp(p->symbol,symbol)==0)
            flag=1;
        p=p->next;
    }
    return flag;
}
