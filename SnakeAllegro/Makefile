# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 08:25:55 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/07/02 19:09:52 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libSnakeAllegro.so

SRC = SnakeAllegro.cpp
SRC2 = SnakeAllegro.cpp main.cpp
CC = LD_LIBRARY_PATH=$$PWD/allegro/lib g++ -Wall -Wextra -Werror -std=c++11

FLAGS =  -L allegro/lib  -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro -lallegro_ttf -lallegro_video

all: $(NAME)

$(NAME): fclean
	@ # $(CC) -o snake $(SRC2) -I ../ -I allegro/include $(FLAGS)
	@  $(CC) -shared -fPIC -o $(NAME) $(SRC) -I ../ -I allegro/include $(FLAGS)

clean:
	@rm -fr $(NAME)

fclean : clean

re: fclean all
