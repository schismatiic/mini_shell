#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
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
    line[strcspn(line, "\n")] = '\0'; // Elimina el salto de línea de getline()
    if (strcmp(line, "exit") ==
        0) // strcmp() devolverá 0 si las dos cadenas son iguales. En ese caso,
           // el bucle se detiene
    {
      break;
    }
    if (strcmp(line, "help") == 0) {
      printf("help: \n exit       Exit HolySH\n");
    }
    printf("Command: %s\n", line);

    char *command = strtok(
        line,
        " "); // fix temporal, hay que usar esta funcion para hacer un array de
              // strings separados por espacios y pasarselo a los argumentos

    int hijo = fork();
    // hay que separar los argumentos por espacios y ponerlos en un array de lo
    // contrario no funca
    if (hijo == 0) {
      execlp(command, "", 0);
      exit(0);
    } else {
      wait(NULL);
    }
  }
  free(line);
}
