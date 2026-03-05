PROJECT     = hashtable_project
TARGET      = main
LIB_NAME    = libhashtable

SRC_DIR     = sources
INC_DIR     = headers
BUILD_DIR   = build
OBJ_DIR     = $(BUILD_DIR)/obj
LIB_DIR     = $(BUILD_DIR)/lib
BIN_DIR     = $(BUILD_DIR)/bin

SRCS        = $(wildcard $(SRC_DIR)/*.c)
MAIN_SRC    = main.c

OBJS        = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
MAIN_OBJ    = $(OBJ_DIR)/main.o

HEADERS     = $(wildcard $(INC_DIR)/*.h)

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -pedantic -std=c17 -I$(INC_DIR) -fPIC
LDFLAGS     = -L$(LIB_DIR)
LDLIBS      = 

.PHONY: all static dynamic clean debug release help

all: static dynamic $(BIN_DIR)/$(TARGET)_static $(BIN_DIR)/$(TARGET)_dynamic

$(BUILD_DIR) $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR):
	@mkdir -p $@

static: $(LIB_DIR)/$(LIB_NAME).a

$(LIB_DIR)/$(LIB_NAME).a: $(OBJS) | $(LIB_DIR)
	ar rcs $@ $^
	ranlib $@

dynamic: $(LIB_DIR)/$(LIB_NAME).so

$(LIB_DIR)/$(LIB_NAME).so: $(OBJS) | $(LIB_DIR)
	$(CC) -shared -o $@ $^

$(BIN_DIR)/$(TARGET)_static: $(MAIN_OBJ) $(LIB_DIR)/$(LIB_NAME).a | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) $(LDFLAGS) -l:$(LIB_NAME).a

$(BIN_DIR)/$(TARGET)_dynamic: $(MAIN_OBJ) $(LIB_DIR)/$(LIB_NAME).so | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) $(LDFLAGS) -lhashtable -Wl,-rpath,$(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(MAIN_SRC) $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g -O0 -DDEBUG
debug: all

release: CFLAGS += -O3 -DNDEBUG
release: all

run_static: $(BIN_DIR)/$(TARGET)_static
	@$(BIN_DIR)/$(TARGET)_static

run_dynamic: $(BIN_DIR)/$(TARGET)_dynamic
	@LD_LIBRARY_PATH=$(LIB_DIR):$(LD_LIBRARY_PATH) $(BIN_DIR)/$(TARGET)_dynamic


clean:
	rm -rf $(BUILD_DIR)
