# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/01/31 18:07:49 by ahmaymou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PHILOSOPHERS

SRCS_OBJ = $(shell ls | grep .c | grep -v main)

SRC = main.c

FLAGS = -Wall -Werror -Wextra

CC = cc

EXEC = philo

OBJ = $(SRCS_OBJ:.c=.o)

all : $(NAME)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : prog

prog : $(OBJ) philo.h
	$(CC) $(FLAGS) $(SRC) $(OBJ) -o $(EXEC)

clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(EXEC)

re : fclean all

.PHONY : all clean fclean re