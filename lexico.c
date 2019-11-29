//
//  lexico.c
//  AnalizadorLexicoJ
//
//  Created by JJ Santos on 21/10/19.
//  Copyright © 2019 JJ Santos. All rights reserved.
//

#include "lexico.h"


const int palabraLength = 10;


//------------------------------ Validaciones Sencillas --------------------------


//Checar Simbolos
int esSimbolo(char ch){
    if(ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']') {
        #ifdef DEBUG
            imprimirTokenCh(ch,"SIMBOLO");
        #endif
        return 1;
    }
    return 0;
}


//Checar Parentesis
int esParentesis(char ch){
    if(ch == '(' || ch == ')') {
        #ifdef DEBUG
            imprimirTokenCh(ch,"Parentesis");
        #endif
        return 1;
    }
    return 0;
}

//Checar Llaves
int esLlave(char ch){
    if(ch == '{' || ch == '}') {
        #ifdef DEBUG
            imprimirTokenCh(ch,"Llave");
        #endif
        return 1;
    }
    return 0;
}

//Checar Corchetes
int esCorchete(char ch){
    if(ch == '[' || ch == ']') {
        #ifdef DEBUG
            imprimirTokenCh(ch,"Corchete");
        #endif
        return 1;
    }
    return 0;
}

//Checar Booleanos
int esBooleano(char ch){
    char operadoresBooleanos[] = "VF";
    for(int i = 0; i < 2; ++i){
        if(ch == operadoresBooleanos[i]) {
            #ifdef DEBUG
                imprimirTokenCh(ch,"Booleano");
            #endif
            return 1;
        }
    }
    return 0;
}

//---------------------------- Validaciones Con Buffer --------------------------

//Checar Operadores Relacionales
int esRelacional(char buffer[]){

    #ifdef DEBUG
        printf("Entramos al chequeo relacional\n"); 
    #endif

    char operadoresRelacionales[6][palabraLength] = {
        "<=",
        ">=",
        "==",
        "<>",
        "<",
        ">"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < 6; ++i){
        if(strcmp(operadoresRelacionales[i], buffer) == 0){
            flag = 1;
            break;
        }
    }

    #ifdef DEBUG
        printf("Resultado chequeo relacional: %d\n",flag);
    #endif

    
    return flag;
}


//Checar Operadores Incrementales
int esAritmetico(char buffer[]){

    #ifdef DEBUG
        printf("Entramos al chequeo aritmetico\n"); 
    #endif

    char operadoresAritmeticos[8][palabraLength] = {
        "++",
        "--",
        "**",
        "+",
        "-",
        "*",
        "/",
        "%"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < 8; ++i){
        if(strcmp(operadoresAritmeticos[i], buffer) == 0){
            flag = 1;
            break;
        }
    }

    #ifdef DEBUG
        printf("Resultado chequeo aritmetico: %d\n",flag);
    #endif

    
    return flag;
}


//Checar Comentarios
int esComentario(char buffer[]){

    #ifdef DEBUG
        printf("Entramos al chequeo de comentatios\n"); 
    #endif

    char comentarios[1][palabraLength] = {
        "//"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < 1; ++i){
        if(strcmp(comentarios[i], buffer) == 0){
            flag = 1;
            break;
        }
    }

    #ifdef DEBUG
        printf("Resultado chequeo comentarios: %d\n",flag);
    #endif

    
    return flag;
}

//Checar Tipos
int esTipo(char buffer[]){

    #ifdef DEBUG
        printf("ENTRAMOS A esTipo CON: %s\n",buffer);
    #endif

    char tipos[4][palabraLength] = {
        "booleano",
        "real",
        "caracter",
        "entero"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < 4; ++i){
        if(strcmp(tipos[i], buffer) == 0){
            flag = 1;
            break;
        }
    }
    
    return flag;
}



//Checar Palabras Reservadas
int esPalabraReservada(char buffer[]){

    #ifdef DEBUG
        printf("ENTRAMOS A esPalabraReservada CON: %s\n",buffer);
    #endif

    char palabrasReservadas[16][palabraLength] = {
        "inicio",
        "si",
        "sino",
        "casos",
        "caso",
        "default",
        "ciclo",
        "mientras",
        "hacer",
        "variable",
        "fin",
        "funcion",
        "null",
        "regresa",
        "llama"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < 16; ++i){
        if(strcmp(palabrasReservadas[i], buffer) == 0){
            flag = 1;
            break;
        }
    }
    
    return flag;
}

//Checar Numeros
int esNumero(char buffer[]){
    if (isdigit(buffer[0])) return 1;
    return 0;
}


//-------------------------------- Automatas para determinar Tokens ---------------

//Funcion para Imprimir Tokens de Operadores Relacionales, dentro de un buffer utilizando un automata
char* automataOpRelacionales(char buffer[]){
    #ifdef DEBUG
        printf("Entro a funcion automata Op Relacional\n");
    #endif
    
    int estado = 0;
    int j = 0;
    char ch;
    
    
    while (1) 
    {
        switch (estado)
        {
        case 0:
            ch = buffer[0];
            #ifdef DEBUG
                printf("Evaluando: %c\n",ch);
            #endif
            if (ch == '<') estado = 1;
            else if (ch == '=') estado = 5;
            else if (ch == '>') estado = 6;
            break;
        case 1:
            j++;
            ch = buffer[j];
            #ifdef DEBUG
                printf("Evaluando el siguiente: %c\n",ch);
            #endif
            if (ch == '=') estado = 2;
            else if (ch == '>') estado = 3;
            else estado = 4;
            break;
        case 2:
            return "LE";
            break;
        case 3:
            return "NE";
            break;
        case 4:
            return "LT";
            break;
        case 5:
            return "EQ";
            break;
        case 6:
            j++;
            ch = buffer[j];
            #ifdef DEBUG
                printf("Evaluando el siguiente: %c\n",ch);
            #endif
            if (ch == '=') estado = 7;
            else estado = 8;
            break;
        case 7:
            return "GE";
            break;
        case 8:
            return "GT";
            break;
    
        default:
            break;
        }

    }
    return "";
    
}


//Funcion para Imprimir Tokens de Numeros, dentro de un buffer utilizando un automata
char* automataNumeros(char buffer[]){
    #ifdef DEBUG
        printf("Entro a funcion automata Op Relacional\n");
    #endif
    
    int estado = 0;
    int j = 0;
    char ch;
    
    
    while (1) 
    {
        switch (estado)
        {
        case 0:
            ch = buffer[0];
            #ifdef DEBUG
                printf("Evaluando: %c\n",ch);
            #endif
            if (isdigit(ch)) estado = 1;
            // else if (ch == '=') estado = 5;
            // else if (ch == '>') estado = 6;
            else return "";
            break;
        case 1:
            j++;
            ch = buffer[j];
            #ifdef DEBUG
                printf("Evaluando el siguiente: %c\n",ch);
            #endif
            if (isdigit(ch)) estado = 1;
            else if (ch == '.') estado = 2;
            else if (ch == ' ' || ch == ';' || ch == '\n') estado = 3;
            break;
        case 2:
            j++;
            ch = buffer[j];
            #ifdef DEBUG
                printf("Encontro punto, evaluando el siguiente: %c\n",ch);
            #endif
            if (isdigit(ch)) estado = 2;
            else if (ch == ' ' || ch == ';' || ch == '\n') estado = 4;
            break;
        case 3:
            return "Entero";
            break;
        case 4:
            return "Real";
            break;
        
        default:
            break;
        }

    }
    return "";
    
}


//------------------------------- Funciones de Ayuda -----------------------------

// Funcion para Imprimir Tokens de un bufffer
void imprimirToken(char buffer[], char tipo[]){
    printf("<%s, %s>\n",tipo,buffer);
}

// Funcion para Imprimir Tokens de un bufffer
void imprimirTokenCh(char ch, char tipo[]){
    printf("<%s, %c>\n",tipo,ch);
}

