# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmil.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/02 20:41:15 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/07/06 16:48:53 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libSnakeSDL.so

INCL = -I ../ -I $$HOME/.brew/opt/sdl2/include/SDL2 -I \
		$$HOME/.brew/opt/sdl2_mixer/include/SDL2 -I \
		$$HOME/.brew/opt/sdl2_ttf/include/SDL2
LIBS = -L $$HOME/.brew/opt/sdl2/lib -L $$HOME/.brew/opt/sdl2_mixer/lib \
		-L $$HOME/.brew/opt/sdl2_ttf/lib \
		-L $$HOME/.brew/opt/freetype/lib
SRC = SnakeSDL.cpp 
SRC2 = SnakeSDL.cpp main.cpp
CC = g++ -Wall -Wextra -Werror -std=c++11

FLAGS = -lSDL2_ttf -lSDL2 -lSDL2main -lSDL2_mixer -lfreetype
all: $(NAME)

$(NAME): fclean
	@ # $(CC) -o snake $(SRC2)  $(INC) $(LIBS) $(FLAGS)
	@  $(CC) -o $(NAME) -shared -fPIC $(SRC) $(INCL) $(LIBS) $(FLAGS) 

clean:
	@rm -fr $(NAME)

fclean : clean

re: fclean all
