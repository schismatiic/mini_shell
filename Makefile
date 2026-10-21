# Con esto podemos automatizar la compilación del proyecto
# Para utilizarlo, hay que ir a la raíz y usar alguno de estos comandos:
# make			------> Compila el proyecto
# ./minishell	------> Ejecuta el programs
# make clean	------> Elimina el ejecutable


CC = gcc
CFLAGS = -Wall -Wextra -Wno-implicit-function-declaration -std=c11 # Esta variable contiene las opciones que se le pasan al compilador

TARGET = minishell
SRCS = main.c shell.c parser.c process.c memory.c matar.c


# all compila y clean elimina el ejecutable
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
clean:
	rm -f $(TARGET)
.PHONY: all clean
