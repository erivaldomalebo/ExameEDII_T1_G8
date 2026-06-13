# Definir o compilador
CC = gcc

# Definir as flags de compilação
CFLAGS = -Iinclude -Wall -std=c99

# Lista de arquivos fonte
# SRC = main.c
SRC = $(wildcard *.c)

# Nome do executável
OUT = programa

# Regra principal para compilar o projeto
all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) 
# Cria o executável a partir dos arquivos fonte

# Regra para executar o programa após compilação
run: all
	./$(OUT)

# Limpar os arquivos compilados (como o executável)
clean:
	rm -f $(OUT)