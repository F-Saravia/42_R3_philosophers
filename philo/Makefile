NAME	=	philo

CC		=	cc 
CFLAGS	=	-Wall -Wextra -Werror -pthread

SRCS	=	main.c \
			ft_atoi.c \
			ft_isxxx.c \
			prints_fd.c \
			parse_argv.c \
			print_philo_isdoing.c \
			time_utils.c \
			state_get_set.c \
			state_init_clean.c \
			threads_init.c \
			threads_start.c \
			philo_do.c \
			philo_eat_death.c \
			fork_gatekeeper.c

# SRCS	+=	test_print_state.c

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
