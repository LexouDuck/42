NAME	=	fillit

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

LFTDIR	=	./libft/
SRCDIR	=	./src/
HDRDIR	=	./
TSTDIR	=	./tests/

LIBFT	=	libft.a

HDRS	=	$(HDRDIR)fillit.h			\
			$(LFTDIR)libft.h
SRCS	=	$(SRCDIR)main.c				\
			$(SRCDIR)reader.c			\
			$(SRCDIR)solver.c			\
			$(SRCDIR)util_map.c			\
			$(SRCDIR)util_t_minos.c		\
			$(SRCDIR)util_t_square.c	\
			$(SRCDIR)tmtype_to_strls.c

OBJS	=	$(SRCS:.c=.o)
GCH		=	$(HDRS:.h=.h.gch)

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

%.o: %.c
	@printf "Compiling file: "$@" -> "$(RED)
	@$(CC) -c $< $(CFLAGS) -o $@
	@printf $(GREEN)"OK!"$(RESET)"\r"

$(NAME): $(OBJS)
	@make -C $(LFTDIR) all
	@printf "Compiling program: "$@" -> "
	@$(CC) $^ $(CFLAGS) -o $@ -lft -L$(LFTDIR)
	@printf $(GREEN)"OK!"$(RESET)"\r"

all: $(NAME)

clean:
	@printf "Deleting object files...\n"
	@make -C $(LFTDIR) clean
	@rm -f $(OBJS)

fclean: clean
	@printf "Deleting executable files...\n"
	@make -C $(LFTDIR) fclean
	@rm -f $(NAME)

re: fclean all

test: all
	@printf "Testing fillit:\n"
	@$(TSTDIR)test.sh
