CUR_DIR := .
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src
INC_DIR := $(CUR_DIR)/inc
LIB_DIR := $(CUR_DIR)/lib/static

OBJ_NAME := $(OBJ_DIR)/%.o
INC_NAME := $(INC_DIR)/*.h
SRC_NAME := $(SRC_DIR)/%.c

CC := $(CC)

# $(OBJ_NAME): $(SRC_NAME) $(INC_NAME)
# 	$(CC) -c -o $@ $< -I $(INC_DIR)/

create_object:
	$(CC) -c -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c -I $(INC_DIR)/
	$(CC) -c -o $(OBJ_DIR)/isPrime.o $(SRC_DIR)/isPrime.c -I $(INC_DIR)/

create_lib: create_object
	ar rcs $(LIB_DIR)/libisPrime.a $(OBJ_DIR)/isPrime.o $(OBJ_DIR)/main.o

linking: create_lib
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_DIR)/ -lisPrime -lm -o $(BIN_DIR)/static_ex

run: linking
	@echo "Run complete!!"
	./$(BIN_DIR)/static_ex

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_DIR)/libisPrime.a
	rm -rf $(BIN_DIR)/static_ex