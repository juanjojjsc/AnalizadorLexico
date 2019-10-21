//
//  main.c
//  AnalizadorLexicoJ
//
//  Created by JJ Santos on 21/10/19.
//  Copyright © 2019 JJ Santos. All rights reserved.
//

#include "lexico.h"


int main(int argc, char **argv){

    // Checar que si se haya pasado el argumento
    if (argc < 2) 
    {
        printf("\tFavor de pasar el nombre del programa a analizar como argumento.\n");
        printf("\tEjemplo: ./lexico programa.txt\n");
        exit(EXIT_FAILURE);
    }



    char ch, buffer[15];
    


    FILE *fp;
    int j=0;


    fp = fopen(argv[1],"r");
    
    if(fp == NULL){
        printf("Error al abrir el programa.\n");
        exit(0);
    } else {
        printf("Abriendo el programa: %s\n\n",argv[1]);
    }
    
    int operadorFlag = 0;
    while((ch = fgetc(fp)) != EOF){
        #ifdef DEBUG
            printf("Leyendo: %c\n",ch); 
        #endif


//////////////////////////////////////// CHECAR LOS TOKENS DE UN SOLO CARACTER, SIN CENTINELAS

        operadorFlag = esParentesis(ch);
        operadorFlag = esAritmetico(ch);
        operadorFlag = esBooleano(ch);

    

/////////////////////////////////////// USAR ESTE CHUNK PARA ALFANUMERICOS CON SENTINELA

        //mientras siga habiendo un caracter, seguir metiendo en el buffer
        if((isalnum(ch) || ch == '=' || ch == '<' || ch == '>' ) && !operadorFlag){
            
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
        //cuando ya no encuentre otro caracter, terminar e identificar el buffer
        else if((ch == ' ' || ch == '\n' || ch == ';') && (j != 0) && !operadorFlag){
            
            #ifdef DEBUG
                printf("Entro. Espacio Encontrado, determinar que fue\n");
            #endif

            //Le mete al buffer un EOL para indicar que ya encontro un espacio o ;
            buffer[j] = '\0';
            j = 0;

            //HASTA QUE ENCUENTRA UN ESPACIO, ENTONCES SE ATREVE A DECIR QUE FUE LO QUE TERMINO SIENDO
            
            
            #ifdef DEBUG
                printf("Evaluando buffer: %s\n",buffer);
            #endif

            if(esPalabraReservada(buffer) == 1)
                printf("FOUND: %s is PALABRA RESERVADA\n\n", buffer);
            else if (esRelacional(buffer)==1)
                printf("FOUND: %s is RELACIONAL COMPUESTO\n\n", buffer);
            else if (!strcmp(buffer,"="))
                printf("FOUND: %s is ASIGNACION\n\n", buffer);
            else printf("FOUND: %s is IDENTIFICADOR\n\n", buffer);
        
        }
        operadorFlag = 0;
        
    }
    
    fclose(fp);
    
    return 0;
}
