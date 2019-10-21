//
//  lexico.h
//  AnalizadorLexicoJ
//
//  Created by JJ Santos on 21/10/19.
//  Copyright © 2019 JJ Santos. All rights reserved.
//

#ifndef lexico_h
#define lexico_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//Funcion para validar Parentesis
int esParentesis(char ch);

//Funcion para validad Operadores Aritmeticos de un solo caracter
int esAritmetico(char ch);

//Funcion para validad Booleanos de un solo caracter
int esBooleano(char ch);

//Funcion para validad Operadores Relacionales dentro de un buffer
int esRelacional(char buffer[]);

//Funcion para validad Palabras Reservadas dentro de un buffer
int esPalabraReservada(char buffer[]);


#endif
