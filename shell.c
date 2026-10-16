#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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
  }
  free(line);
}
