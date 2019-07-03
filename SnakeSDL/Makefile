# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/02 20:41:15 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/07/03 15:00:32 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libSnakeSDL.so

SRC = SnakeSDL.cpp 
SRC2 = SnakeSDL.cpp main.cpp
CC = LD_LIBRARY_PATH=$$PWD/SDL2/lib g++ -Wall -Wextra -Werror -std=c++11

FLAGS =  -L SDL2/lib -lSDL2_ttf -lSDL2 -lSDL2main -lfreetype
all: $(NAME)

$(NAME): fclean
	@  $(CC) -o snake $(SRC2) -I ../ -I SDL2/include $(FLAGS)
	@ # $(CC) -o $(NAME) -shared -fPIC $(SRC) -I ../ -I SDL2/include $(FLAGS) 

clean:
	@rm -fr $(NAME)

fclean : clean

re: fclean all
