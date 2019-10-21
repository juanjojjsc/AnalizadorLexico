//
//  lexico.c
//  AnalizadorLexicoJ
//
//  Created by JJ Santos on 21/10/19.
//  Copyright © 2019 JJ Santos. All rights reserved.
//

#include "lexico.h"


const int keywordsNumber = 32;
const int palabrasReservadasNumero = 10;
const int opRelacionalesNumero = 6;
const int palabraLength = 10;


char operadoresRelacionales[] = "<>!";
char operadoresAritmeticos[] = "+-*/%";
char operadoresIncrementales[] = "++ --";
char operadoresBooleanos[] = "VF";
char operadoresRelacionalesSencillos[] = "<>";
int relacionalesSencillosLength = 2;
int aritmeticosLenght = 5;
int relacionalesLength = 3;
int booleanosLength = 2;


//Checar Parentesis
int esParentesis(char ch){
    if(ch == '(' || ch == ')') {
        
        printf("FOUND: PARENTESIS: %c\n\n",ch);
        return 1;
    }
    return 0;
}

//Checar Operadores Aritmeticos
int esAritmetico(char ch){
    for(int i = 0; i < aritmeticosLenght; ++i){
        if(ch == operadoresAritmeticos[i]) {
            //Decir que ya terminamos este chequeo, no es necesario seguir checando
            printf("FOUND: OP ARITMETICO: %c\n\n",ch);
            return 1;
        }
    }
    return 0;
}

//Checar Booleanos
int esBooleano(char ch){
    for(int i = 0; i < booleanosLength; ++i){
        if(ch == operadoresBooleanos[i]) {
            //Decir que ya terminamos este chequeo, no es necesario seguir checando
            printf("FOUND: BOOLEANO: %c\n\n",ch);
            return 1;
        }
    }
    return 0;
}


//Checar Operadores Relacionales
int esRelacional(char buffer[]){

    printf("Entramos al chequeo relacional\n");
    char operadoresRelacionales[opRelacionalesNumero][palabraLength] = {
        "<=",
        ">=",
        "==",
        "!=",
        "<",
        ">"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < opRelacionalesNumero; ++i){
        if(strcmp(operadoresRelacionales[i], buffer) == 0){
            flag = 1;
            break;
        }
    }
    printf("Resultado chequeo relacional: %d\n",flag);
    return flag;
}

int esPalabraReservada(char buffer[]){

    // char keywords[keywordsNumber][palabraLength] = {"auto","break","case","char","const","continue","default",
    //     "do","double","else","enum","extern","float","for","goto",
    //     "if","int","long","register","return","short","signed",
    //     "sizeof","static","struct","switch","typedef","union",
    //     "unsigned","void","volatile","while"};

    char palabrasReservadas[palabrasReservadasNumero][palabraLength] = {
        "programa",
        "si",
        "sino",
        "casos",
        "caso",
        "default",
        "ciclo",
        "mientras",
        "hacer",
        "fin"
    };

    int i = 0;
    int flag = 0;
    
    for(i = 0; i < keywordsNumber; ++i){
        if(strcmp(palabrasReservadas[i], buffer) == 0){
            flag = 1;
            break;
        }
    }
    
    return flag;
}



