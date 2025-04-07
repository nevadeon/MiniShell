NAME := so_long
TEST_BIN := tests

# Compiler, flags and args
CC := cc
CFLAGS = -O3 -Wall -Wextra -I$(INC_DIR)
LDFLAGS =
VALGRIND_FLAGS := --quiet --leak-check=full --show-leak-kinds=all
GDB_FLAGS := --quiet --args
GDB_VALGRIND_ARGS :=

# Directories
INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := test

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

$(NAME): $(LIBFT) $(OBJ)
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
#        Library rules                                                         #
# ============================================================================ #
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

libre:
	@$(MAKE) -s -C $(LIBFT_DIR) re

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

valgrind: CFLAGS += -g
valgrind: libtest re
	valgrind $(VALGRIND_FLAGS) ./$(NAME) $(GDB_VALGRIND_ARGS)

gdb: CFLAGS += -g
gdb: libtest re
	gdb $(GDB_FLAGS) ./$(NAME) $(GDB_VALGRIND_ARGS)

.PHONY: all clean fclean lclean re libre libtest test valgrind gdb
