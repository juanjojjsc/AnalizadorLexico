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

//Checar Parentesis
int esParentesis(char ch){
    if(ch == '(' || ch == ')') {
        imprimirTokenCh(ch,"Parentesis");
        return 1;
    }
    return 0;
}

//Checar Llaves
int esLlave(char ch){
    if(ch == '{' || ch == '}') {
        imprimirTokenCh(ch,"Llave");
        return 1;
    }
    return 0;
}

//Checar Corchetes
int esCorchete(char ch){
    if(ch == '[' || ch == ']') {
        imprimirTokenCh(ch,"Corchete");
        return 1;
    }
    return 0;
}

//Checar Booleanos
int esBooleano(char ch){
    char operadoresBooleanos[] = "VF";
    for(int i = 0; i < 2; ++i){
        if(ch == operadoresBooleanos[i]) {
            imprimirTokenCh(ch,"Booleano");
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
        "!=",
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


//Checar Palabras Reservadas
int esPalabraReservada(char buffer[]){

    char palabrasReservadas[15][palabraLength] = {
        "programa",
        "si",
        "sino",
        "casos",
        "caso",
        "default",
        "ciclo",
        "mientras",
        "hacer",
        "variable",
        "caracter",
        "entero",
        "real",
        "booleano",
        "fin"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < 15; ++i){
        if(strcmp(palabrasReservadas[i], buffer) == 0){
            flag = 1;
            break;
        }
    }
    
    return flag;
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
