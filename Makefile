CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -lpthread -Iincludes/ -Ilibs/glib/includes
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
LIBGLIB	= libglib.a

FOLDER  = build/
TARGET	= bomberman
GLIB	= -L$(FOLDER) -lglib
RM		= rm -f

SRC		= \
		$(wildcard src/core/*.c) \
		$(wildcard src/ui/*.c) \
		$(wildcard src/network/packets/*.c) \
		$(wildcard src/network/game/*.c) \
		src/main.c

OBJ		= $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): makeglib $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(FOLDER)$(TARGET) $(SDL) $(GLIB)

makeglib:
	cd libs/glib && $(MAKE)
	cp libs/glib/$(LIBGLIB) $(FOLDER)

.PHONY: clean fclean re

clean:
	$(RM) $(OBJ)
	$(RM) $(FOLDER)$(LIBGLIB)
	cd libs/glib && $(MAKE) clean

fclean: clean
	$(RM) $(FOLDER)$(TARGET)
	cd libs/glib && $(MAKE) fclean

re: fclean all
