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

//Estructura para la comunicacion con la tabla de Simbolos
struct Entrada 
{
    int token;
    char* valor;
    char simbolo;
    int addr;
};



//Declarar estructura para recibir tokens de entrada
struct Entrada miToken;

//Apuntadores a primer y ultimo nodo de la Lista Ligada
struct TablaSimbolos *first,*last;

//Declaracion de la funcion daToken
struct Entrada daToken();

//Delcaracion de funciones de gramatica
void programa();
int def_variables();
int def_funciones();
int lista_sentencias();
int sentencia();
int funcion();
int expresionAsignacion();
int termino();
int expresionComparativa();
int expresionIncremental();
int argumentos();
int argumentosLlamada();
int condSi();
int ciclo();
int mientras();
int hacerMientras();
int casos();
int llamaFuncion();
int checaReservada(struct Entrada x, char* palabra);
int checaSimbolo(struct Entrada x, char simbolo);
void mensajeError(char* mensaje);


//Variables
char ch;
int next = 0;
int size = 0;
char input[15]; 
char buffer[15];
char data[255];
int j = 0;
int caracterSencilloFlag = 0;
int idNumero = 1;
int fileLenght = 0;
int bufferSize = 0;
int fileIndex = 0;

char tokens[9][20] = {
                        "PalabraReservada",
                        "Literal",
                        "Otro",
                        "Identificador",
                        "OperadorAritmetico",
                        "OperadorRelacional",
                        "OperadorAsignacion",
                        "Simbolo",
                        "Tipo"
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

    //Copiar archivo al arreglo data    
    while((fscanf(archivo, "%c", &data[fileLenght])) != EOF) {
        #ifdef DEBUG
            printf("Data[%d]: %c\n",fileLenght,data[fileLenght]);
        #endif
        fileLenght++;
    }

    //Agregar un EOF al final
    data[fileLenght] = EOF;


    #ifdef DEBUG
        //Imprimir data
        for (int i=0; i<fileLenght+1; i++)
            printf("%c",data[i]);

        printf("File Lenght: %d\n",fileLenght);
    #endif

    //Cerrar Archivo
    fclose(archivo);




    // LLAMADAS A FUNCIONES DE GRAMATICA ////////////////////////////////////


    programa();
    // printf("llamaFuncion: %d\n",llamaFuncion());



    


    

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    // miToken = daToken();
    // printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    
    return 0;
}


// Funcion de Grmatica inicial que manda a llamar a las demas
void programa() {
    printf("programa\n");

    struct Entrada miToken;
    miToken = daToken();
    int error = 0;

    printf("Token: %d\n",miToken.token);
    printf("Valor: %s\n",miToken.valor);
    printf("Simbolo: %c\n",miToken.simbolo);


    if(!checaReservada(miToken,"inicio")) {
        printf("hola\n");
        printf("Token INICIO encontrado\n");
        printf("adios\n");

        //Checar que no haya error con def_variables
        error = def_variables();
        printf("Resultado DEF_VARIABLES: %d\n",error);
        if (error) {
            mensajeError("Error en defincion de variables.");
        }

        //Checar que no haya error con def_funciones
        error = def_funciones();
        printf("Resultado DEF_FUNCIONES: %d\n",error);
        if (error) {
            mensajeError("Error en defincion de funciones.");
        }

        printf("DEF_FUNCIONES TERMINADA, el token actual:\n");
        printf("Token: %d\n",miToken.token);
        printf("Valor: %s\n",miToken.valor);
        printf("Simbolor: %c\n",miToken.simbolo);


        printf("FASE 3: LISTA_SENTENCIAS\n");
        //Checar que no haya error con lista_sentencias
        error = lista_sentencias();
        printf("Resultado LISTA_SENTENCIAS: %d\n",error);
        if (error) {
            mensajeError("Error en lista de sentencias.");
        }

        //Checar que el programa termine con la palabra reservada 'fin'
        //miToken = daToken();
        printf("Vamos a checar si hay fin en: %d\n",miToken.token);
        if(!checaReservada(miToken,"fin")) {
            printf("EXITO\n");
        } else {
            mensajeError("ERROR, FALTA FIN");
        }

    }

}

// Funcion Gramatical
int def_variables() {

    printf("adentro de def_vars\n");
    miToken = daToken();
    char tipo[15];
    char nombre[15];

    printf("DEF_VARIABLES\n");

    printf("Token: %d\n",miToken.token);
    printf("Valor: %s\n",miToken.valor);
    printf("Simbolor: %c\n",miToken.simbolo);

    // si es sgte token es "Tipo"
    if (miToken.token == 9) {
        printf("SI - 1\n");
        strcpy(tipo, miToken.valor);
        printf("TIPO: %s\n",tipo);
        miToken = daToken();
        printf("El siguiente token fue... %d\n",miToken.token);
        // si el siguiente es "Identificador"
        if (miToken.token == 4) {
            printf("SI - 2\n");
            strcpy(nombre, miToken.valor);
            printf("ID: %s\n",nombre);
            miToken = daToken();
            //si el siguiente un operador asignacion
            if (miToken.token == 7) {
                printf("SI - 3\n");
                miToken = daToken();
                //si el siguiente es un literal
                if (miToken.token == 2) {
                    printf("SI - 4\n");
                    // HASTA AQUI,DAR DE ALTA EN LA TABLA DE SIMBOLOS
                    // EL LEXICO SOLAMENTE DA TOKENS, NO HACE REGISTROS EN LA TABLA

                    // REGISTRAR
                    return 0;

                }
            }
            

            //LLAMADA RECURSIVA
            return def_variables();
        } else {
            mensajeError("error");
            return 1;
        }
        //Si es palabra reservada null, es la condicion d eparo
    } else if(miToken.token == 1) {

        printf("PALABRA RESERVADA: %s\n",miToken.valor);

        if(!checaReservada(miToken,"null")) {
                // regrsar 0 es no hubo error
            return 0;
        } else {
            mensajeError("ERROR VARIABLE DECLARADA INCORRECTAMENTE");
            return 1;
        } 


    } else { return 1; }


}


// Funcion Gramatical
int argumentos() {

    // int error = 0;
    char tipo[15];
    char nombre[15];
    // struct Entrada miToken;
    miToken = daToken();
    
    printf("Token: %d\n",miToken.token);
    printf("Valor: %s\n",miToken.valor);
    printf("Simbolo: %c\n",miToken.simbolo);

    //Checar Tipo 
    // si es sgte token es "Tipo"
    if (miToken.token == 9) {
        printf("SI - Tipo\n");
        strcpy(tipo, miToken.valor);
        printf("TIPO: %s\n",tipo);
        miToken = daToken();
        //Checar ID
        if (miToken.token == 4) {
            printf("SI - ID\n");
            strcpy(nombre, miToken.valor);
            printf("ID: %s\n",nombre);

            //Llamada recursiva
            return 0;
        } else {
            return 1;
        }
    } else {
        return 1;
    }

}

// Funcion Gramatical
int llamaFuncion() {

    int error = 0;
    // char tipo[15];
    char nombre[15];
    //struct Entrada miToken;
    miToken = daToken();
    
    printf("Token: %d\n",miToken.token);
    printf("Valor: %s\n",miToken.valor);
    printf("Simbolo: %c\n",miToken.simbolo);

    //Checar ID
    if (miToken.token == 4) {
        printf("SI - ID\n");
        strcpy(nombre, miToken.valor);
        printf("ID: %s\n",nombre);
        miToken = daToken();
        //Checar parentesis
        if (miToken.token == 8) {
            if(miToken.simbolo == '(') {
                printf("Parentesis ( encontrado\n");
                //Checar Argumentos de llamada
                error = argumentosLlamada();
                if (!error) {
                    miToken = daToken();
                    //Checar parentesis
                    if (miToken.token == 8) {
                        if(miToken.simbolo == ')') {
                            printf("Parentesis ) encontrado\n");
                            return 0;
                        } else return 1;
                    } else return 1;
                } else return 1;
            } else return 1;
        } else return 1;

    } else {
        return 1;
        mensajeError("Error en llamada de funcion");
    }



}

// Funcion Gramatical
int argumentosLlamada() {

    // int error = 0;
    // char tipo[15];
    char nombre[15];
    //struct Entrada miToken;
    miToken = daToken();
    
    printf("Token: %d\n",miToken.token);
    printf("Valor: %s\n",miToken.valor);
    printf("Simbolo: %c\n",miToken.simbolo);

    //Checar ID
    if (miToken.token == 4) {
        printf("SI - ID\n");
        strcpy(nombre, miToken.valor);
        printf("ID: %s\n",nombre);
        return 0;

        //Checar Literal
        //IMPLEMENTAR RECURSION
    } else if (miToken.token == 2) {
        printf("SI - LITERAL\n");
        return 0;
    } else {
        mensajeError("Error en argumentos de llamda");
        return 1;
    }

}

// Funcion Gramatical
int lista_sentencias() {

    int error = 0;
    char nombre[15];
    //struct Entrada miToken;
    miToken = daToken();
    printf("Entramos a lista_sentencias\n");
    printf("Token: %d\n",miToken.token);
    printf("Valor: %s\n",miToken.valor);
    printf("Simbolo: %c\n",miToken.simbolo);

    int res = !checaReservada(miToken,"null");
    printf("Resultado de compara: %d\n",res);



    //Checar ID
    if (miToken.token == 4 || miToken.token ==1) {
        printf("Encontamos ID dentro de list\n");
        strcpy(nombre, miToken.valor);
        printf("ID: %s\n",nombre);
        printf("es sentencia\n");
        error = sentencia();
        printf("Resultado SENTENCIA: %d\n",error);
        if (error) {
            mensajeError("Error en defincion de funciones.");
        //Si es palabra reservada null, es la condicion d eparo
        } else {
            printf("No hubo error con lista_sentencias\n");
            return lista_sentencias();
        }
        
    }

    
    if(!checaReservada(miToken,"fin")) {


            printf("fin encontrado\n");
            return 0;
        


    }

}

//Funcion Gramatical
int ciclo() {
    


}

// Funcion Gramatical
int mientras() {
    printf("Entramos a mientras...\n");

    // Si es un mientras
    if(miToken.token == 1) {
        printf("PALABRA RESERVADA: %s\n",miToken.valor);
        if(!checaReservada(miToken,"mientras")) {
            printf("mientras encontrado\n");
            //Checar parentesis
            if (miToken.token == 8) {
                if(miToken.simbolo == '(') {
                    printf("Parentesis ( encontrado\n");
                    return 0;
                } 
            }


            
        } else {
            return 1;
        } 
    } //Si es un HACER MIENTRAS 
     else if (miToken.token == 1) {
        printf("PALABRA RESERVADA: %s\n",miToken.valor);
        if(!checaReservada(miToken,"hacer")) {
            printf("hacer encontrado\n");

            return 0;
        } else {
            return 1;
        } 
     } else {
         mensajeError("ERROR MIENTRAS DECLARADO INCORRECTAMENTE");
        return 1;
     }


}

// Funcion Gramatical
int condicion() {

    int error = 0;
    char nombre[15];
    error = expresionComparativa();
    if (!error) {
        printf("Expresion Comparativa Correcta\n");
        miToken = daToken();
    } else {
        error = expresionIncremental();
        if (!error) {
            printf("Expresion Incremental Correcta\n");
            miToken = daToken();
        } else {
            //Checar ID
            if (miToken.token == 4) {
                printf("Encontamos ID en expresion asignacion\n");
                strcpy(nombre, miToken.valor);
                printf("ID: %s\n",nombre);
                return 0;
            }

        }
    }        


}



//Funcion Gramatical
int sentencia() {

    printf("DENTRO DE FUNCION SENTENCIA\n");
    
    int error = 0;

    //Si es una sentencia que empieze con palabra reservada
    if (miToken.token == 2) {
        //Definir sentencia

        //error = ciclo();
        if (!error) {
            printf("Ciclo Encontrado");
            return 0;
        } else {
            error = mientras();
            if (!error) {
                printf("Mientras Encontrado");
                return 0;
            } else {
                //error = hacerMientras();
                if (!error) {
                    printf("Hacer Mientas Encontrado");
                    return 0;
                } else {
                    //error = condSi();
                    if (!error) {
                        printf("Cond Si Encontrado");
                        return 0;
                    } else {
                        //error = hacerMientras();
                        if (!error) {
                            printf("Hacer Mientas Encontrado");
                            return 0;
                        } else {
                            //error = casos();
                            if (!error) {
                                printf("Casos Encontrado");
                                return 0;
                            } else {
                                //error = llamaFuncion();
                                if (!error) {
                                    printf("Llama funcion Encontrado");
                                    return 0;
                                }

                            }

                        }


                    }
                }

            }
            
        }
    


        //Si es una sentencia que empieza con IDENTIFICADOR
    } else if(miToken.token == 4) {

        printf("Encontramos id.....\n");

        error = expresionAsignacion();

        if (!error) {
            
            return 0;
        } else {
            return 1;
            mensajeError("Error en expresion de asignacion");
        }

    } 

}

// Funcion Gramatical
int termino() {

    char nombre[15];
    // Si es un literal
    if (miToken.token == 2) {
        printf("SI - LITERAL\n");
        // HASTA AQUI,DAR DE ALTA EN LA TABLA DE SIMBOLOS
        // EL LEXICO SOLAMENTE DA TOKENS, NO HACE REGISTROS EN LA TABLA

        // REGISTRAR
        return 0;

    // Si comienza con Identificador
    } else if (miToken.token == 4) {
        printf("Encontramos ID\n");
        strcpy(nombre, miToken.valor);
        printf("ID: %s\n",nombre);
        miToken = daToken();
        printf("El siguiente token fue... %d\n",miToken.token);
        //Checar Operador Aritmetico
        if (miToken.token == 5) {
            printf("Operador Aritmetico encontrado\n");
            miToken = daToken();
            // Si es un literal
            if (miToken.token == 2) {
                printf("SI - LITERAL\n");
                return 0;
            }
        }
        
    }

}

// Funcion Gramatical
int expresionComparativa() {

    int error = 0;

    //si el siguiente es un termino
    error = termino();
    printf("Resultado TERMINO: %d\n",error);
    if (error) {
        mensajeError("Error en termino.");
        return 1;
    }  else {
        //Checar Operador Relacional
        miToken = daToken();
        if (miToken.token == 6) {
            printf("Operador Relacional encontrado\n");
            miToken = daToken();
            //si el siguiente es un operador relacional
            error = termino();
            printf("Resultado TERMINO: %d\n",error);
            if (error) {
                mensajeError("Error en termino.");
                return 1;
            }  else {
                printf("Termino encontrado");
                return 0;
            }
            
        }
    }

}

// Funcion Gramatical
int expresionIncremental() {

    int error = 0;

    //si el siguiente es un termino
    error = termino();
    printf("Resultado TERMINO: %d\n",error);
    if (error) {
        mensajeError("Error en termino.");
        return 1;
    }  else {
        miToken = daToken();
        //Checar Operador Incremental
        if (miToken.token == 5) {
            if(strcmp(miToken.valor,"++")) {
                printf("Operador Incremental encontrado\n");
                return 0;
            }
        }
        
    }

}

// Funcion Gramatical
int expresionAsignacion() {
    
    char nombre[15];
    int error = 0;
    // char tipo[15];
    //Checar ID
    if (miToken.token == 4) {
        printf("Encontamos ID en expresion asignacion\n");
        strcpy(nombre, miToken.valor);
        printf("ID: %s\n",nombre);
        miToken = daToken();
        printf("El siguiente token fue... %d\n",miToken.token);
        //si el siguiente un operador asignacion
        if (miToken.token == 7) {
            printf("SI - OAs\n");
            miToken = daToken();
            //si el siguiente es un termino
            error = termino();
            printf("Resultado TERMINO: %d\n",error);
            if (error) {
                mensajeError("Error en termino.");
                return 1;
            }  else {
                printf("Expresion de asignacion correcta\n");
                return 0;
            }

        }

    } else {
        mensajeError("Error en expresion de asignacion..\n");
        return 1;
    }


}


// Funcion Gramatical
int def_funciones() {

    printf("Adentro de Def_Funciones\n");

    int error = 0;

    if (miToken.token == 1) {

        printf("PALABRA RESERVADA: %s\n",miToken.valor);

        if(!checaReservada(miToken,"null")) {
                // regrsar 0 es no hubo error
            return 0;
        } else {
            mensajeError("ERROR VARIABLE DECLARADA INCORRECTAMENTE");
            return 1;
        }
    }

    //Checar que no haya error con funcion
    error = funcion();
    printf("Resultado FUNCION: %d\n",error);
    if (error) {
        mensajeError("Error en defincion de funciones.");
        return 1;
    }  else {
        printf("Adios Def_Funciones");
        return 0;
    }


}

// Funcion Gramatical
int funcion() {

    int error = 0;
    //struct Entrada miToken;
    miToken = daToken();
    char tipo[15];
    char nombre[15];

    printf("ADENTRO DE FUNCION\n");

    printf("Token: %d\n",miToken.token);
    printf("Valor: %s\n",miToken.valor);
    printf("Simbolor: %c\n",miToken.simbolo);

    // si es sgte token es "Tipo"
    if (miToken.token == 9) {
        printf("SI - 1\n");
        strcpy(tipo, miToken.valor);
        printf("TIPO: %s\n",tipo);
        miToken = daToken();
        printf("El siguiente token fue... %d\n",miToken.token);
        // si el siguiente es palabra reservada "funcion"
        if (miToken.token == 1) {
            printf("SI - 2\n");
            //strcpy(nombre, miToken.valor);
            //printf("ID: %s\n",nombre);
            if(!checaReservada(miToken,"funcion")) {
                printf("SI - 3\n");
                printf("Palabra reservada funcion\n");
                miToken = daToken();
                //Checar ID
                if (miToken.token == 4) {
                    printf("SI - 4\n");
                    strcpy(nombre, miToken.valor);
                    printf("ID: %s\n",nombre);
                    miToken = daToken();
                    printf("El siguiente token fue... %d\n",miToken.token);
                    //Checar parentesis
                    if (miToken.token == 8) {
                        if(miToken.simbolo == '(') {
                            printf("Parentesis ( encontrado\n");
                            //Checar argumentos
                            error = argumentos();
                            if (!error) {
                                printf("Argumentos correctos\n");
                                miToken = daToken();
                                //Checar parentesis )
                                if (miToken.token == 8) {
                                    if(miToken.simbolo == ')') {
                                        printf("Parentesis encontrado )\n");
                                        miToken = daToken();
                                        //Checar Corchete {
                                        if (miToken.token == 8) {
                                            if(miToken.simbolo == '{') {
                                                printf("Corchete encontrado {\n");
                                                //Checar que no haya error con def_variables
                                                error = def_variables();
                                                printf("Resultado DEF_VARIABLES dentro de DEF_FUNCIONES: %d\n",error);
                                                if (error) {
                                                    mensajeError("Error en defincion de variables.");
                                                } else {
                                                    //Checar que no haya error con lista_sentencias
                                                    error = lista_sentencias();
                                                    printf("Resultado LISTA_SENTENCIAS dentro de DEF_FUNCIONES: %d\n",error);
                                                    if (error) {
                                                        mensajeError("Error en LISTA_SENTENCIAS.");
                                                    } else {

                                                        printf("Sin error en LISTA_SENTENCIAS\n");
                                                        //Checar palabra reservada 'regresa'
                                                        if (miToken.token == 1) {
                                                            printf("PALABRA RESERVADA: %s\n",miToken.valor);
                                                            if(!checaReservada(miToken,"regresa")) {
                                                                printf("Encontramos 'regresa'\n");
                                                                miToken = daToken();
                                                                //Checar identificador
                                                                if (miToken.token == 4) {
                                                                    printf("SI regresa un ID\n");
                                                                    strcpy(nombre, miToken.valor);
                                                                    printf("ID: %s\n",nombre);

                                                                    miToken = daToken();
                                                                    //Checar corchete }
                                                                    if (miToken.token == 8) {
                                                                        if(miToken.simbolo == '}') {
                                                                            printf("Corchete encontrado }\n");
                                                                            return 0;
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                mensajeError("ERROR REGRESO DE FUNCION INCORRECTO");
                                                                return 1;
                                                            }


                                                    }



                                                    
                                                    
                                                }

                                                    
                                                }

                                            }
                                        }
                                    }
                                }
                            }
                            
                        }

                    }
                }
            }
        }
    } else {
        mensajeError("ERROR en definicion de funcion");
        return 1;
    }
           


}


//Funcion que checa que el token de entrada sea la palabra reservada deseada
int checaReservada(struct Entrada x, char* palabra) {
    //if x.token es igual a tokens[0] osea PalabraReservada
    if (x.token == 1) {
        // if true
        return strcmp(x.valor, palabra) == 1;
    } else {
        //if false
        return 1;
    }
}

//Funcion que checa que el token de entrada sea la palabra reservada deseada
int checaSimbolo(struct Entrada x, char simbolo) {
    //if x.token es igual a tokens[0] osea PalabraReservada
    if (x.token == 8) {
        // if true
        return !(x.token == simbolo);
    } else {
        //if false
        return 1;
    }
}


// Funcion que imprime mensaje de error y termina programa
void mensajeError(char* mensaje) {
    printf("%s\n\n", mensaje);
    printf("Terminando programa.\n\n");
    exit(0);
}


//Funcion que devuelve el siguiente Token en forma de estructura
struct Entrada daToken() {

    #ifdef DEBUG
        printf("Pidiendo Token\n"); 
    #endif

    //Instanciar token de entrada
    struct Entrada e;
   
    //Si es un punto y coma, recorrer el indice
    if ( data[fileIndex] == ';') {
        #ifdef DEBUG
            printf("Encontramos punto y coma\n"); 
        #endif
        fileIndex++;
    }

    //Si es un espacio, recorrer el indice
    if ( data[fileIndex] == ' ') {  
        #ifdef DEBUG
            printf("Encontramos espacio\n");
        #endif
        fileIndex++;
    }

    //Si es una NUEVA LINEA, recorrer el indice
    if ( data[fileIndex] == '\n') {
        #ifdef DEBUG
            printf("Encontramos nueva linea\n");
        #endif
        fileIndex++;
    }

    // Si ya se acabo el file, regresar un token fallido.
    if (data[fileIndex] == EOF) {
        #ifdef DEBUG
            printf("\n\tEOF\n");
        #endif
        struct Entrada failed;
        failed.token = -1;
        return failed;
    }
    

    #ifdef DEBUG
        printf("Entrando a daToken con indice: %d\n", fileIndex);
        printf("Vamos a checar: %c\n", data[fileIndex]);
    #endif


    // CHECAR LOS TOKENS DE UN SOLO CARACTER OSEA SIMBOLOS, SIN CENTINELAS
    caracterSencilloFlag = 0;
    caracterSencilloFlag = esSimbolo(data[fileIndex]);
    if (caracterSencilloFlag) {
        #ifdef DDEBUG
            printf("Caracter Sencillo encontrado\n");
            printf("Se va a guardar: %c\n", data[fileIndex]);
        #endif
        
        // Cargar Data
        // token num 8 es Simbolos 
        e.token = 8;
        e.simbolo = data[fileIndex];
        e.valor = "-";

        #ifdef DEBUG
            printf("Guardamos token: %d\n", e.token);
            printf("Guardamos simbolo: %c\n", e.simbolo);
        #endif
        
        //Incrementar el indice en cada pasada
        fileIndex++;
        
        return e;
    }

    caracterSencilloFlag = esBooleano(data[fileIndex]);
    if (caracterSencilloFlag) {
        #ifdef DDEBUG
            printf("Caracter Booleano encontrado\n");
            printf("Se va a guardar: %c\n", data[fileIndex]);
        #endif
        
        // Cargar Data
        // token num 2 es Literal 
        e.token = 2;
        // char str[15];
        // str[0] = data[fileIndex];
        if (data[fileIndex] == 'V')
            e.valor = "V";
        if (data[fileIndex] == 'F')
            e.valor = "F";
        e.simbolo = '-';

        #ifdef DEBUG
            printf("Guardamos token: %d\n", e.token);
            printf("Guardamos simbolo: %c\n", e.simbolo);
        #endif
        
        //Incrementar el indice en cada pasada
        fileIndex++;
        
        return e;
    }



    // CHECAR TOKENS ALFANUMERICOS CON CENTINELA

    //Mientras el indice de data sea menor que su longitud
    //Evaluar cada caracter, ir incrementando el indice para formar tokens
    while(fileIndex < fileLenght) {

        
        //Si se llega al final del archivo, romper el ciclo
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
            
            #ifdef DEBUG
                printf("Entro.  %c si fue alfanum, seguimos checando...\n",data[fileIndex]); 
            #endif
            //METEMOS LA BUFFER EL CARACTER QUE SIGUE, PARA VER SI YA ACABO
            //SEGUIMOS METIENDO HASTA ENCONTRAR UN ESPACIO
            buffer[j++] = data[fileIndex];
            bufferSize++;
            #ifdef DEBUG
                printf("Avanzamos el buffer, ahora Buffer tiene: %c\n",data[fileIndex]);
            #endif


            //Incrementar indice
            fileIndex++;
            
        }
        //Cuando encuentra un espacio o terminador, terminar e identificar que fue el buffer
        else if((data[fileIndex] == ' ' || data[fileIndex] == '\n' || data[fileIndex] == ';') && (j != 0) && !caracterSencilloFlag){
            
            #ifdef DEBUG
                printf("Espacio Encontrado, determinar que fue el buffer.\n");
            #endif

            //Le mete al buffer un EOL para indicar que ya encontro un espacio o terminador
            buffer[j] = '\0';
            j = 0;

            //HASTA QUE ENCUENTRA UN ESPACIO, ENTONCES SE PUEDE DECIR QUE FUE LO QUE TERMINO SIENDO

            //Imprimir buffer
            #ifdef DEBUG
                printf("BUFFER: %s\n",buffer);
            #endif 

            //Identificar el buffer utilizando funciones de evaluacion
            //Carga la informacion del token en una instancia de estructura Entrada
            //Devuelve la estructura con el token
            if(esPalabraReservada(buffer) == 1) {
                #ifdef DEBUG
                    printf("Buffer size: %d\n",bufferSize);
                    imprimirToken(buffer,"Palabra Reservada");  
                #endif
                e.token = 1;
                e.valor = buffer;
                e.simbolo = '-';
                return e;
            } else if(esTipo(buffer) == 1) {
                #ifdef DEBUG
                    printf("Buffer size: %d\n",bufferSize);
                    imprimirToken(buffer,"Tipo");  
                #endif
                e.token = 9;
                e.valor = buffer;
                e.simbolo = '-';
                return e;
            } else if (esRelacional(buffer)==1) {
                //Que tipo de Operador Relacional es usando un automata de estados
                char* token = automataOpRelacionales(buffer);
                #ifdef DEBUG
                    printf("<OP Relacional, %s>\n",token);
                    printf("Buffer size: %d\n",bufferSize);
                #endif
                e.token = 6;
                e.valor = token;
                e.simbolo = '-';
                return e;
            } else if (esAritmetico(buffer)==1) {
                #ifdef DEBUG
                    imprimirToken(buffer,"Operador Aritmetico");
                    printf("Buffer size: %d\n",bufferSize);
                #endif
                e.token = 5;
                e.valor = buffer;
                e.simbolo = '-';
                return e;
            } else if (esComentario(buffer)==1) {
                #ifdef DEBUG
                    imprimirToken(buffer,"Comentario");
                    printf("Buffer size: %d\n",bufferSize);
                #endif
                e.token = 8;
                e.valor = buffer;
                e.simbolo = '-';
                return e;
            } else if (!strcmp(buffer,"=")) {
                #ifdef DEBUG
                    imprimirToken(buffer,"Asignacion");
                    printf("Buffer size: %d\n",bufferSize);
                #endif
                e.token = 7;
                e.valor = buffer;
                e.simbolo = '-';
                return e;
            } else if (esNumero(buffer)==1) {
                char* token = automataNumeros(buffer);
                #ifdef DEBUG
                    printf("<Literal, %s>\n",token);
                    printf("Buffer size: %d\n",bufferSize);
                #endif
                e.token = 2;
                e.valor = token;
                e.simbolo = '-';
                return e;
            } else {
                //insertarRegistro(buffer,"Identificador",idNumero);
                //imprimirListaLigada();
                #ifdef DEBUG
                    printf("Registro insertado\n");
                    printf("<Identificador, %d>\n",idNumero);
                    printf("Buffer size: %d\n",bufferSize);
                    printf("\n");
                #endif
                
                
                e.valor = buffer;
                e.addr = idNumero;
                e.token = 4;
                e.simbolo = '-';
        
                idNumero++;
                return e;
            } 
        
        } 
        //Terminar la iteracion
        caracterSencilloFlag = 0;
        
    }
    //Return failed token. Not a valid afanumerical character
    printf("REGRESA");
    e.token = -1;
    return e;

}
    





//----------------- Funciones de la Tabla de Simbolos ---------------


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
    printf("\n\n");
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
