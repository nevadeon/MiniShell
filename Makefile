NAME := minishell
TEST_BIN := tests

# Compiler, flags and args
CC := cc
CFLAGS = -Wall -Wextra -I$(INC_DIR)
LDFLAGS = -lreadline
VALGRIND_FLAGS := --quiet --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --track-origins=yes --suppressions=./rl.supp
GDB_FLAGS := --quiet --args
GDB_VALGRIND_ARGS =

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

# Include subdirectories
CFLAGS += $(foreach dir, $(shell find $(INC_DIR) -type d), -I$(dir))

# Sources and objects
SRC := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
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

macro: CFLAGS += -D_GNU_SOURCE -DINCLUDE_TEST_MACRO -g
macro: LDFLAGS += -ldl
macro: re

g: CFLAGS += -g
g: re

valgrind: g
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(GDB_VALGRIND_ARGS)

gdb: g
	gdb $(GDB_FLAGS) ./$(NAME) $(GDB_VALGRIND_ARGS)

valgrind_test: CFLAGS += -g -DINCLUDE_TEST_HEADER
valgrind_test: fclean $(TEST_BIN)
	valgrind $(VALGRIND_FLAGS) ./$(TEST_BIN)

gdb_test: CFLAGS += -g -DINCLUDE_TEST_HEADER
gdb_test: fclean $(TEST_BIN)
	gdb $(GDB_FLAGS) ./$(TEST_BIN)

.PHONY: all re clean fclean test valgrind gdb valgrind_test gdb_test macro g
