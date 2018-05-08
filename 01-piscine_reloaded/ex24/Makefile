NAME		=	libft.a

CFLAGS		+=	-Wall -Wextra -Werror

PATH_SRCS	=	./srcs/

HEADER		=	./includes/

SRCS		=	$(PATH_SRCS)ft_putchar.c	\
				$(PATH_SRCS)ft_swap.c		\
				$(PATH_SRCS)ft_putstr.c		\
				$(PATH_SRCS)ft_strlen.c		\
				$(PATH_SRCS)ft_strcmp.c

OBJS		=	ft_putchar.o	\
				ft_swap.o		\
				ft_putstr.o		\
				ft_strlen.o		\
				ft_strcmp.o

all:
	@make $(NAME)

$(NAME):
	gcc $(CFLAGS) -c -I $(HEADER) $(SRCS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)				

re: fclean all
