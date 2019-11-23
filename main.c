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
int checaReservada();
void mensajeError();


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

char tokens[8][20] = {
                        "PalabraReservada",
                        "Tipo",
                        "Otro",
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


    // programa();



    


    

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    miToken = daToken();
    printf("\tTOKEN: %d\tVALOR: %s\tSIMBOLO: %c\t ADDR: %d\n\n",miToken.token,miToken.valor,miToken.simbolo,miToken.addr);

    
    return 0;
}


// Funcion de Grmatica inicial que manda a llamar a las demas
void programa() {
    printf("programa\n");

    struct Entrada t1;
    t1 = daToken();
    int error = 0;

    printf("Token: %d\n",t1.token);
    printf("Valor: %s\n",t1.valor);
    printf("Simbolor: %c\n",t1.simbolo);


    if(!checaReservada(t1,"inicio")) {
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
        //error = def_funciones();
        printf("Resultado DEF_FUNCIONES: %d\n",error);
        if (error) {
            mensajeError("Error en defincion de funciones.");
        }

        //Checar que no haya error con lista_sentencias
        //error = lista_sentencias();
        printf("Resultado LISTA_SENTENCIAS: %d\n",error);
        if (error) {
            mensajeError("Error en lista de sentencias.");
        }

        //Checar que el programa termine con la palabra reservada 'fin'
        t1 = daToken();
        if(!checaReservada(t1,"fin")) {
            printf("EXITO\n");
        } else {
            mensajeError("ERROR, FALTA FIN");
        }

    }

}

// Funcion Gramatical
int def_variables() {

    struct Entrada t1;
    t1 = daToken();
    char tipo[15];
    char nombre[15];

    printf("DEF_VARIABLES\n");

    printf("Token: %d\n",t1.token);
    printf("Valor: %s\n",t1.valor);
    printf("Simbolor: %c\n",t1.simbolo);

    // si es sgte token es "Tipo"
    if (t1.token == 2) {
        strcpy(tipo, t1.valor);
        printf("TIPO: %s\n",tipo);
        t1 = daToken();
        // si el siguiente es "Identificador"
        if (t1.token == 3) {
            strcpy(nombre, t1.valor);
            printf("ID: %s\n",nombre);
            t1 = daToken();
            //si el siguiente un operador asignacion
            if (t1.token == 7) {
                t1 = daToken();
                //si el siguiente es un literal
                if (t1.token == 2) {
                    // HASTA AQUI,DAR DE ALTA EN LA TABLA DE SIMBOLOS
                    // EL LEXICO SOLAMENTE DA TOKENS, NO HACE REGISTROS EN LA TABLA
                }
            }
            

            //LLAMADA RECURSIVA
            return def_variables();
        } else {
            mensajeError("error");
            return 1;
        }
        //Si es palabra reservada null, es la condicion d eparo
    } else if(t1.token == 1) {

        printf("PALABRA RESERVADA: %s\n",t1.valor);

        if(!checaReservada(t1,"null")) {
                // regrsar 0 es no hubo error
            return 0;
        } else {
            mensajeError("ERROR VARIABLE DECLARADA INCORRECTAMENTE");
            return 1;
        } 


    } else { return 1; }


}


//Funcion que checa que el token de entrada sea la palabra reservada deseada
int checaReservada(struct Entrada x, char* palabra) {
    //if x.token es igual a tokens[0] osea PalabraReservada
    if (x.token == 1) {
        // if true
        printf("in\n");
        return strcmp(x.valor, palabra) == 1;
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
                    printf("<Tipo, %s>\n",token);
                    printf("Buffer size: %d\n",bufferSize);
                #endif
                e.token = 2;
                e.valor = token;
                e.simbolo = '-';
                return e;
            } else {
                insertarRegistro(buffer,"Identificador",idNumero);
                imprimirListaLigada();
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
