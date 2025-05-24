CUR_DIR := .
OBJ_DIR := $(CUR_DIR)/obj
BIN_DIR := $(CUR_DIR)/bin
SRC_DIR := $(CUR_DIR)/src
INC_DIR := $(CUR_DIR)/inc
LIB_DIR := $(CUR_DIR)/lib/shared

CC := $(CC)


create_object:
	$(CC) -c -fPIC $(SRC_DIR)/main.c    -o $(OBJ_DIR)/main.o    -I $(INC_DIR)/
	$(CC) -c -fPIC $(SRC_DIR)/isPrime.c -o $(OBJ_DIR)/isPrime.o -I $(INC_DIR)/

create_lib: create_object
	$(CC) -shared $(OBJ_DIR)/isPrime.o $(OBJ_DIR)/main.o -o $(LIB_DIR)/libisPrime.so

linking: create_lib
	$(CC)  $(OBJ_DIR)/main.o -L$(LIB_DIR)/ -lisPrime -lm -o $(BIN_DIR)/shared_ex

run: linking
	@echo "Run complete!!"
	./$(BIN_DIR)/shared_ex

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_DIR)/libisPrime.a
	rm -rf $(BIN_DIR)/shared_ex