# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/15 11:47:19 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/07/17 16:31:25 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libSnakeFLTK.so

INCL = -I ../ -I $$HOME/.brew/opt/FLTK/include
LIBS = -L $$HOME/.brew/opt/FLTK/lib
SRC = SnakeFLTK.cpp
SRC2 = main.cpp SnakeFLTK.cpp 
CC =  g++ -g -Wall -Wextra -Werror -std=c++11

FLAGS = -lfltk

all: $(NAME)

$(NAME): fclean
	@ # $(CC) -o snake $(SRC2) $(INCL) $(LIBS) $(FLAGS)
	@  $(CC) -shared -fPIC -o $(NAME) $(SRC) $(INCL) $(LIBS) $(FLAGS)

clean:
	@rm -fr $(NAME)
	@rm -fr $(NAME).dSYM
	@rm -fr *.dSYM

fclean : clean

re: fclean all