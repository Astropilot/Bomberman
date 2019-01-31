CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ -Ilibs/glib/includes
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
GLIB	= -L. -lglib
LIBGLIB	= libglib.a

TARGET	= bomberman
RM		= rm -f

SRC		= \
		src/frame_game.c \
		src/frame_main_menu.c \
		src/frame_host_menu.c \
		src/frame_join_menu.c \
		src/main.c \

OBJ		= $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): makeglib $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(SDL) $(GLIB)

makeglib:
	cd libs/glib && $(MAKE)
	cp libs/glib/$(LIBGLIB) .

.PHONY: clean fclean re

clean:
	$(RM) $(OBJ)
	$(RM) $(LIBGLIB)
	cd libs/glib && $(MAKE) clean

fclean: clean
	$(RM) $(TARGET)
	cd libs/glib && $(MAKE) fclean

re: fclean all
