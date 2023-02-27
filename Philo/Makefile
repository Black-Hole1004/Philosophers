# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/24 14:45:24 by ahmaymou          #+#    #+#              #
#    Updated: 2023/02/24 14:53:18 by ahmaymou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS_OBJ = $(shell ls | grep .c | grep -v main)

SRC = main.c

FLAGS = -Wall -Werror -Wextra

CC = cc

OBJ = $(SRCS_OBJ:.c=.o)

all : $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) philo.h
	$(CC) $(FLAGS) $(SRC) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re