#define _DEFAULT_SOURCE
#include "matar.h"
#include "stats.h"
#include <stdio.h>
#include <sys/resource.h>
#include <sys/wait.h>

void matar_hijos(void)
{
  int estado;
  pid_t pid;
  struct rusage uso;

  while ((pid = wait4(-1, &estado, WNOHANG, &uso)) > 0)
  {
    register_process(pid, uso.ru_maxrss);
  }
}
