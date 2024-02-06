NAME		=	libft_malloc_$(HOSTTYPE).so
LN_NAME		=	libft_malloc.so

ifeq ($(HOSTTYPE), )
	HOSTTYPE := $(shell uname -n)_$(shell uname -s)
endif

OBJ_DIR =	./objs
SRC_DIR =	./srcs

SRC		=	ft_malloc.c \
			print_hexa.c

OBJ		=	$(SRC:.c=.o)
OBJS	=	$(OBJ:%=$(OBJ_DIR)/%)

AC		=	ar rc
RANLIB	=	ranlib
RM		=	rm -rf
ECHO	=	echo

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LDFLAGS =	-L.
LDLIBS  =	-l

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LN_NAME)
	$(RM) test

re: fclean all

$(NAME): $(OBJS)
	$(CC) $(OBJS) -shared -o $(NAME)
	ln -sf $(NAME) $(LN_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -I. -c -fPIC $< -o $@

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

test: $(NAME)
	gcc test.c -o test
	LD_PRELOAD=./$(LN_NAME) ./test

ls: $(NAME)
	LD_PRELOAD=./$(LN_NAME) ls -lR ~/

emacs: $(NAME)
	LD_PRELOAD=./$(LN_NAME) emacs test.c

.PHONY: all clean fclean re test ls emacs
