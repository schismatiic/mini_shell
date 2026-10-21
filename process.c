#include "process.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void execute_command(char **argumentos) {
  // detectar & para correr programas en segundo plano
  int i = 0;
  bool segundo_plano = false;

  while (argumentos[i] != NULL)
    i++;

  if (i > 0 && strcmp(argumentos[i - 1], "&") == 0) {
    argumentos[i - 1] = NULL;
    segundo_plano = true; // detectamos el & ejecutaremos en segundo plano
  }

  pid_t hijo = fork(); // para hacer waitpid despues
  // hay que separar los argumentos por espacios y ponerlos en un array de lo
  // contrario no funca (Hola emi acabo de hacerlo, pero me da miedo tocar lo
  // que hiciste aca no quiero que me pegues)

  if (hijo == -1) {
    perror("fork failed"); // no creo que llegue a fallar pero por si acaso
  }

  if (hijo == 0) {
    execvp(argumentos[0],
           argumentos); // chasgpt me dijo que era mejor este exec que el otro,
                        // no tengo tiempo para verificar por mi cuenta

    perror(argumentos[0]);
    _exit(127); // convencion para error de comando

  } // esto no se ejecutara por el padre ya que todos los hijos (deberia ser uno
    // solo) terminan su ejecucion
  if (!segundo_plano) {
    int estado;
    if (waitpid(hijo, &estado, 0) == -1) {
      perror("waitpid failed");
      return;
    }
  } else {
    printf("[ %d ] proceso en segundo plano\n", hijo);
  }
}
