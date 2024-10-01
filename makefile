# Nome do executável
TARGET = main

# Diretórios
SRC_DIR = .
BUILD_DIR = build

# Fontes
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Flags do compilador
CC = gcc
CFLAGS = -g -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`

# Regra padrão
all: $(TARGET)

# Regra para o executável
$(TARGET): $(OBJ_FILES)
	$(CC) -o $@ $^ $(LDFLAGS)

# Regra para compilar arquivos .c em .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Para executar
# Para executar
run: all
	./$(TARGET)

.PHONY: all clean run