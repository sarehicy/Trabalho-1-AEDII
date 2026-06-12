CC = gcc
CFLAGS =

SRC = main.c \
      auxiliares.c \
      cabecalhos.c \
      escrever_arq.c \
      func_buscar.c \
      func_criar.c \
      func_insercao.c \
      func_remocao.c \
      func_atualizar.c \
      ler_arq.c \
      registros.c 

OBJ = $(SRC:.c=.o)

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

rebuild: clean all

run:
	./main