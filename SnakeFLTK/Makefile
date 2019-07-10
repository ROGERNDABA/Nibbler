# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 08:25:55 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/07/10 09:38:45 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libSnakeFLTK.so

SRC = SnakeAllegro.cpp
SRC2 = main.cpp #SnakeAllegro.cpp
CC =  g++ -g -Wall -Wextra -Werror -std=c++11

FLAGS =  -L FLTK/lib -lfltk -lfltk_gl -lfltk_forms -lfltk_images
all: $(NAME)

$(NAME): fclean
	@  $(CC) -o snake $(SRC2) -I ../ -I FLTK/include $(FLAGS)
	@ # $(CC) -shared -fPIC -o $(NAME) $(SRC) -I ../ -I FLTK/include $(FLAGS)

clean:
	@rm -fr $(NAME)
	@rm -fr $(NAME).dSYM

fclean : clean

re: fclean all