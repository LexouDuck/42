NAME	=	fractol

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra

LIBS	=	$(LIBFT) $(LIBX_WIN)
LIBFT	=	-L$(LFTDIR) -lft
LIBX_MAC	=	-lm -lmlx -framework OpenGL -framework AppKit
LIBX_WIN	=	-lm -L/usr/lib/ -I/usr/include/X11/ -lmlx -lX11.dll -lXext.dll

SRCDIR	=	./src/
HDRDIR	=	./
MLXDIR	=	./minilibx/
LFTDIR	=	./libft/

HDRS	=	$(HDRDIR)fdf.h				\
			$(LFTDIR)libft.h
SRCS	= 	$(SRCDIR)main.c				\
			$(SRCDIR)event.c			\
			$(SRCDIR)render.c			\
			$(SRCDIR)window.c			\
			$(SRCDIR)color.c			

OBJS	=	$(SRCS:.c=.o)

RESET	=	"\033[0m"
RED		=	"\033[0;31m"
GREEN	=	"\033[0;32m"

%.o: %.c
	@printf "Compiling file: "$@" -> "$(RED)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $(GREEN)"OK!"$(RESET)"\n"

$(NAME): $(OBJS)
	@make -C $(LFTDIR) all
	@printf "Compiling program: "$@" -> "
	@$(CC) $^ $(CFLAGS) -o $@ $(LIBS)
	@printf $(GREEN)"OK!"$(RESET)"\n"

all: $(NAME)

clean:
	@make -C $(LFTDIR) clean
	@printf "Deleting object files...\n"
	@rm -f $(OBJS)

fclean: clean
	@make -C $(LFTDIR) fclean
	@printf "Deleting program: $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

test: all
	@printf "Testing $(NAME):\n"
	startxwin ./fractol julia

mlx:
	@make -C $(MLXDIR) all && sh ./mlx.sh
	@make fclean
	@make test
