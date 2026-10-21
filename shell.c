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


static void show_prompt(void)
{
    char cwd[1024]; // Un arreglo para guardar la ruta actual

    // getcwd obtiene la ruta actual y la guarda en 'cwd'
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("holysh:%s$ ", cwd); // Muestra la ruta dentro del prompt
    }
    else
    {
        printf("holysh> "); // Plan B por si falla
    }
    
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
    printf("  cd                Change Directory\n");
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

    char dir_inicial[1024]; // arreglo de chars (string?) para guardar la dirección inicial

    if (getcwd(dir_inicial, sizeof(dir_inicial)) == NULL) //esto hace 2 cosas, obtiene la dirección actual con getcwd y lo guarda en dir_inicial especificando el tamaño que requiere y por otro lado se asegura de que se pudo obtener, como recién partió el programa, estamos justo en la direccion que nos importa mantener como inicial o un pseudo home
    {
        perror("holysh: error al obtener directorio inicial");
    }
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

        int contador_de_argumentos = parse_command(line, argumentos, 128);

        if (contador_de_argumentos == 0)
        {
            continue; // Si el usuario hace enter, pues pasamos de largo nomas
        }
        argumentos[contador_de_argumentos] =
            NULL; // Recordar que exec necesita un NULL al final, se lo chantamos
                  // aca a lo cerdo
        if (strcmp(argumentos[0], "cd") == 0)
        {
            if (argumentos[1] == NULL) // si no hay segundo argumento, (e.i solo "cd") nos vamos al dir_inicial
            {
                if (chdir(dir_inicial) != 0)
                {
                    perror("holysh: cd");
                }
            }
            else
            {
                // Si el usuario escribió "cd [carpeta]", intentamos cambiar a argumentos[1] o [carpeta] altiro
                if (chdir(argumentos[1]) != 0) // Si el resultado es distinto de 0 (es decir, falló), mostramos el error con perror
                {
                    perror("holysh: cd");
                }
            }
            
            continue;
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
