# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-yous <mel-yous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 12:01:16 by mel-yous          #+#    #+#              #
#    Updated: 2023/05/17 17:53:58 by mel-yous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
COMPILER = cc
CFLAGS = -Wall -Werror -Wextra

SOURCES = helper.c initializer.c parsing.c philo.c threading.c
OBJECTS = $(SOURCES:.c=.o)
HEADER = philo.h

FSANITIZE = -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJECTS)
	$(COMPILER) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c $(HEADER)
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re