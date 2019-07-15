# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 08:25:55 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/07/06 16:49:08 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libSnakeAllegro.so

INCL = $$HOME/.brew/Cellar/allegro/*/include
LIBS = $$HOME/.brew/Cellar/allegro/*/lib
SRC = SnakeAllegro.cpp
SRC2 = SnakeAllegro.cpp main.cpp
CC =  g++ -g -Wall -Wextra -Werror -std=c++11

FLAGS =  -L $(LIBS) -lallegro  -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro -lallegro_ttf -lallegro_video

all: $(NAME)

$(NAME): fclean
	@ # $(CC) -o snake $(SRC2) -I ../ -I $(INCL) $(FLAGS)
	@  $(CC) -shared -fPIC -o $(NAME) $(SRC) -I ../ -I  $(INCL) $(FLAGS)

clean:
	@rm -fr $(NAME)
	@rm -fr $(NAME).dSYM

fclean : clean

re: fclean all