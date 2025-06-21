CUR_DIR := .
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src
INC_DIR := $(CUR_DIR)/inc
LIB_DIR := $(CUR_DIR)/lib/static

# OBJ_NAME := $(OBJ_DIR)/%.o
# INC_NAME := $(INC_DIR)/*.h
# SRC_NAME := $(SRC_DIR)/%.c

CC := $(CC)

# $(OBJ_NAME): $(SRC_NAME) $(INC_NAME)
# 	$(CC) -c -o $@ $< -I $(INC_DIR)/

create_object:
	@if [ ! -d $(OBJ_DIR) ]; then \
		echo "Directory '$(OBJ_DIR)' does not exist. Creating..."; \
		mkdir $(OBJ_DIR); \
	else \
		echo "Directory '$(OBJ_DIR)' already exists."; \
	fi

	$(CC) -c -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c -I $(INC_DIR)/
	$(CC) -c -o $(OBJ_DIR)/isPrime.o $(SRC_DIR)/isPrime.c -I $(INC_DIR)/

create_lib: create_object
	@if [ ! -d $(LIB_DIR) ]; then \
		echo "Directory '$(LIB_DIR)' does not exist. Creating..."; \
		mkdir -p $(LIB_DIR); \
	else \
		echo "Directory '$(LIB_DIR)' already exists."; \
	fi

	ar rcs $(LIB_DIR)/libisPrime.a $(OBJ_DIR)/isPrime.o $(OBJ_DIR)/main.o

linking: create_lib
	@if [ ! -d $(BIN_DIR) ]; then \
		echo "Directory '$(BIN_DIR)' does not exist. Creating..."; \
		mkdir $(BIN_DIR); \
	else \
		echo "Directory '$(BIN_DIR)' already exists."; \
	fi

	$(CC) $(OBJ_DIR)/main.o -L$(LIB_DIR)/ -lisPrime -lm -o $(BIN_DIR)/static_ex

run: linking
	@echo "Run complete!!"
	./$(BIN_DIR)/static_ex

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(dir $(LIB_DIR))
	rm -rf $(BIN_DIR)