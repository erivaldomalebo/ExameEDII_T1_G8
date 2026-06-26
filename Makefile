# ============================================================
# Makefile — UniConnect
#
# Estrutura de pastas esperada:
#   include/    .h dos módulos (interesse.h, utilizador.h, ...)
#   estrutura/  utils.h, utils.c, TADs.h, TADs.c
#   src/        .c dos módulos (interesse.c, utilizador.c, ...)
#
# Uso:
#   make / mingw32-make         -> compila tudo para exec/uniconnect
#   make run      -> compila e executa
#   make clean    -> apaga .o e o executável
# ============================================================

CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -g
INCLUDES := -Iinclude -Iestrutura

SRC_DIR    := src
STRUCT_DIR := estrutura

#MAIN FORA DAS PASTAS
MAIN := main.c

SOURCES := $(MAIN) \
           $(wildcard $(SRC_DIR)/*.c) \
           $(wildcard $(STRUCT_DIR)/*.c)

OBJECTS := $(SOURCES:.c=.o)

TARGET := uniconnect.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)