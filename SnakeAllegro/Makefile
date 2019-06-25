# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Roger Ndaba <rogerndaba@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 08:25:55 by Roger Ndaba       #+#    #+#              #
#    Updated: 2019/06/25 13:19:38 by Roger Ndaba      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = snake

SRC = main.cpp SnakeAllegro.cpp

CC = g++ -Wall -Wextra -Werror -std=c++11 -I allegro/include -I ../ -L allegro/lib -lallegro.5.2.5  -lallegro_audio  -lallegro_font.5.2  -lallegro_memfile.5.2.5  -lallegro_primitives  -lallegro.5.2  -lallegro_color.5.2.5  -lallegro_font  -lallegro_memfile.5.2  -lallegro_ttf.5.2.5  -lallegro  -lallegro_color.5.2  -lallegro_image.5.2.5  -lallegro_memfile  -lallegro_ttf.5.2  -lallegro_acodec.5.2.5  -lallegro_color  -lallegro_image.5.2  -lallegro_physfs.5.2.5  -lallegro_ttf -lallegro_acodec.5.2  -lallegro_dialog.5.2.5  -lallegro_image  -lallegro_physfs.5.2  -lallegro_video.5.2.5  -lallegro_acodec  -lallegro_dialog.5.2  -lallegro_main.5.2.5  -lallegro_physfs  -lallegro_video.5.2  -lallegro_audio.5.2.5  -lallegro_dialog  -lallegro_main.5.2  -lallegro_primitives.5.2.5  -lallegro_video  -lallegro_audio.5.2  -lallegro_font.5.2.5  -lallegro_main  -lallegro_primitives.5.2


all: $(NAME)

$(NAME): fclean
	@$(CC) $(SRC) -o $(NAME)

clean:
	@rm -fr $(NAME)

fclean : clean

re: fclean all
