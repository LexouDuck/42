NAME	=	ft_display_file

SRCS	=	ft_display_file.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	+=	-Wall -Wextra -Werror

all:
	@make $(NAME)

$(NAME):
	gcc -c $(SRCS)
	gcc -o $(NAME) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
