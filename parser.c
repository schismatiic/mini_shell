#include "parser.h"
#include <stdio.h>
#include <string.h>

int parse_command(char *line, char **argumentos)
{
    // Lo mucho que carrea strtok no tiene sentido :D
    char *command =
        strtok(line, " \n"); // Basicamente strtok separa el string segun " " y
                             // "\n" y retorna el primer string, guardando donde
                             // se quedo en la memoria
    int contador_de_argumentos = 0;
    while (command != NULL)
    {
        argumentos[contador_de_argumentos] = command;
        printf("Comando %d: %s \n", contador_de_argumentos, argumentos[contador_de_argumentos]);
        // Se le dice argumentos y no contador por diferencias
        // creativas con el resto del equipo (12:36AM)
        contador_de_argumentos++;
        command = strtok(NULL, " \n");
    } // Este parseador nos permitira elegir de forma selectiva los comandos
      // para mas tarde

    return contador_de_argumentos;
}