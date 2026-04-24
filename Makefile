# Nome do executável
TARGET = programa

# Compilador
CXX = g++

# Flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Diretórios
SRC_DIRS = src tests
OBJ_DIR = obj

# Arquivos fonte
SRCS = $(shell find $(SRC_DIRS) -name "*.cpp")

# Converte src/...cpp → obj/...o
OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilação genérica (FUNCIONA PRA QUALQUER PASTA)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

rebuild: clean all