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

CFLAGS := -Wall -Wextra -Werror -fPIC -shared -I$(INCLUDE_DIR)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all : $(NAME)

$(NAME) : Makefile $(OBJS) | $(LIB_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread
	ln -sf $(NAME_NO_PATH) $(SYMLINK)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

test: re $(TEST_PROG)
	LD_PRELOAD=./$(SYMLINK) ./$(TEST_PROG)

$(TEST_PROG): tests/main.c $(NAME)
	$(CC) -o $@ $< -I$(INCLUDE_DIR) -L$(LIB_DIR) -lft_malloc -Wl,-rpath=$(LIB_DIR)

clean :
	rm -f $(TEST_PROG)
	rm -rf $(OBJ_DIR)
	rm -f test0
	rm -f test1
	rm -f test2
	rm -f test3
	rm -f test4
	rm -f test5

fclean : clean
	rm -rf $(LIB_DIR)

re : fclean all

test0w: clean
	$(CC) -o test0 tests/test0.c && /usr/bin/time -v ./test0
test0: clean
	$(CC) -o test0 tests/test0.c && ./tests/run_linux.sh /usr/bin/time -v ./test0
test1w: clean
	$(CC) -o test1 tests/test1.c && /usr/bin/time -v ./test1
test1: clean
	$(CC) -o test1 tests/test1.c && ./tests/run_linux.sh /usr/bin/time -v ./test1
test2w: clean
	$(CC) -o test2 tests/test2.c && /usr/bin/time -v ./test2
test2: clean
	$(CC) -o test2 tests/test2.c && ./tests/run_linux.sh /usr/bin/time -v ./test2
test3w: clean
	$(CC) -o test3 tests/test3.c && ./test3
test3: clean
	$(CC) -o test3 tests/test3.c -L./lib -lft_malloc && ./tests/run_linux.sh ./test3
test4w: clean
	$(CC) -o test4 tests/test4.c && ./test4
test4: clean
	$(CC) -o test4 tests/test4.c -L./lib -lft_malloc && ./tests/run_linux.sh ./test4
test5w: clean
	$(CC) -o test5 tests/test5.c && ./test5
test5: clean
	$(CC) -o test5 tests/test5.c -L./lib -lft_malloc && ./tests/run_linux.sh ./test5

.PHONY	: all clean fclean re test test0