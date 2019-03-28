#*******************************************************************************
# PROJECT: gLib
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
SDL		= -lSDL2 -lSDL2_ttf -lSDL2_image
CFLAGS	= -Wall -Wextra -Werror -g -Iincludes/ $(SDL)

NAME	= libglib.a
RM		= rm -f

SRC		= \
		src/window.c \
		src/frame.c \
		src/sprite.c \
		src/sprite_animated.c \
		src/sprites_animated.c \
		src/text.c \
		src/button.c \
		src/inputbox.c \
		src/utils.c \
		src/network/sockets.c \
		src/network/packer.c \
		src/network/client.c \
		src/network/server.c

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
