# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-bagh <ael-bagh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/09 18:49:01 by ael-bagh          #+#    #+#              #
#    Updated: 2021/06/09 19:10:06 by ael-bagh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = execute.c ft_split.c main.c parsing_utils.c utils.c
NAME = pipex

all: $(NAME)

$(NAME): 
	gcc -Wall -Werror -Wextra -fsanitize=address -o pipex $(SRC)
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all