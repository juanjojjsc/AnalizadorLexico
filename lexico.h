//
//  lexico.h
//  AnalizadorLexicoJ
//
//  Created by JJ Santos on 21/10/19.
//  Copyright © 2019 JJ Santos. All rights reserved.
//

#ifndef lexico_h
#define lexico_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//------------------------------ Validaciones Sencillas --------------------------

//Funcion para validar Simbolos
int esSimbolo(char ch);

//Funcion para validar Parentesis
int esParentesis(char ch);

//Funcion para validar Corchetes
int esCorchete(char ch);

//Funcion para validar Llaves
int esLlave(char ch);

//Funcion para validar Booleanos
int esBooleano(char ch);

//Funcion para validar Caracteres
int esCaracter(char ch);



//---------------------------- Validaciones Con Buffer --------------------------

//Funcion para validar Operadores Relacionales dentro de un buffer
int esRelacional(char buffer[]);

//Funcion para validar Palabras Reservadas dentro de un buffer
int esPalabraReservada(char buffer[]);

//Funcion para validar Tipos dentro de un buffer
int esTipo(char buffer[]);


//Funcion para validar Comentarios dentro de un buffer
int esComentario(char buffer[]);

//Funcion para validar Operadores Aritmeticos dentro de un buffer
int esAritmetico(char buffer[]);

//Funcion para validar Numeros dentro de un buffer
int esNumero(char buffer[]);



//------------------------------- Automatas --------------------------------------

//Funcion para Imprimir Tokens de Operadores Relacionales dentro de un buffer utilizando un automata
char* automataOpRelacionales(char buffer[]);

//Funcion para Imprimir Tokens de Numeros dentro de un buffer utilizando un automata
char* automataNumeros(char buffer[]);


//------------------------------- Funciones de Ayuda -----------------------------

// Funcion para Imprimir Tokens en un buffer
void imprimirToken(char buffer[], char tipo[]);

// Funcion para Imprimir Tokens de un solo caracter
void imprimirTokenCh(char ch, char tipo[]);

#endif


//-------------------------------- Funciones de la Tabla de Simbolos ---------------

// Funcion para insertar un nuevo registro en la Tabla de Simbolos
void insertarRegistro(int addr, char token[], char symbol[], char type[], char scope[]);
// Funcion para mostrar todos los registros de la Tabla de Simbolos
void imprimirListaLigada();

// Funcion de busqueda de registros de la Tabla de Simbolos
int buscaRegistro(char symbol[]);

