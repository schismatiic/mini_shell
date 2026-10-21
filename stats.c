#include "stats.h"
#include <stdio.h>

static int total_processes = 0;
static long total_memory = 0;

void register_process(pid_t pid, long memory_kb)
{
    total_processes++;
    if (memory_kb >= 0)
    {
        total_memory += memory_kb;
    }
    printf("Proceso %ld terminado\n", (long)pid);
    if (memory_kb >= 0)
    {
        printf("Memoria utilizada: %ld kB\n", memory_kb);
    }
    else
    {
        printf("No se pudo obtener la memoria utilizada\n");
    }
}
void show_stats(void)
{
    printf("\n");
    printf("========== Holy † Stats ==========\n"); // Amén
    printf("Procesos registrados: %d\n", total_processes);
    printf("Memoria acumulada: %ld kB\n", total_memory);
    printf("=======================================\n");
    printf("\n");
}