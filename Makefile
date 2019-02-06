CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -lpthread -Iincludes/ -Ilibs/glib/includes -Ilibs/reslib/includes
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
GLIB	= -L. -lglib
RESLIB	= -L. -lreslib
LIBGLIB	= libglib.a
LIBRESLIB	= libreslib.a

TARGET	= bomberman
RM		= rm -f

SRC		= \
		src/frame_game.c \
		src/frame_main_menu.c \
		src/frame_host_menu.c \
		src/frame_join_menu.c \
		src/main.c

#SRC			= \
		src/network_test.c

OBJ		= $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): makeglib makereslib $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(SDL) $(GLIB) $(RESLIB)

makeglib:
	cd libs/glib && $(MAKE)
	cp libs/glib/$(LIBGLIB) .

makereslib:
	cd libs/reslib && $(MAKE)
	cp libs/reslib/$(LIBRESLIB) .

.PHONY: clean fclean re

clean:
	$(RM) $(OBJ)
	$(RM) $(LIBGLIB)
	$(RM) $(LIBRESLIB)
	cd libs/glib && $(MAKE) clean
	cd libs/reslib && $(MAKE) clean

fclean: clean
	$(RM) $(TARGET)
	cd libs/glib && $(MAKE) fclean
	cd libs/reslib && $(MAKE) fclean

re: fclean all
