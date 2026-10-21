#include "memory.h"
#include <stdio.h>
#include <string.h>

// Esta función busca en base al nombre que le pasemos como argumento. Primero abre /proc/meminfo, leé sus líneas una por una, separa el nombre del campo
// compara el nombre con el que le pasamos como argumenti y devuelve el valor si coincide
// En resumen, por ahora, field va a recibir "MemTotal:" o "MemAvailable:" y devolverá los kB de cada uno
static long read_memory_value(const char *field)
{
    FILE *file = fopen("/proc/meminfo", "r"); // Acá fopen() abre el archivo en modeo lectura (r)
    // Error handling: si fopen devuelve NULL signifca que no pudo abrir el archivo
    if (file == NULL)
    {
        perror("holysh: meminfo");
        return -1;
    }
    char line[256];  // Buffer para guardar una línea completa del archivo
    char name[64];   // Esto va a almacenar el nombre del campo (por ahora, otra vez, "MemTotal:" o "MemAvailable:")
    long value = -1; // Y esto almacena el resultado en kB. Usé long porque, al parecer, tira valores muy altos
    while (fgets(line, sizeof(line), file) != NULL)
    {
        long current_value;

        if (sscanf(line, "%63s %ld kB", name, &current_value) == 2)
        {
            if (strcmp(name, field) == 0)
            {
                value = current_value;
                break;
            }
        }
    }
    fclose(file);
    return value;
}

// Bueno, como dije antes, estas funciones se encargan de pasarle un el char que se va a buscar como argumento a read_memory_value
long get_total_memory(void)
{
    return read_memory_value("MemTotal:");
}
long get_available_memory(void)
{
    return read_memory_value("MemAvailable:");
}