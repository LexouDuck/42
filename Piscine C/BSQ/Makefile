# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aduquesn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 21:33:33 by aduquesn          #+#    #+#              #
#    Updated: 2017/09/20 22:04:45 by aduquesn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	bsq
OUTPUT	=	-o $(NAME)
CFLAGS	=	-Wall -Werror -Wextra

FILES	=	main.c			\
			reader.c		\
			solver.c		\
			split_map.c		\
			check_map.c		\
			util_display.c	\
			util_strings.c

OBJS	=	$(FILES:.c=.o)

TESTS	=	tests/*

all: $(OBJS)
	gcc $(OUTPUT) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: $(OBJS)
	gcc -g $(OUTPUT) $(CFLAGS) $(OBJS)

test: re
	./$(NAME) $(TESTS)
	rm -f *.o
