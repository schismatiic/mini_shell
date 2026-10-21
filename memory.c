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
    char line[256];                                 // Buffer para guardar una línea completa del archivo
    char name[64];                                  // Esto va a almacenar el nombre del campo (por ahora, otra vez, "MemTotal:" o "MemAvailable:")
    long value = -1;                                // Y esto almacena el resultado en kB. Usé long porque, al parecer, tira valores muy altos
    while (fgets(line, sizeof(line), file) != NULL) // fget() leé una línea de file y la almacena en line
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

// La siguiente función es muy parecida a read_memory_value, pero con algunas diferencias. Para empezar, recibe un pid ya que
// se encarga de consultar la memoria de un proceso en específico
long get_process_memory(pid_t pid)
{
    char path[64];
    // LO siguiente es casi que la única diferencia con read_memory_value
    // Para que se entienda, esta vez file utilizará un path que depende del pid, eso D:
    snprintf(path, sizeof(path), "/proc/%ld/status", (long)pid); // Construye la path /proc/[pid]/status
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        perror("holysh: process memory");
        return -1;
    }
    char line[256];
    char name[64];
    long value = -1;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        long current_value;
        if (sscanf(line, "%63s %ld kB", name, &current_value) == 2)
        {
            if (strcmp(name, "VmRSS:") == 0) // Por si acaso, VmRSS son siglas de Virtual Memory Resident Set Size
            {
                value = current_value;
                break;
            }
        }
    }
    fclose(file);
    return value;
}