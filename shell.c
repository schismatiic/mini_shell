#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int i;

void run_shell(void) {
  char *line = NULL;
  size_t capacity = 0;
  while (1) {
    printf("holysh> ");
    fflush(stdout);
    ssize_t bytes = getline(
        &line, &capacity, stdin); // bytes se usará para comprobar si getline()
                                  // leyó bien la entrada. Con getline() el
                                  // búfer va a crecer según sea necesario

    if (bytes == -1)              // getline() da -1 en caso de error
    {
      break;
    }

    char *argumentos[128]; // Supongamos que nadie pone mas de 128 argumentos
                           // Hola profe son las 12:32AM
    // Lo mucho que carrea strtok no tiene sentido :D
    char *command =
        strtok(line, " \n"); // Basicamente strtok separa el string segun " " y
                             // "\n" y retorna el primer string, guardando donde
                             // se quedo en la memoria
    int contador_de_argumentos = 0;
    while (command != NULL) {
      argumentos[contador_de_argumentos] = command;
      printf("Comando %d: %s \n", contador_de_argumentos,argumentos[contador_de_argumentos]);
      // Se le dice argumentos y no contador por diferencias
      // creativas con el resto del equipo (12:36AM)
      contador_de_argumentos++;
      command = strtok(NULL, " \n");
    } // Este parseador nos permitira elegir de forma selectiva los comandos
      // para mas tarde

    if (contador_de_argumentos == 0) {
      continue; //Si el usuario hace enter, pues pasamos de largo nomas
    }
    argumentos[contador_de_argumentos] = NULL; // Recordar que exec necesita un NULL al final, se lo chantamos aca a lo cerdo
    if (strcmp(argumentos[0], "cd") == 0) {
      // Lo puedo intentar, pero me da flojera ahora, seguire tocando el resto
    }

    // line[strcspn(line, "\n")] = '\0'; // strtok ya elimina el salto de linea
    if (strcmp(argumentos[0], "exit") ==
        0) // strcmp() devolverá 0 si las dos cadenas son iguales. En ese caso,
           // el bucle se detiene
    {
      break;
    }
    if (strcmp(argumentos[0], "help") == 0) {
      printf("help: \n exit       Exit HolySH\n");
    }

    int hijo = fork();
    // hay que separar los argumentos por espacios y ponerlos en un array de lo
    // contrario no funca (Hola emi acabo de hacerlo, pero me da miedo tocar lo que hiciste aca no quiero que me pegues)
    if (hijo == 0) {
      execlp(argumentos[0], argumentos[1]);
      exit(0);
    } else {
      wait(NULL);
    }
  }
  free(line);
}
