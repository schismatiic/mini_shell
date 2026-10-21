#include "process.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void execute_command(char **argumentos) {
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
  int estado;
  if (waitpid(hijo, &estado, 0) == -1) {
    perror("waitpid failed");
    return;
  }
}
