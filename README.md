# Repositorio miniShell Sistemas Operativos.

##  Integrantes
// Cambiar por  nombres reales al entregar

[Integrante 1](https://github.com/schismatiic)
[Integrante 2](https://github.com/Nurodayo)
[Integrante 3](https://github.com/Andreh-Achepe)
[Integrante 4](https://github.com/ELBA21)

## Evaluacion

### Normas (parafraseado)

1. El resultado de Aprendizaje a calificar es: Reconoce la infraestructura computacional de un sistema operativo, identificando sus principios de diseño y metricas de desempeño, con el fin de implementar soluciones que incorporen planificacion de procesos e hilos.

2. La evaluacion sera de caracter grupal.

3. La entrega del proyecto se hara efectiva el 21 de octubre del 2025??? hasta las 11:30hrs. En clases.
4. Es obligatorio el uso de fork y funciones de la familia exec en la resolucion del proyecto.
5. Se tendra que mostrar una demostracion en vivio junto con la revision del codigo. Max 10 minutos

### Enunciado
- Implementar una mini-shell en C para Linux que ejecute programas externos, gestione procesos en primer/segundo plano, evite zombies y que al terminar cada proceso hijo muestre un reporte de memoria (ejemplo: memoria disponible del sistema y/o uso de memoria del hijo). Algunos requisitos de la aplicacion son:
  - Prompt y lectura de comandos:
    - Mostrar un prompt tipo: `minish>` e ingresar lineas y/o comandos.
    - Soportar ejecucion de un programa con argumentos: ejemplo `ls -l /tmp`.
  - Ejecucion de procesos y sincronizacion.
  - Comandos internos minimos:
    - `cd [dir]`: cambia de directorio.
    - `exit`: termina la shel liberando recursos y mostraodn un resumen final de memoria.
    - `help` lista de uso.
  - Al salir la shell (exit), mostrar un resumen respecto a los procesos ejecutados y la memoria utilizada.
 
## Documentacion
 
### main.c
- Simplemene ejecuta la terminal.

### shell.c
- Ejecuta las funciones propias de la sell, no depende de procesos externos y orquesta
