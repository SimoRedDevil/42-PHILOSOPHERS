NAME = philo
SRCS = philo.c parser.c helper.c initializer.c threading.c
OBJS = $(SRCS:.c=.o)

GCC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	$(GCC) $(OBJS) -o $@
%.o: %.c philo.h
	$(GCC) -c $< -o $@

clean:
	rm -rf $(OBJS)
fclean: clean
	rm -rf $(NAME)
re: fclean all