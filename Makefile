CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ -Ilibs/glib/includes -Ilibs/reslib/includes
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
GLIB	= -L. -lglib
RESLIB	= -L. -lreslib
LIBGLIB	= libglib.a
LIBRESLIB	= libreslib.a

NAME	= bomberman
RM		= rm -f

SRC		= \
		src/frame_game.c \
		src/frame_menu.c \
		src/main_test.c \

OBJ		= $(SRC:.c=.o)

makeglib:
	cd libs/glib && $(MAKE)
	cp libs/glib/$(LIBGLIB) .

makereslib:
	cd libs/reslib && $(MAKE)
	cp libs/reslib/$(LIBRESLIB) .

all: $(NAME)

$(NAME): makeglib $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(NAME) $(SDL) $(GLIB)

clean:
	$(RM) $(OBJ)
	cd libs/glib && $(MAKE) clean
	cd libs/reslib && $(MAKE) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBGLIB)
	$(RM) $(LIRESGLIB)
	cd libs/glib && $(MAKE) fclean
	cd libs/reslib && $(MAKE) fclean

re: fclean all

.PHONY: makeglib all $(NAME) clean fclean re
