# Diretórios
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include
AUTH_DIR = $(SRC_DIR)/auth
PROCESS_DIR = $(SRC_DIR)/process
FILE_SYSTEM_DIR = $(SRC_DIR)/file_system

# Binário
TARGET = $(BIN_DIR)/Apparatus-operandi

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(INCLUDE_DIR) -lssl -lcrypto

# Fontes e objetos
SOURCES = $(SRC_DIR)/shell.cpp \
          $(AUTH_DIR)/auth.cpp \
          $(PROCESS_DIR)/process_manager.cpp \
          $(FILE_SYSTEM_DIR)/file_system.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Regras
all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)  # Cria o diretório bin caso não exista
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*.o $(TARGET)

.PHONY: all clean
