#ifndef STATS_H
#define STATS_H
#include <sys/types.h>

void register_process(pid_t pid, long memory_kb);
void show_stats(void);

#endif