NAME	= $(LIB_DIR)/$(NAME_NO_PATH)
NAME_NO_PATH = libft_malloc_$(HOSTTYPE).so
SYMLINK = $(LIB_DIR)/libft_malloc.so

INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib

SRCS =	malloc.c \
		print.c \
		block.c \
		pages.c \
		show_alloc_mem.c \
		free.c \
		realloc.c \
		tools.c
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))
HEADER = libft_malloc.h

vpath %.c $(SRC_DIR)
vpath %.h $(INCLUDE_DIR)

CC := gcc

TEST_PROG := testprog

CFLAGS := -Wall -Wextra -Werror -shared -fPIC -I$(INCLUDE_DIR)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all : $(NAME)

$(NAME) : Makefile $(OBJS) | $(LIB_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	ln -sf $(NAME_NO_PATH) $(SYMLINK)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

test: re $(TEST_PROG)
	LD_PRELOAD=./$(SYMLINK) ./$(TEST_PROG)

$(TEST_PROG): testfiles/main.c $(NAME)
	$(CC) -o $@ $< -I$(INCLUDE_DIR) -L$(LIB_DIR) -lft_malloc -Wl,-rpath=$(LIB_DIR)

clean :
	rm -f $(TEST_PROG)
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(LIB_DIR)

re : fclean all

.PHONY	: all clean fclean re test