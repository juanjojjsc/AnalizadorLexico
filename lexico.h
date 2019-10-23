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

//------------------------------ Validaciones Sencillas --------------------------

//Funcion para validar Parentesis
int esParentesis(char ch);

//Funcion para validar Corchetes
int esCorchete(char ch);

//Funcion para validar Llaves
int esLlave(char ch);

//Funcion para validad Booleanos de un solo caracter
int esBooleano(char ch);



//---------------------------- Validaciones Con Buffer --------------------------

//Funcion para validar Operadores Relacionales dentro de un buffer
int esRelacional(char buffer[]);

//Funcion para validar Palabras Reservadas dentro de un buffer
int esPalabraReservada(char buffer[]);

//Funcion para validar Comentarios dentro de un buffer
int esComentario(char buffer[]);

//Funcion para validar Operadores Aritmeticos dentro de un buffer
int esAritmetico(char buffer[]);

//Funcion para validar Numeros dentro de un buffer
int esNumero(char buffer[]);



//------------------------------- Automatas --------------------------------------

//Funcion para Imprimir Tokens de un buffer utilizando un automata
char* automataOpRelacionales(char buffer[]);


//------------------------------- Funciones de Ayuda -----------------------------

// Funcion para Imprimir Tokens en un buffer
void imprimirToken(char buffer[], char tipo[]);

// Funcion para Imprimir Tokens de un solo caracter
void imprimirTokenCh(char ch, char tipo[]);

#endif
