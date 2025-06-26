NAME := minishell
TEST_BIN := tests

# Compiler, flags and args
CC := cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
# CFLAGS += $(foreach dir, $(shell find $(INC_DIR) -type d), -I$(dir))
LDFLAGS = -lreadline
VAL_FLAGS := --leak-check=full --quiet --show-leak-kinds=all --track-fds=yes --trace-children=yes --track-origins=yes --suppressions=./rl.supp
GDB_FLAGS := --quiet --args
FUZZER_ARGS = $(FUZZ_DIR)/parsing $(FUZZ_DIR)/seed_corpus/ -artifact_prefix=$(FUZZ_DIR)/crash/ -max_len=32 -only_ascii=0 -print_final_stats=1

# OS detection
UNAME_P := $(shell uname -p)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -DLINUX
endif

# Directories
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := test
FUZZ_DIR := $(TEST_DIR)/fuzzer

# Sources and objects
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
FUZZ_SRC := $(shell find $(SRC_DIR)/tools $(SRC_DIR)/parsing -type f -name "*.c") $(SRC_DIR)/error.c
FUZZ_OBJ := $(filter $(OBJ_DIR)/parsing/% $(OBJ_DIR)/tools/%, $(OBJ)) $(OBJ_DIR)/error.o
TEST_SRC := $(shell find $(TEST_DIR) -type f -name "*.c")
TEST_OBJ := $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/$(TEST_DIR)/%.o, $(TEST_SRC))
TEST_LINK_OBJ := $(filter-out $(OBJ_DIR)/main.o, $(OBJ)) $(TEST_OBJ)

# ============================================================================ #
#        Main rules                                                            #
# ============================================================================ #
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@./update_progress_bar.sh "Compiling $(NAME):"

re: fclean all

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

# ============================================================================ #
#        Test rules                                                            #
# ============================================================================ #
test: CFLAGS += -DINCLUDE_TEST_HEADER
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(LIBFT) $(TEST_LINK_OBJ)
	$(CC) $(CFLAGS) -o $@ $(TEST_LINK_OBJ) $(LDFLAGS)

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

g: CFLAGS += -g
g: re

valgrind: CFLAGS += -g
valgrind: re
	valgrind $(VAL_FLAGS) ./$(NAME)

gdb: CFLAGS += -g
gdb: re
	gdb $(GDB_FLAGS) ./$(NAME)

val_test: CFLAGS += -g -DINCLUDE_TEST_HEADER
val_test: fclean $(TEST_BIN)
	valgrind $(VAL_FLAGS) ./$(TEST_BIN)

gdb_test: CFLAGS += -g -DINCLUDE_TEST_HEADER
gdb_test: fclean $(TEST_BIN)
	gdb $(GDB_FLAGS) ./$(TEST_BIN)

macro: CFLAGS += -D_GNU_SOURCE -DINCLUDE_TEST_MACRO -g
macro: LDFLAGS += -ldl
macro: re

fuzz: CFLAGS += -g
fuzz: re
	clang -g -O1 -fsanitize=fuzzer,address,signed-integer-overflow $(FUZZ_DIR)/fuzzer.c -o fuzz -I$(INC_DIR) $(FUZZ_OBJ) $(LDFLAGS)
	./fuzz $(FUZZER_ARGS)

.PHONY: all re clean fclean test g valgrind gdb val_test gdb_test macro fuzz
