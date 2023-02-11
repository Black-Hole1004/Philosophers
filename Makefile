# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/02/11 19:34:52 by ahmaymou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PHILOSOPHERS

SRCS_OBJ = $(addprefix src_mandatory/,$(shell ls src_mandatory/ | grep .c | grep -v main))

SRCS_OBJ_BONUS = $(addprefix src_bonus/,$(shell ls src_bonus/ | grep .c | grep -v main))

SRC = $(addprefix src_mandatory/,main.c)

SRC_BONUS = $(addprefix src_bonus/,main.c)

FLAGS = -Wall -Werror -Wextra

CC = cc

EXEC = philo

EXEC_BONUS = philo_bonus

OBJ = $(SRCS_OBJ:.c=.o)

OBJ_BONUS = $(SRCS_OBJ_BONUS:.c=.o)

all : $(NAME)

%.o: %.c src_mandatory/philo.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : prog

prog : $(OBJ) src_mandatory/philo.h
	$(CC) $(FLAGS) $(SRC) $(OBJ) -o $(EXEC)

bonus : $(OBJ_BONUS) src_bonus/philo.h
	$(CC) $(FLAGS) $(SRC_BONUS) $(OBJ_BONUS) -o $(EXEC_BONUS)

clean :
	rm -rf $(OBJ) $(OBJ_BONUS)
fclean : clean
	rm -rf $(EXEC) $(EXEC_BONUS)

re : fclean all

.PHONY : all clean fclean re