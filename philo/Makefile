NAME = philo

SRCS = main.c\
	init.c\
	utils.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

FLAGS = -Wall -Werror -Wextra -g3

all: $(NAME)

$(NAME): $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c philo.h
	gcc $(FLAGS) -c $< -o $@

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus