# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 08:25:55 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/06/30 22:08:50 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = snake

SRC = SnakeAllegro.cpp
CC = g++ -Wall -Wextra -Werror -std=c++11

FLAGS =  -L allegro/lib  -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro -lallegro_ttf -lallegro_video

all: $(NAME)

$(NAME): fclean
	@$(CC) -shared -fPIC -o SnakeAllegro.so $(SRC) -I ../ -I allegro/include $(FLAGS)

clean:
	@rm -fr $(NAME)

fclean : clean

re: fclean all
