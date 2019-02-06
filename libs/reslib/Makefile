CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ -lpthread

NAME	= libreslib.a
RM		= rm -f

SRC		= \
		src/reslib.c \
		src/packer.c \
		src/message.c \
		src/client.c \
		src/server.c \

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

.PHONY: clean fclean re

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
