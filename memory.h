#ifndef MEMORY_H
#define MEMORY_H
#include <sys/types.h>

long get_total_memory(void);
long get_available_memory(void);
long get_process_memory(pid_t pid);

#endif