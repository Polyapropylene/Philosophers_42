# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrhyhorn <rrhyhorn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 04:51:53 by rrhyhorn          #+#    #+#              #
#    Updated: 2022/07/01 18:20:18 by rrhyhorn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = philo_bonus.c\
		utils_bonus.c\
		check_and_init_bonus.c\
		philo_lifes_bonus.c\
		ft_atoi_bonus.c
	

OBJS = $(patsubst %.c, %.o, $(SRCS))

FLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c philo_bonus.h
	gcc $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re