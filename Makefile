CXX = g++
CXXFLAGS = -std=c++14 -Wall -Iinclude

SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin

SRCS = $(SRC_DIR)/FileSystem.cpp
OBJS = $(SRCS:.cpp=.o)

TESTS = $(TEST_DIR)/FileSystemTest.cpp

BIN = $(BIN_DIR)/filesystem
TEST_BIN = $(BIN_DIR)/filesystem_test

.PHONY: all test run clean dirs

all: dirs $(BIN)

dirs:
	mkdir -p $(BIN_DIR)

$(BIN): $(SRCS)
	@echo "🔨 Compilando $(BIN)..."
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_BIN): $(TESTS) $(SRCS) | dirs
	@echo "🧪 Compilando testes..."
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(TEST_BIN)
	@echo "🚀 Rodando testes..."
	./$(TEST_BIN)

run: all
	@echo "🚀 Executando o programa..."
	./$(BIN)

clean:
	@echo "🧹 Limpando arquivos compilados..."
	rm -rf $(BIN_DIR)
