#*******************************************************************************
# PROJECT: Bomberman
#
# AUTHORS: Yohann Martin, Aziz Hamide, Gauthier Desplanque, William Weber
#
# DATE CREATED: 01/16/2019
#
# Copyright (c) 2019 Yohann MARTIN (@Astropilot). All rights reserved.
#
# Licensed under the MIT License. See LICENSE file in the project root for full
# license information.
#*******************************************************************************

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ -Ilibs/glib/includes
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
