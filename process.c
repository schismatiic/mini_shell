#include "process.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void execute_command(char **argumentos)
{
    int hijo = fork();
    // hay que separar los argumentos por espacios y ponerlos en un array de lo
    // contrario no funca (Hola emi acabo de hacerlo, pero me da miedo tocar lo que hiciste aca no quiero que me pegues)
    if (hijo == 0)
    {
        execlp(argumentos[0], argumentos[1]);
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}