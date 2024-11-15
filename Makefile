# Diretórios
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

# Binário
TARGET = $(BIN_DIR)/Apparatus-operandi

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(INCLUDE_DIR) -I"C:/Program Files/OpenSSL-Win64/include"
LDFLAGS = -L"C:/Program Files/OpenSSL-Win64/lib" -lssl -lcrypto -lstdc++fs

# Fontes e objetos
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/auth.cpp \
          $(SRC_DIR)/file_system.cpp \
          $(SRC_DIR)/process.cpp \
          $(SRC_DIR)/utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regras
all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
    $(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Regras específicas para compilar .cpp em .o com caminhos completos
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Garantir que o diretório bin existe
$(BIN_DIR):
    mkdir -p $(BIN_DIR)

clean:
    rm -rf $(OBJECTS) $(TARGET)

.PHONY: all clean
