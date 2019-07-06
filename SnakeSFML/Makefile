# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 08:25:55 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/07/06 17:13:46 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libSnakeSFML.so

SRC = SnakeSFML.cpp
SRC2 = SnakeSFML.cpp main.cpp
CC = g++ -Wall -Wextra -Werror -std=c++11

FLAGS =  -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(NAME)

$(NAME): fclean
	@ # $(CC) -o snake $(SRC2) -I ../ -I SFML/include $(FLAGS)
	@  $(CC) -shared -fPIC -o $(NAME) $(SRC) -I ../ -I SFML/include $(FLAGS)

clean:
	@rm -fr $(NAME)

fclean : clean

re: fclean all
