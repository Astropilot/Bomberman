CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ -Ilibs/glib/includes
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
GLIB	= -L. -lglib
RESLIB	= -L. -lreslib
LIBGLIB	= libglib.a

NAME	= bomberman
RM		= rm -f

SRC		= \
		src/frame_game.c \
		src/frame_main_menu.c \
		src/frame_host_menu.c \
		src/frame_join_menu.c \
		src/main.c \

OBJ		= $(SRC:.c=.o)

makeglib:
	cd libs/glib && $(MAKE)
	cp libs/glib/$(LIBGLIB) .

all: $(NAME)

$(NAME): makeglib $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(NAME) $(SDL) $(GLIB)

clean:
	$(RM) $(OBJ)
	cd libs/glib && $(MAKE) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBGLIB)
	cd libs/glib && $(MAKE) fclean

re: fclean all

.PHONY: makeglib all $(NAME) clean fclean re
