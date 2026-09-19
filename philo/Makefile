NAME	=	philo

CC		=	cc -g3
CFLAGS	=	-Wall -Wextra -Werror -pthread

SRCS	=	main.c \
			ft_atoi.c \
			ft_isxxx.c \
			prints_fd.c \
			parse_argv.c \

SRCS	+=	test_print_state.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
