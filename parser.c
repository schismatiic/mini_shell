#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

int parse_command(char *line, char **argumentos, int max_args) {

  int contador_de_argumentos = 0;
  // Lo mucho que carrea strtok no tiene sentido :D
  char *token = strtok(line, " \t\n");
  // Basicamente strtok separa el string segun " " y
  // "\n" y retorna el primer string, guardando donde
  // se quedo en la memoria, \t se encarta de TAB
  while (token != NULL) {

    if (contador_de_argumentos >= max_args - 1) {
      break;
    }

    argumentos[contador_de_argumentos] = token;
    contador_de_argumentos++;
    token = strtok(NULL, " \t\n");
  } // Este parseador nos permitira elegir de forma selectiva los comandos
  // para mas tarde
  argumentos[contador_de_argumentos] = NULL;
  // El null se usa para indicar donde termina el array.
  return contador_de_argumentos;
}
