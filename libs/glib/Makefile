CC		= gcc
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ $(SDL)

NAME	= libglib.a
RM		= rm -f

SRC		= \
		src/drawables.c \
		src/window.c \
		src/frame.c \
		src/sprite.c \
		src/sprite_animated.c \
		src/text.c \
		src/button.c \
		src/inputbox.c \
		src/utils.c \

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