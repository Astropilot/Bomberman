CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -lpthread -Iincludes/ -Ilibs/glib/includes -Ilibs/reslib/includes
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
LIBGLIB	= libglib.a
LIBRESLIB	= libreslib.a

FOLDER  = build/
TARGET	= bomberman
GLIB	= -L$(FOLDER) -lglib
RESLIB	= -L$(FOLDER) -lreslib
RM		= rm -f

SRC		= \
		$(wildcard src/core/*.c) \
		$(wildcard src/ui/*.c) \
		$(wildcard src/network/packets/*.c) \
		$(wildcard src/network/game/*.c) \
		src/main.c

OBJ		= $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): makeglib makereslib $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(FOLDER)$(TARGET) $(SDL) $(GLIB) $(RESLIB)

makeglib:
	cd libs/glib && $(MAKE)
	cp libs/glib/$(LIBGLIB) $(FOLDER)

makereslib:
	cd libs/reslib && $(MAKE)
	cp libs/reslib/$(LIBRESLIB) $(FOLDER)

.PHONY: clean fclean re

clean:
	$(RM) $(OBJ)
	$(RM) $(FOLDER)$(LIBGLIB)
	$(RM) $(FOLDER)$(LIBRESLIB)
	cd libs/glib && $(MAKE) clean
	cd libs/reslib && $(MAKE) clean

fclean: clean
	$(RM) $(FOLDER)$(TARGET)
	cd libs/glib && $(MAKE) fclean
	cd libs/reslib && $(MAKE) fclean

re: fclean all
