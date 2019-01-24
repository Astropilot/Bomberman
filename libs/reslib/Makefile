CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/

NAME	= libreslib.a
RM		= rm -f

SRC		= \
		src/client.c \
		src/reslib.c \

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(NAME) clean fclean re
