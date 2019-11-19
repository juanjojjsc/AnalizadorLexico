#include <stdio.h>


char* tokens = ["PalabraReservada", "Tipo", "Funcion", "Identificador", "OperadorAsignacion", ""];


struct Entrada {
    int token;
    char* valor;
}

int main() {
    programa();
}


int checaReservada(struct Entrada x, char* palabra) {
    //if x.token es igual a tokens[0] osea PalabraReservada
    if (x.token == 0) {
        // if true
        return strcmp(x.valor, palabra) == 0);
    } else {
        //if false
        return 1;
    }
}


mensajeError()
{
    printf("")
    system pause
    EXIT();
}


void programa() {
    struct Entrada t1;
    t1 = daToken();
    int error;

    if(!checaReservada(t1,"inicio")) {

        //Checar que no haya error con def_variables
        error = def_variables();
        if (error) {
            mensajeError(1);
        }
        error = def_funciones();
        error = lista_sentencias();
        //pedir sgte token
        t1 = daToken();

        if(!checaReservada(t1,"fin")) {
            printf("EXITO");
        } else {
            printf("ERROR, FALTA FIN");
        }


    } else {
        printf("NO SE CUMPLE LA SINTAXIS, FALTA INICIO")
    }
} 


int def_variables() {

    struct Entrada t1;
    t1 = daToken();
    char* tipo;
    char* nombre;

    // si es "Tipo"
    if (t1.token == 1) {
        strcpy(tipo, t1.valor);
        t1 = daToken();
        // si es "Identificador"
        if (t1.token == 3) {
            strcpy(nombre, t1.valor);
            t1 = daToken();
            //si es un operador asignacion
            if (t1.token == 5) {
                //dametoken
                //checar que sea literal   
            }
            // HASTA AQUI,DAR DE ALTA EN LA TABLA DE SIMBOLOS
            // EL LEXICO SOLAMENTE DA TOKENS, NO HACE REGISTROS EN LA TABLA

            //LLAMADA RECURSIVA
            def_variables();
        } else {
            "error"
        }
        //Si es palabra reservada null, es la condicion d eparo
    } else if(t1.token == 0){

        if(!checaReservada(t1,"null")) {
                // regrsar 0 es no hubo error
            return 0;
        } else {
                    "ERROR VARIABLE DECLARADA INCORRECTAMENTE"
            return 1;
        }


    }


}



// ESTE ES EL LEXICO
struct Entrada daToken() {


    return e;
}