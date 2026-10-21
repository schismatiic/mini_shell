#include <stdio.h>
#include <sys/wait.h>

void matar_hijos(void) {
  int estado;
  pid_t pid;

  while ((pid = waitpid(-1, &estado, WNOHANG)) > 0) {
    printf("[ %d ] proceso terminado\n", pid);
  }
}
