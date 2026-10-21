#include "shell.h"
#include "matar.h"
#include "parser.h"
#include "process.h"
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int i;

static void show_prompt(void)
{
    printf("holysh> ");
    fflush(stdout);
}

static void show_help(void)
{
    printf("help: \n exit       Exit HolySH\n");
    printf("\n");
    printf("=============== Holy † Help ===============\n");
    printf("\n");
    printf("  help              Show the help message\n");
    printf("  exit              Exit HolySH\n");
    printf("\n");
    printf("  ls                List directory contents\n");
    printf("  pwd               Print current directory\n");
    printf("  echo Hello        Print a message\n");
    printf("\n");
    printf("===========================================\n");
    printf("\n");
}
// asdlsajdsa
void run_shell(void)
{
    char *line = NULL;
    size_t capacity = 0;
    while (1)
    {
        matar_hijos(); // waitpid a los procesos en segundo plano
        show_prompt();

        ssize_t bytes = getline(
            &line, &capacity, stdin); // bytes se usará para comprobar si getline()
                                      // leyó bien la entrada. Con getline() el
                                      // búfer va a crecer según sea necesario

        if (bytes == -1) // getline() da -1 en caso de error
        {
            break;
        }

        char *argumentos[128]; // Supongamos que nadie pone mas de 128 argumentos
                               // Hola profe son las 12:32AM

        int contador_de_argumentos = parse_command(line, argumentos);

        if (contador_de_argumentos == 0)
        {
            continue; // Si el usuario hace enter, pues pasamos de largo nomas
        }
        argumentos[contador_de_argumentos] =
            NULL; // Recordar que exec necesita un NULL al final, se lo chantamos
                  // aca a lo cerdo
        if (strcmp(argumentos[0], "cd") == 0)
        {
            // Lo puedo intentar, pero me da flojera ahora, seguire tocando el resto
        }

        // line[strcspn(line, "\n")] = '\0'; // strtok ya elimina el salto de linea
        if (strcmp(argumentos[0], "exit") ==
            0) // strcmp() devolverá 0 si las dos cadenas son iguales. En ese caso,
               // el bucle se detiene
        {
            show_stats();
            break;
        }
        if (strcmp(argumentos[0], "help") == 0)
        {
            show_help();
            continue;
        }

        execute_command(argumentos);
    }
    free(line);
}
